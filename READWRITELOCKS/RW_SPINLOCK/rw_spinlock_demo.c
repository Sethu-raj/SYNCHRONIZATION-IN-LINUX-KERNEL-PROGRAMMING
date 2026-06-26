#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/rwlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("RW Spinlock Demo");

static rwlock_t my_rwlock;
static int shared_data = 0;

static struct task_struct *reader1;
static struct task_struct *reader2;
static struct task_struct *writer;

static int reader_fn(void *data)
{
    int id = *(int *)data;

    while (!kthread_should_stop()) {

        read_lock(&my_rwlock);

        printk(KERN_INFO "Reader-%d: shared_data = %d\n",
               id, shared_data);

        read_unlock(&my_rwlock);

        msleep(1000);
    }

    return 0;
}

static int writer_fn(void *data)
{
    while (!kthread_should_stop()) {

        write_lock(&my_rwlock);

        shared_data++;

        printk(KERN_INFO
               "Writer: Updated shared_data = %d\n",
               shared_data);

        write_unlock(&my_rwlock);

        msleep(5000);
    }

    return 0;
}

static int __init rw_spinlock_init(void)
{
    static int id1 = 1;
    static int id2 = 2;

    rwlock_init(&my_rwlock);

    reader1 = kthread_run(reader_fn, &id1, "reader1");
    reader2 = kthread_run(reader_fn, &id2, "reader2");
    writer  = kthread_run(writer_fn, NULL, "writer");

    printk(KERN_INFO "RW Spinlock Module Loaded\n");

    return 0;
}

static void __exit rw_spinlock_exit(void)
{
    kthread_stop(reader1);
    kthread_stop(reader2);
    kthread_stop(writer);

    printk(KERN_INFO "RW Spinlock Module Unloaded\n");
}

module_init(rw_spinlock_init);
module_exit(rw_spinlock_exit);
