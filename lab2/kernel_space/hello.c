#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>

SYSCALL_DEFINE0(hello)
{
  printk("KERNEL SAYS: HELLO\n");
  return 0;
}

SYSCALL_DEFINE1(get_task_struct, void*, data)
{
  struct task_struct *task;
  struct task_struct *ts = kmalloc(sizeof(task)*200, GFP_KERNEL);

  int i = 0;
  for_each_process(task) {
    printk(KERN_INFO "PID: %d, Name: %s\n", task->pid, task->comm);

    ts[i] = *task;
    i++;
  }

  int copy_result = copy_to_user(data, ts, sizeof(ts));
  if (copy_result > 0){
    printk(KERN_ERR "Failed to copy %d bytes\n", copy_result);
    return -EFAULT;
  }

  return 0;
}

