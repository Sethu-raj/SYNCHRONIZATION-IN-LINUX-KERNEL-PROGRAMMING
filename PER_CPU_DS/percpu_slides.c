#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>
#include <linux/smp.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sethu");
MODULE_DESCRIPTION("Per CPU Variables Demo");

#define PROC_FILENAME "percpu_entry"

/* Per-CPU style array */
static unsigned int percpu_data[NR_CPUS];

/* Read function */
static int proc_show_cpu(struct seq_file *m, void *v)
{
    int cpu;

    seq_printf(m, "--- Per-CPU Data Array State ---\n");

    for_each_online_cpu(cpu) {
        seq_printf(m,
                   "percpu_data on cpu=%d is %u\n",
                   cpu,
                   percpu_data[cpu]);
    }

    return 0;
}

/* Open function */
static int proc_open_cpu(struct inode *inode, struct file *file)
{
    return single_open(file, proc_show_cpu, NULL);
}

/* Write function */
static ssize_t proc_write_cpu(struct file *file,
                              const char __user *buffer,
                              size_t count,
                              loff_t *ppos)
{
    char buf[10];
    unsigned int user_val;
    int cpu;

    pr_info("%s called\n", __func__);

    if (count >= sizeof(buf))
        return -EINVAL;

    if (copy_from_user(buf, buffer, count))
        return -EFAULT;

    buf[count] = '\0';

    if (kstrtouint(buf, 10, &user_val))
        return -EINVAL;

    /* Disable preemption and get current CPU */
    cpu = get_cpu();

    percpu_data[cpu] = user_val;

    pr_info("percpu_data on cpu=%d is %u\n",
            cpu,
            percpu_data[cpu]);

    /* Enable preemption */
    put_cpu();

    return count;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)

static const struct proc_ops cpu_proc_fops = {
    .proc_open    = proc_open_cpu,
    .proc_read    = seq_read,
    .proc_write   = proc_write_cpu,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

#else

static const struct file_operations cpu_proc_fops = {
    .owner   = THIS_MODULE,
    .open    = proc_open_cpu,
    .read    = seq_read,
    .write   = proc_write_cpu,
    .llseek  = seq_lseek,
    .release = single_release,
};

#endif

/* Module Init */
static int __init percpu_slides_init(void)
{
    if (!proc_create(PROC_FILENAME,
                     0666,
                     NULL,
                     &cpu_proc_fops)) {

        pr_err("Failed to create /proc/%s\n",
               PROC_FILENAME);
        return -ENOMEM;
    }

    pr_info("Created /proc/%s\n",
            PROC_FILENAME);

    return 0;
}

/* Module Exit */
static void __exit percpu_slides_exit(void)
{
    remove_proc_entry(PROC_FILENAME, NULL);

    pr_info("Module unloaded\n");
}

module_init(percpu_slides_init);
module_exit(percpu_slides_exit);
