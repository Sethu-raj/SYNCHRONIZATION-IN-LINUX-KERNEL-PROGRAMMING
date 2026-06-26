# Atomic Operators Kernel Module

## Overview

This Linux Kernel Module demonstrates the usage of **Atomic Operations** in the Linux Kernel.

Atomic operations provide a lightweight synchronization mechanism for safely accessing and modifying shared variables in multiprocessor (SMP) systems without using spinlocks or mutexes.

The module illustrates common atomic APIs such as:

* `atomic_read()`
* `atomic_set()`
* `atomic_inc()`
* `atomic_dec()`
* `atomic_add()`
* `atomic_sub()`

---

## Objective

* Understand race conditions in shared variables.
* Learn why atomic operations are required.
* Understand the `atomic_t` data type.
* Learn common Linux kernel atomic APIs.
* Observe atomic variable manipulation through kernel logs.

---

## Header File

```c
#include <linux/atomic.h>
```

---

## Atomic Data Types

### 32-bit Atomic Variable

```c
atomic_t counter;
```

### 64-bit Atomic Variable

```c
atomic64_t counter64;
```

---

## Initialization

```c
atomic_t counter = ATOMIC_INIT(5);
```

or

```c
atomic_set(&counter, 5);
```

---

## APIs Demonstrated

### Read Value

```c
atomic_read(&counter);
```

Returns the current value of the atomic variable.

---

### Set Value

```c
atomic_set(&counter, 100);
```

Assigns a new value atomically.

---

### Increment

```c
atomic_inc(&counter);
```

Atomically increments the variable by 1.

---

### Decrement

```c
atomic_dec(&counter);
```

Atomically decrements the variable by 1.

---

### Add

```c
atomic_add(10, &counter);
```

Atomically adds 10 to the variable.

---

### Subtract

```c
atomic_sub(3, &counter);
```

Atomically subtracts 3 from the variable.

---

## Source File

### atomic_demo.c

The module initializes an atomic variable and performs various atomic operations while displaying the results in the kernel log.

---

## Build Instructions

Compile the module:

```bash
make
```

Generated Output:

```text
atomic_demo.ko
```

---

## Load the Module

Insert the module:

```bash
sudo insmod atomic_demo.ko
```

---

## Verify Output

Check kernel logs:

```bash
dmesg | tail -20
```

Example Output:

```text
===== Atomic Operations Demo =====

Initial Value = 5

After atomic_inc() = 6

After atomic_dec() = 5

After atomic_add(10) = 15

After atomic_sub(3) = 12

After atomic_set(100) = 100

==================================
```

---

## Remove the Module

Unload the module:

```bash
sudo rmmod atomic_demo
```

Verify:

```bash
dmesg | tail -5
```

Example Output:

```text
Atomic Demo Module Removed
```

---

## Why Atomic Operations?

Consider the following operation:

```c
counter++;
```

Internally this performs:

```text
1. Read counter
2. Increment value
3. Write back counter
```

If multiple CPUs execute this sequence simultaneously, race conditions can occur and updates may be lost.

Atomic operations ensure that the entire operation executes as a single indivisible unit.

---

## Advantages

* Prevents race conditions.
* No explicit lock management.
* Faster than spinlocks for simple counters.
* Low synchronization overhead.
* Suitable for SMP systems.

---

## Limitations

Atomic operations are suitable for:

* Counters
* Statistics
* Reference counts
* Status flags

Atomic operations are not suitable for:

* Multiple shared variables
* Large critical sections
* Complex synchronization requirements

In such cases, use:

* Spinlocks
* Mutexes
* Semaphores

---

## Atomic Operations vs Spinlocks

| Atomic Operations       | Spinlocks                |
| ----------------------- | ------------------------ |
| Protect single variable | Protect critical section |
| Fast                    | Slower                   |
| No lock/unlock required | Requires lock/unlock     |
| Low overhead            | Higher overhead          |

---

## Learning Outcome

After completing this experiment, you will be able to:

* Understand race conditions.
* Use atomic variables in Linux kernel modules.
* Apply atomic APIs safely in SMP environments.
* Distinguish between atomic operations and lock-based synchronization mechanisms.

---

## Author

Sethu Raj

Linux Kernel Programming Practice
