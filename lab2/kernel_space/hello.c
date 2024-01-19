#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include "my_task_struct.h"

static void task_to_mts(struct task_struct *task, struct my_task_struct *mts){
    mts->pid = task->pid;
    mts->ppid = task_ppid_nr(task);
    mts->cmd = (char *)(task->comm);
    mts->com_len = strlen(mts->cmd);
    mts->tty = tty_name(task->signal->tty);
    mts->tty_len = strlen(mts->tty);
}

SYSCALL_DEFINE0(hello)
{
  printk("KERNEL SAYS: HELLO\n");
  return 0;
}

SYSCALL_DEFINE2(get_task_struct, int*, size, void*, data)
{
  struct task_struct *task;
  struct my_task_struct* mts = kmalloc(sizeof(struct my_task_struct), GFP_KERNEL);
  struct my_task_struct *ts = kmalloc(sizeof(my_task_struct)*200, GFP_KERNEL);

  int i = 0;
  for_each_process(task) {
    task_to_mts(task, mts);
    ts[i] = mts;
    i++;
  }

  int copy_result = copy_to_user(data, ts, sizeof(ts));
  if (copy_result > 0){
    printk(KERN_ERR "Failed to copy %d bytes\n", copy_result);
    return -EFAULT;
  }

  size = i;
  return 0;
}

