/**
* File:   GoodmanLKM.c
* Linux Kernel Module for displaying kernel processes
*
* Completion time:  __ hours
*
* @author Goodman
* @version 2020.09.03
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("SER334");
MODULE_DESCRIPTION("Display processes");
MODULE_AUTHOR("Goodman");