#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/atomic.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Atomic Operators Demo");

static atomic_t counter = ATOMIC_INIT(5);

static int __init atomic_demo_init(void)
{
    printk(KERN_INFO "\n===== Atomic Operations Demo =====\n");

    printk(KERN_INFO "Initial Value = %d\n",
           atomic_read(&counter));

    atomic_inc(&counter);
    printk(KERN_INFO "After atomic_inc() = %d\n",
           atomic_read(&counter));

    atomic_dec(&counter);
    printk(KERN_INFO "After atomic_dec() = %d\n",
           atomic_read(&counter));

    atomic_add(10, &counter);
    printk(KERN_INFO "After atomic_add(10) = %d\n",
           atomic_read(&counter));

    atomic_sub(3, &counter);
    printk(KERN_INFO "After atomic_sub(3) = %d\n",
           atomic_read(&counter));

    atomic_set(&counter, 100);
    printk(KERN_INFO "After atomic_set(100) = %d\n",
           atomic_read(&counter));

    printk(KERN_INFO "==================================\n");

    return 0;
}

static void __exit atomic_demo_exit(void)
{
    printk(KERN_INFO "Atomic Demo Module Removed\n");
}

module_init(atomic_demo_init);
module_exit(atomic_demo_exit);
