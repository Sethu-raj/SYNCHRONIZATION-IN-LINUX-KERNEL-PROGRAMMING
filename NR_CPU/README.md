# NR_CPUS and Online CPUs Kernel Module

## Overview

This Linux Kernel Module demonstrates the use of CPU-related kernel APIs:

* `NR_CPUS`
* `num_online_cpus()`
* `num_possible_cpus()`
* `num_present_cpus()`

The module prints CPU information to the kernel log during module initialization.

---

## Objective

To understand:

* Maximum CPUs supported by the kernel.
* Number of CPUs currently online.
* Number of CPUs present in the system.
* Number of CPUs that the kernel may use.

---

## APIs Used

### NR_CPUS

```c
NR_CPUS
```

Returns the maximum number of processors supported by the kernel configuration.

Example:

```text
NR_CPUS = 8192
```

---

### num_online_cpus()

```c
num_online_cpus();
```

Returns the number of CPUs currently online and available for scheduling.

---

### num_possible_cpus()

```c
num_possible_cpus();
```

Returns the maximum number of CPUs the kernel may use.

---

### num_present_cpus()

```c
num_present_cpus();
```

Returns the number of CPUs physically present in the system.

---

## Source File

### nr_cpus_demo.c

The module prints CPU-related information during initialization.

---

## Build Instructions

Compile the module:

```bash
make
```

Generated output:

```text
nr_cpus_demo.ko
```

---

## Load the Module

Insert the module into the kernel:

```bash
sudo insmod nr_cpus_demo.ko
```

---

## Verify Output

Check kernel messages:

```bash
dmesg | tail -10
```

Example Output:

```text
========== CPU Information ==========
Maximum CPUs supported (NR_CPUS) = 8192
Online CPUs = 4
Possible CPUs = 4
Present CPUs = 4
=====================================
```

---

## Remove the Module

Unload the module:

```bash
sudo rmmod nr_cpus_demo
```

Verify:

```bash
dmesg | tail -5
```

---

## Checking Kernel Configuration

To view the configured maximum number of CPUs:

```bash
grep NR_CPUS /boot/config-$(uname -r)
```

Example:

```text
CONFIG_NR_CPUS=8192
```

---

## Limiting CPUs at Boot Time

The number of CPUs used by the kernel can be limited using the boot parameter:

```text
nr_cpus=12
```

Example GRUB entry:

```text
GRUB_CMDLINE_LINUX="nr_cpus=12"
```

After reboot, the kernel will use only 12 CPUs even if more are available.

---

## Expected Learning Outcome

After completing this experiment, you should be able to:

* Understand SMP CPU configuration.
* Use CPU-related kernel APIs.
* Determine the maximum and active CPUs in a Linux system.
* Build and load Linux kernel modules.
* Interpret CPU information from kernel logs.

---

## Author

Sethu Raj

Linux Kernel Programming Practice
