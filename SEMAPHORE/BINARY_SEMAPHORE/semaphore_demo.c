#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/semaphore.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Semaphore Demo");

static struct task_struct *thread1;
static struct task_struct *thread2;

/* Binary Semaphore */
static struct semaphore sem;

static int thread_fn1(void *data)
{
    printk(KERN_INFO "Thread1: Waiting for semaphore\n");

    down(&sem);

    printk(KERN_INFO "Thread1: Acquired semaphore\n");

    msleep(5000);

    printk(KERN_INFO "Thread1: Releasing semaphore\n");

    up(&sem);

    return 0;
}

static int thread_fn2(void *data)
{
    msleep(1000);

    printk(KERN_INFO "Thread2: Waiting for semaphore\n");

    down(&sem);

    printk(KERN_INFO "Thread2: Acquired semaphore\n");

    msleep(2000);

    printk(KERN_INFO "Thread2: Releasing semaphore\n");

    up(&sem);

    return 0;
}

static int __init semaphore_demo_init(void)
{
    printk(KERN_INFO "Semaphore Module Loaded\n");

    /* Binary semaphore */
    sema_init(&sem, 1);

    thread1 = kthread_run(thread_fn1, NULL, "sem_thread1");
    thread2 = kthread_run(thread_fn2, NULL, "sem_thread2");

    return 0;
}

static void __exit semaphore_demo_exit(void)
{
    printk(KERN_INFO "Semaphore Module Unloaded\n");
}

module_init(semaphore_demo_init);
module_exit(semaphore_demo_exit);
