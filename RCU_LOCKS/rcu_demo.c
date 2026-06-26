#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/rcupdate.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Simple RCU Demo");

struct my_data {
    int value;
};

/* Global RCU protected pointer */
static struct my_data __rcu *gptr;

static struct task_struct *reader_thread;
static struct task_struct *writer_thread;

/* Reader Thread */
static int reader_fn(void *data)
{
    struct my_data *ptr;

    while (!kthread_should_stop()) {

        rcu_read_lock();

        ptr = rcu_dereference(gptr);

        if (ptr)
            printk(KERN_INFO "Reader : value = %d\n", ptr->value);

        rcu_read_unlock();

        msleep(1000);
    }

    return 0;
}

/* Writer Thread */
static int writer_fn(void *data)
{
    struct my_data *old;
    struct my_data *new;

    while (!kthread_should_stop()) {

        msleep(5000);

        /* Allocate new object */
        new = kmalloc(sizeof(*new), GFP_KERNEL);
        if (!new)
            continue;

        /* Get current object */
        old = rcu_dereference_protected(gptr, 1);

        if (old)
            new->value = old->value + 1;
        else
            new->value = 1;

        printk(KERN_INFO "Writer : updating value to %d\n", new->value);

        /* Atomically replace pointer */
        rcu_assign_pointer(gptr, new);

        /* Wait until all readers finish */
        synchronize_rcu();

        /* Safe to free old object */
        if (old)
            kfree(old);
    }

    return 0;
}

/* Module Init */
static int __init rcu_demo_init(void)
{
    struct my_data *init_data;

    init_data = kmalloc(sizeof(*init_data), GFP_KERNEL);
    if (!init_data)
        return -ENOMEM;

    init_data->value = 0;

    rcu_assign_pointer(gptr, init_data);

    reader_thread = kthread_run(reader_fn, NULL, "rcu_reader");
    writer_thread = kthread_run(writer_fn, NULL, "rcu_writer");

    printk(KERN_INFO "RCU Demo Module Loaded\n");

    return 0;
}

/* Module Exit */
static void __exit rcu_demo_exit(void)
{
    struct my_data *ptr;

    kthread_stop(reader_thread);
    kthread_stop(writer_thread);

    synchronize_rcu();

    ptr = rcu_dereference_protected(gptr, 1);

    if (ptr)
        kfree(ptr);

    printk(KERN_INFO "RCU Demo Module Unloaded\n");
}

module_init(rcu_demo_init);
module_exit(rcu_demo_exit);
