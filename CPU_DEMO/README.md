# SMP Processor ID Kernel Module

## Overview

This Linux Kernel Module demonstrates the usage of the `smp_processor_id()` API to identify the CPU on which the current kernel code is executing.

The module prints the processor ID during module initialization and unload operations. This example is useful for understanding Symmetric Multiprocessing (SMP) concepts in the Linux kernel.

---

## Objectives

* Learn about SMP (Symmetric Multiprocessing).
* Understand the `smp_processor_id()` API.
* Identify the CPU executing kernel code.
* Build and load a simple Linux kernel module.

---

## Source Code

### File: `cpu_demo.c`

The module uses:

```c
smp_processor_id();
```

to retrieve the current processor ID.

---

## Build Instructions

Compile the module using:

```bash
make
```

This generates:

```text
cpu_demo.ko
```

---

## Load the Module

Insert the module into the kernel:

```bash
sudo insmod cpu_demo.ko
```

---

## Verify Output

Check kernel messages:

```bash
dmesg | tail -10
```

Example Output:

```text
Running on CPU: 2
```

The output indicates that the module initialization function executed on CPU 2.

---

## Remove the Module

Unload the module:

```bash
sudo rmmod cpu_demo
```

Verify:

```bash
dmesg | tail -10
```

Example Output:

```text
Module Removed
```

---

## Understanding `smp_processor_id()`

### Syntax

```c
int cpu;

cpu = smp_processor_id();
```

### Purpose

Returns the logical CPU number of the processor currently executing the code.

Example:

```text
CPU0
CPU1
CPU2
CPU3
```

If the code is executing on CPU1:

```c
cpu = smp_processor_id();
```

returns:

```text
1
```

---

## Important Note

A task may migrate from one CPU to another if preemption is enabled.

For safe usage:

```c
preempt_disable();

cpu = smp_processor_id();

preempt_enable();
```

or

```c
cpu = get_cpu();

/* critical section */

put_cpu();
```

---

## Related SMP APIs

### Number of Online CPUs

```c
num_online_cpus();
```

Returns the number of CPUs currently online.

### Number of Possible CPUs

```c
num_possible_cpus();
```

Returns the maximum number of CPUs the kernel may use.

### Number of Present CPUs

```c
num_present_cpus();
```

Returns the number of CPUs physically present in the system.

---

## Expected Learning Outcome

After completing this experiment, you should be able to:

* Understand SMP architecture.
* Use `smp_processor_id()` in kernel modules.
* Identify the CPU executing kernel code.
* Build, load, and unload Linux kernel modules.
* Understand CPU-related kernel APIs.

---

## Author

Sethu Raj

Linux Kernel Programming Practice
