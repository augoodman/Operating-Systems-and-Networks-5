/**
* File:   GoodmanLKM.c
* Linux Kernel Module for displaying kernel processes
*
* Completion time:  10 hours
*
* @author Goodman
* @version 2020.09.03
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/sched/signal.h>

/* Take in command line argument as module parameter. */
int inp_pid = 0;
module_param(inp_pid, int, 0644);

struct task_struct* p;
struct list_head* list;

/* This function is called when the module is loaded. */
int process_list_init(void) {
    printk(KERN_INFO "Loading Module\n");
    for_each_process(p) {
        if(p->pid > inp_pid) {
            printk("PROCESS        \tPID\tSTATE\tPRIO\tST_PRIO\tNORM_PRIO\n");
            printk("%-15s\t%d\t%ld\t%d\t%d\t%d\n", p->comm, p->pid, p->state, p->prio, p->static_prio, p->normal_prio);
            list_for_each(list, &p->children) {
                struct task_struct *child;
                child = list_entry(list, struct task_struct, sibling);
                printk("CHILD\n");
                printk("%-15s\t%d\t%ld\t%d\t%d\t%d\n", child->comm, child->pid, child->state, child->prio,
                       child->static_prio, child->normal_prio);
            }
            printk("PARENT\n");
            printk("%-15s\t%d\t%ld\t%d\t%d\t%d\n\n", p->real_parent->comm, p->real_parent->pid, p->real_parent->state,
                   p->real_parent->prio, p->real_parent->static_prio, p->real_parent->normal_prio);
        }
    }
    return 0;
}

/* This function is called when the module is removed. */
void process_list_exit(void) {
    printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( process_list_init );
module_exit( process_list_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Display system processes");
MODULE_AUTHOR("Goodman");