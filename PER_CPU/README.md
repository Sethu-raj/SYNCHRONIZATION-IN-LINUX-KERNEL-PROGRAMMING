# Per-CPU Variables Demo

## Overview

This Linux Kernel Module demonstrates the use of Per-CPU Variables using the Linux kernel API:

```c
DEFINE_PER_CPU()
```

Each CPU maintains its own private copy of the variable, eliminating race conditions and reducing synchronization overhead.

---

## Objective

* Understand Per-CPU Variables.
* Learn how to declare and access Per-CPU data.
* Understand why Per-CPU variables improve performance in SMP systems.

---

## APIs Used

### Declare Per-CPU Variable

```c
DEFINE_PER_CPU(int, cpu_counter);
```

Creates a separate copy of `cpu_counter` for every CPU.

### Increment Current CPU Variable

```c
this_cpu_inc(cpu_counter);
```

### Read Current CPU Variable

```c
this_cpu_read(cpu_counter);
```

### Access Specific CPU Variable

```c
per_cpu(cpu_counter, cpu);
```

---

## Build Instructions

Compile:

```bash
make
```

Load:

```bash
sudo insmod percpu_demo.ko
```

View Output:

```bash
dmesg | tail -10
```

Remove:

```bash
sudo rmmod percpu_demo
```

---

## Sample Output

```text
Current CPU = 2
CPU 2 Counter = 1
```

Module Removal:

```text
Per CPU Counter Values:
CPU 0 -> 0
CPU 1 -> 0
CPU 2 -> 1
CPU 3 -> 0
```

---

## Advantages of Per-CPU Variables

* No race conditions.
* No locking required.
* Reduced cache contention.
* Better SMP scalability.

---

## Learning Outcome

After completing this experiment, you will understand how Linux uses Per-CPU variables to improve performance and avoid synchronization overhead.
