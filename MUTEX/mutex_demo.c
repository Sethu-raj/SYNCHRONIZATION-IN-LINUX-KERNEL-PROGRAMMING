#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Mutex Demo");

static struct task_struct *thread1;
static struct task_struct *thread2;

static struct mutex my_mutex;

static int thread_fn1(void *data)
{
    printk(KERN_INFO "Thread1: Waiting for mutex\n");

    mutex_lock(&my_mutex);

    printk(KERN_INFO "Thread1: Acquired mutex\n");

    msleep(5000);

    printk(KERN_INFO "Thread1: Releasing mutex\n");

    mutex_unlock(&my_mutex);

    return 0;
}

static int thread_fn2(void *data)
{
    msleep(1000);

    printk(KERN_INFO "Thread2: Waiting for mutex\n");

    mutex_lock(&my_mutex);

    printk(KERN_INFO "Thread2: Acquired mutex\n");

    msleep(2000);

    printk(KERN_INFO "Thread2: Releasing mutex\n");

    mutex_unlock(&my_mutex);

    return 0;
}

static int __init mutex_demo_init(void)
{
    printk(KERN_INFO "Mutex Module Loaded\n");

    mutex_init(&my_mutex);

    thread1 = kthread_run(thread_fn1, NULL, "mutex_thread1");
    thread2 = kthread_run(thread_fn2, NULL, "mutex_thread2");

    return 0;
}

static void __exit mutex_demo_exit(void)
{
    printk(KERN_INFO "Mutex Module Unloaded\n");
}

module_init(mutex_demo_init);
module_exit(mutex_demo_exit);
