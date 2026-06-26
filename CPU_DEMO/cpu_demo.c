#include <linux/module.h>
#include <linux/init.h>
#include <linux/smp.h>

MODULE_LICENSE("GPL");

static int __init cpu_info_init(void)
{
    int cpu;

    for_each_online_cpu(cpu)
        pr_info("Online CPU: %d\n", cpu);

    return 0;
}

static void __exit cpu_info_exit(void)
{
    pr_info("Module Removed\n");
}

module_init(cpu_info_init);
module_exit(cpu_info_exit);
