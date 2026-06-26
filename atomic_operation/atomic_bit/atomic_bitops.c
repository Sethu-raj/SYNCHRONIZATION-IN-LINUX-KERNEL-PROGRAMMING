#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/bitops.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Atomic Bit Operations Demo");

static unsigned long flags = 0;

static int __init bitops_demo_init(void)
{
    printk(KERN_INFO "\n===== Atomic Bit Operations Demo =====\n");

    printk(KERN_INFO "Initial flags = %lx\n", flags);

    /* Set bit 0 */
    set_bit(0, &flags);
    printk(KERN_INFO "After set_bit(0)       = %lx\n", flags);

    /* Set bit 2 */
    set_bit(2, &flags);
    printk(KERN_INFO "After set_bit(2)       = %lx\n", flags);

    /* Test bit 0 */
    if (test_bit(0, &flags))
        printk(KERN_INFO "Bit 0 is SET\n");

    /* Clear bit 0 */
    clear_bit(0, &flags);
    printk(KERN_INFO "After clear_bit(0)     = %lx\n", flags);

    /* Toggle bit 1 */
    change_bit(1, &flags);
    printk(KERN_INFO "After change_bit(1)    = %lx\n", flags);

    /* Test and Set bit 3 */
    printk(KERN_INFO "Old value of bit3 = %d\n",
           test_and_set_bit(3, &flags));

    printk(KERN_INFO "After test_and_set_bit(3) = %lx\n",
           flags);

    /* Test and Clear bit 2 */
    printk(KERN_INFO "Old value of bit2 = %d\n",
           test_and_clear_bit(2, &flags));

    printk(KERN_INFO "After test_and_clear_bit(2) = %lx\n",
           flags);

    printk(KERN_INFO "======================================\n");

    return 0;
}

static void __exit bitops_demo_exit(void)
{
    printk(KERN_INFO "Atomic Bit Operations Module Removed\n");
}

module_init(bitops_demo_init);
module_exit(bitops_demo_exit);
