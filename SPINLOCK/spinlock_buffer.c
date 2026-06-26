#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Spinlock Shared Buffer Demo");

#define BUF_SIZE 10

/* Shared Buffer */
static int buffer[BUF_SIZE];
static int index_pos = 0;

/* Spinlock */
static spinlock_t buffer_lock;

/* Kernel Threads */
static struct task_struct *thread1;
static struct task_struct *thread2;

/* Producer Thread */
static int producer_fn(void *data)
{
    int value = (long)data;

    while (!kthread_should_stop())
    {
        spin_lock(&buffer_lock);

        if (index_pos < BUF_SIZE)
        {
            buffer[index_pos++] = value;

            printk(KERN_INFO
                   "Thread-%d -> Added %d, index=%d\n",
                   value,
                   value,
                   index_pos);
        }

        spin_unlock(&buffer_lock);

        msleep(500);
    }

    return 0;
}

static int __init spinlock_demo_init(void)
{
    printk(KERN_INFO "Spinlock Buffer Demo Loaded\n");

    spin_lock_init(&buffer_lock);

    thread1 = kthread_run(producer_fn,
                          (void *)1,
                          "producer1");

    thread2 = kthread_run(producer_fn,
                          (void *)2,
                          "producer2");

    return 0;
}

static void __exit spinlock_demo_exit(void)
{
    int i;

    kthread_stop(thread1);
    kthread_stop(thread2);

    printk(KERN_INFO "\nFinal Buffer Contents:\n");

    for (i = 0; i < index_pos; i++)
        printk(KERN_INFO "buffer[%d] = %d\n",
               i,
               buffer[i]);

    printk(KERN_INFO "Spinlock Demo Unloaded\n");
}

module_init(spinlock_demo_init);
module_exit(spinlock_demo_exit);
