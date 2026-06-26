#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cpumask.h>
#include <linux/smp.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("NR_CPUS and Online CPUs Demo");

static int __init nr_cpus_demo_init(void)
{
    pr_info("========== CPU Information ==========\n");

    pr_info("Maximum CPUs supported (NR_CPUS) = %d\n", NR_CPUS);

    pr_info("Online CPUs = %d\n", num_online_cpus());

    pr_info("Possible CPUs = %u\n", num_possible_cpus());

    pr_info("Present CPUs = %u\n", num_present_cpus());

    pr_info("=====================================\n");

    return 0;
}

static void __exit nr_cpus_demo_exit(void)
{
    pr_info("NR_CPUS Demo Module Removed\n");
}

module_init(nr_cpus_demo_init);
module_exit(nr_cpus_demo_exit);
