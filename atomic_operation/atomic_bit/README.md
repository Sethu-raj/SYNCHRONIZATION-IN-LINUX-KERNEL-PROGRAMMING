# Atomic Bit Operations Kernel Module

## Overview

This Linux Kernel Module demonstrates the use of **Atomic Bit Operations** provided by the Linux kernel.

Atomic bit operations allow individual bits within a variable to be manipulated safely in multiprocessor (SMP) environments without race conditions.

These operations are commonly used for:

* Device status flags
* Driver state management
* Resource tracking
* Lock-free synchronization

---

## Objective

* Understand bit-level synchronization.
* Learn atomic bit manipulation APIs.
* Understand how status flags are implemented in the Linux kernel.
* Observe atomic bit operations through kernel logs.

---

## Header File

```c
#include <linux/bitops.h>
```

---

## Why Atomic Bit Operations?

Consider a status variable:

```c
unsigned long flags = 0;
```

Example bit assignments:

```text
Bit 0 -> Device Open
Bit 1 -> Device Busy
Bit 2 -> Data Available
Bit 3 -> Error State
```

Multiple CPUs may attempt to modify these bits simultaneously.

Atomic bit operations ensure safe access without race conditions.

---

## APIs Demonstrated

### set_bit()

Sets a bit atomically.

```c
set_bit(0, &flags);
```

---

### clear_bit()

Clears a bit atomically.

```c
clear_bit(0, &flags);
```

---

### change_bit()

Toggles a bit atomically.

```c
change_bit(1, &flags);
```

---

### test_bit()

Checks whether a bit is set.

```c
test_bit(0, &flags);
```

Returns:

```text
1 -> Bit Set
0 -> Bit Clear
```

---

### test_and_set_bit()

Atomically:

```text
1. Tests the bit
2. Sets the bit
```

Returns the previous value.

```c
test_and_set_bit(3, &flags);
```

---

### test_and_clear_bit()

Atomically:

```text
1. Tests the bit
2. Clears the bit
```

Returns the previous value.

```c
test_and_clear_bit(2, &flags);
```

---

## Source File

### atomic_bitops.c

The module demonstrates various atomic bit manipulation APIs and prints the results in the kernel log.

---

## Build Instructions

Compile the module:

```bash
make
```

Generated Output:

```text
atomic_bitops.ko
```

---

## Load the Module

Insert the module:

```bash
sudo insmod atomic_bitops.ko
```

---

## Verify Output

Check kernel logs:

```bash
dmesg | tail -20
```

Example Output:

```text
===== Atomic Bit Operations Demo =====

Initial flags = 0

After set_bit(0)       = 1

After set_bit(2)       = 5

Bit 0 is SET

After clear_bit(0)     = 4

After change_bit(1)    = 6

Old value of bit3 = 0

After test_and_set_bit(3) = e

Old value of bit2 = 1

After test_and_clear_bit(2) = a

======================================
```

---

## Remove the Module

Unload the module:

```bash
sudo rmmod atomic_bitops
```

Verify:

```bash
dmesg | tail -5
```

Example Output:

```text
Atomic Bit Operations Module Removed
```

---

## Atomic Bit Operations Summary

| API                     | Description           |
| ----------------------- | --------------------- |
| `set_bit()`             | Set a bit             |
| `clear_bit()`           | Clear a bit           |
| `change_bit()`          | Toggle a bit          |
| `test_bit()`            | Check a bit           |
| `test_and_set_bit()`    | Test and set a bit    |
| `test_and_clear_bit()`  | Test and clear a bit  |
| `test_and_change_bit()` | Test and toggle a bit |

---

## Atomic Integer vs Atomic Bit Operations

| Atomic Integer            | Atomic Bit Operations       |
| ------------------------- | --------------------------- |
| `atomic_t`                | Bit Operations              |
| Operates on whole integer | Operates on individual bits |
| Used for counters         | Used for flags              |
| `atomic_inc()`            | `set_bit()`                 |
| `atomic_dec()`            | `clear_bit()`               |

---

## Advantages

* Prevents race conditions.
* No explicit locks required.
* Efficient for flag management.
* Suitable for SMP systems.
* Low synchronization overhead.

---

## Common Use Cases

* Device state flags
* Driver status information
* Resource allocation tracking
* Interrupt status flags
* Lock-free synchronization mechanisms

---

## Learning Outcome

After completing this experiment, you will be able to:

* Understand atomic bit-level synchronization.
* Use Linux kernel bit manipulation APIs.
* Implement status flags safely in SMP systems.
* Differentiate between atomic integer operations and atomic bit operations.

---

## Author

Sethu Raj

Linux Kernel Programming Practice
