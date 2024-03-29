#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <linux/tty.h>
#include "my_task_struct.h"

static void task_to_mts(struct task_struct *task, struct my_task_struct *mts){
    mts->pid = task->pid;
    mts->ppid = task_ppid_nr(task);
    mts->cmd = (char *)(task->comm);
    mts->com_len = strlen(mts->cmd);
    mts->tty = tty_name(task->signal->tty);
    mts->tty_len = strlen(mts->tty);
}

static void print_process_info(struct my_task_struct *task){
    printk(KERN_INFO "PID: %d, PPID: %d, CMD: %s, TTY: %s", task->pid, task->ppid, task->cmd, task->tty);
}

static int __init my_module_init(void){
    printk(KERN_INFO "Module initialized\n");
   
    struct task_struct *task;
    for_each_process(task){
       struct my_task_struct* mts = kmalloc(sizeof(struct my_task_struct), GFP_KERNEL);
       task_to_mts(task, mts);
       print_process_info(mts);
       kfree(mts);
    }

    return 0;
}

static void __exit my_module_exit(void){
    printk(KERN_INFO "Module exited\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
