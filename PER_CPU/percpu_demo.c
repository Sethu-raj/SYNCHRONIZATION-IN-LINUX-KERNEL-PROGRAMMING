#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/percpu.h>
#include <linux/smp.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Per CPU Variable Demo");

/* Declare a per-CPU variable */
DEFINE_PER_CPU(int, cpu_counter);

static int __init percpu_demo_init(void)
{
    int cpu;

    cpu = smp_processor_id();

    /* Increment current CPU's counter */
    this_cpu_inc(cpu_counter);

    pr_info("Current CPU = %d\n", cpu);
    pr_info("CPU %d Counter = %d\n",
            cpu,
            this_cpu_read(cpu_counter));

    return 0;
}

static void __exit percpu_demo_exit(void)
{
    int cpu;

    pr_info("Per CPU Counter Values:\n");

    for_each_online_cpu(cpu) {
        pr_info("CPU %d -> %d\n",
                cpu,
                per_cpu(cpu_counter, cpu));
    }

    pr_info("Per CPU Demo Module Removed\n");
}

module_init(percpu_demo_init);
module_exit(percpu_demo_exit);
