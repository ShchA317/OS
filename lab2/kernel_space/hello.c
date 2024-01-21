#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/tty.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include "my_task_struct.h"

static void task_to_mts(struct task_struct *task, struct my_task_struct *mts){
    mts->pid = task->pid;
    mts->ppid = task_ppid_nr(task);
    strncpy(mts->cmd, task->comm, TASK_COMM_LEN);
    strncpy(mts->tty, tty_name(task->signal->tty), 64);
}

SYSCALL_DEFINE0(hello)
{
  printk("KERNEL SAYS: HELLO BUDDY\n");
  return 0;
}

SYSCALL_DEFINE2(get_task_struct, int*, size, void*, data)
{
  struct task_struct *task;
  printk("[hello]: allocating %i structs for ps\n", *size);
  int bufsize = sizeof(struct my_task_struct) * *size;
  struct my_task_struct *ts = kmalloc(bufsize, GFP_KERNEL);

  int i = 0;
  for_each_process(task) {
    printk("[hello]: copying info of process with %i pid\n", task->pid);
    task_to_mts(task, ts + i);
    if (++i == *size)
	break;
  }

  int copy_result = copy_to_user(data, ts, bufsize);
  kfree(ts);
  if (copy_result > 0){
    printk(KERN_ERR "Failed to copy %d bytes\n", copy_result);
    return -EFAULT;
  }

  *size = i;
  return 0;
}

