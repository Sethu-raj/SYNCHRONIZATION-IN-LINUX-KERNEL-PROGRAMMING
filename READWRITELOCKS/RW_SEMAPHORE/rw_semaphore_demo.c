#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/rwsem.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("RW Semaphore Demo");

static struct rw_semaphore my_rwsem;
static int shared_data = 0;

static struct task_struct *reader1;
static struct task_struct *reader2;
static struct task_struct *writer;

static int reader_fn(void *data)
{
    int id = *(int *)data;

    while (!kthread_should_stop()) {

        down_read(&my_rwsem);

        printk(KERN_INFO
               "Reader-%d: shared_data = %d\n",
               id, shared_data);

        up_read(&my_rwsem);

        msleep(1000);
    }

    return 0;
}

static int writer_fn(void *data)
{
    while (!kthread_should_stop()) {

        down_write(&my_rwsem);

        shared_data++;

        printk(KERN_INFO
               "Writer: Updated shared_data = %d\n",
               shared_data);

        msleep(3000);

        up_write(&my_rwsem);

        msleep(2000);
    }

    return 0;
}

static int __init rwsem_demo_init(void)
{
    static int id1 = 1;
    static int id2 = 2;

    init_rwsem(&my_rwsem);

    reader1 = kthread_run(reader_fn, &id1, "reader1");
    reader2 = kthread_run(reader_fn, &id2, "reader2");
    writer  = kthread_run(writer_fn, NULL, "writer");

    printk(KERN_INFO "RW Semaphore Module Loaded\n");

    return 0;
}

static void __exit rwsem_demo_exit(void)
{
    kthread_stop(reader1);
    kthread_stop(reader2);
    kthread_stop(writer);

    printk(KERN_INFO "RW Semaphore Module Unloaded\n");
}

module_init(rwsem_demo_init);
module_exit(rwsem_demo_exit);
