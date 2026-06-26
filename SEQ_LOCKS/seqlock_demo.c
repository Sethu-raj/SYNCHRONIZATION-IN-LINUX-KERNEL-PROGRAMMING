#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/seqlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Sequential Lock (Seqlock) Demo");

static seqlock_t my_seqlock;
static int shared_data = 0;

static struct task_struct *reader1;
static struct task_struct *reader2;
static struct task_struct *writer;

/* Reader Thread */
static int reader_fn(void *data)
{
    int id = *(int *)data;
    unsigned int seq;
    int value;

    while (!kthread_should_stop()) {

        do {
            seq = read_seqbegin(&my_seqlock);

            value = shared_data;

        } while (read_seqretry(&my_seqlock, seq));

        printk(KERN_INFO "Reader-%d : shared_data = %d\n", id, value);

        msleep(1000);
    }

    return 0;
}

/* Writer Thread */
static int writer_fn(void *data)
{
    while (!kthread_should_stop()) {

        msleep(5000);

        write_seqlock(&my_seqlock);

        shared_data++;

        printk(KERN_INFO "Writer : Updated shared_data = %d\n",
               shared_data);

        write_sequnlock(&my_seqlock);
    }

    return 0;
}

/* Module Init */
static int __init seqlock_demo_init(void)
{
    static int id1 = 1;
    static int id2 = 2;

    seqlock_init(&my_seqlock);

    reader1 = kthread_run(reader_fn, &id1, "reader1");
    reader2 = kthread_run(reader_fn, &id2, "reader2");
    writer  = kthread_run(writer_fn, NULL, "writer");

    printk(KERN_INFO "Seqlock Demo Module Loaded\n");

    return 0;
}

/* Module Exit */
static void __exit seqlock_demo_exit(void)
{
    kthread_stop(reader1);
    kthread_stop(reader2);
    kthread_stop(writer);

    printk(KERN_INFO "Seqlock Demo Module Unloaded\n");
}

module_init(seqlock_demo_init);
module_exit(seqlock_demo_exit);
