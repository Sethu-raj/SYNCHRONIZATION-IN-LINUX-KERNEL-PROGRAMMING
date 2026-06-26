#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/semaphore.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Counting Semaphore Demo");

#define NUM_THREADS 5

static struct semaphore sem;
static struct task_struct *threads[NUM_THREADS];

static int thread_fn(void *data)
{
    int id = *(int *)data;

    printk(KERN_INFO "Thread-%d: Waiting for semaphore\n", id);

    down(&sem);

    printk(KERN_INFO "Thread-%d: Acquired semaphore\n", id);

    msleep(5000);

    printk(KERN_INFO "Thread-%d: Releasing semaphore\n", id);

    up(&sem);

    return 0;
}

static int __init counting_sem_init(void)
{
    static int ids[NUM_THREADS];
    int i;

    printk(KERN_INFO "Counting Semaphore Module Loaded\n");

    /* Allow 3 threads simultaneously */
    sema_init(&sem, 3);

    for (i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        threads[i] = kthread_run(thread_fn,
                                 &ids[i],
                                 "sem_thread_%d",
                                 i + 1);
    }

    return 0;
}

static void __exit counting_sem_exit(void)
{
    printk(KERN_INFO "Counting Semaphore Module Unloaded\n");
}

module_init(counting_sem_init);
module_exit(counting_sem_exit);
