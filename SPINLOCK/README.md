# Spinlock Shared Buffer Kernel Module

## Overview

This Linux Kernel Module demonstrates the use of **Spinlocks** to protect a shared buffer accessed concurrently by multiple kernel threads.

The module creates two kernel threads that write data into a shared buffer. A spinlock is used to ensure that only one thread can access and modify the shared buffer at a time, thereby preventing race conditions.

---

# Objective

* Understand the need for spinlocks.
* Learn how to protect a critical section.
* Prevent race conditions while accessing shared resources.
* Demonstrate synchronization between multiple kernel threads.
* Understand the use of `spin_lock()` and `spin_unlock()`.

---

# What Problem Does This Solve?

Consider two kernel threads accessing the same buffer:

```c
buffer[index_pos++] = value;
```

Without synchronization:

```text
Thread1 reads index_pos = 5
Thread2 reads index_pos = 5

Thread1 writes buffer[5]
Thread2 writes buffer[5]

One update is lost.
```

This results in a **Race Condition**.

To prevent this, Linux provides **Spinlocks**.

---

# What is a Spinlock?

A Spinlock is a synchronization mechanism that allows only one CPU or thread to enter a critical section at a time.

If another thread tries to acquire the lock while it is already held:

```text
Thread waits
     ↓
Checks lock repeatedly
     ↓
Acquires lock when available
```

This repeated checking is called **Busy Waiting (Spinning)**.

---

# Header File

```c
#include <linux/spinlock.h>
```

---

# Spinlock APIs Used

## Initialize Spinlock

```c
spin_lock_init(&buffer_lock);
```

Initializes the spinlock.

---

## Acquire Spinlock

```c
spin_lock(&buffer_lock);
```

Acquires the lock before entering the critical section.

If another thread already holds the lock, the current thread spins until the lock becomes available.

---

## Release Spinlock

```c
spin_unlock(&buffer_lock);
```

Releases the lock and allows other waiting threads to proceed.

---

# Shared Resources

The module protects the following shared resources:

```c
static int buffer[BUF_SIZE];
static int index_pos = 0;
```

These variables are accessed by multiple kernel threads and therefore require synchronization.

---

# Critical Section

```c
spin_lock(&buffer_lock);

if (index_pos < BUF_SIZE)
{
    buffer[index_pos++] = value;
}

spin_unlock(&buffer_lock);
```

Only one thread can execute this section at a time.

---

# Kernel Threads

The module creates two kernel threads:

```c
thread1
thread2
```

Each thread continuously attempts to write data into the shared buffer.

---

# Build Instructions

Compile the module:

```bash
make
```

Expected output:

```text
spinlock_buffer.ko
```

---

# Load the Module

Insert the module:

```bash
sudo insmod spinlock_buffer.ko
```

---

# Verify Output

Monitor kernel messages:

```bash
dmesg -w
```

Example Output:

```text
Spinlock Buffer Demo Loaded

Thread-1 -> Added 1, index=1
Thread-2 -> Added 2, index=2
Thread-1 -> Added 1, index=3
Thread-2 -> Added 2, index=4
Thread-1 -> Added 1, index=5
Thread-2 -> Added 2, index=6
```

---

# Remove the Module

Unload the module:

```bash
sudo rmmod spinlock_buffer
```

---

# Final Buffer Contents

Example:

```text
Final Buffer Contents:

buffer[0] = 1
buffer[1] = 2
buffer[2] = 1
buffer[3] = 2
buffer[4] = 1
buffer[5] = 2
buffer[6] = 1
buffer[7] = 2
buffer[8] = 1
buffer[9] = 2
```

---

# Advantages of Spinlocks

* Prevents race conditions.
* Simple synchronization mechanism.
* Very fast for short critical sections.
* No context switching overhead.
* Suitable for SMP systems.

---

# Limitations

* Busy waiting wastes CPU cycles.
* Not suitable for long critical sections.
* Sleeping while holding a spinlock can cause deadlocks.
* Blocking operations must not be performed inside spinlock-protected regions.

---

# Important Rules

### Rule 1: Never Sleep While Holding a Spinlock

Incorrect:

```c
spin_lock(&lock);

msleep(100);

spin_unlock(&lock);
```

---

### Rule 2: Keep Critical Sections Short

Correct:

```c
spin_lock(&lock);

counter++;

spin_unlock(&lock);
```

---

### Rule 3: Avoid Blocking Functions

Do not call:

```c
msleep()
schedule()
mutex_lock()
copy_to_user()
copy_from_user()
```

inside a spinlock protected section.

---

# Learning Outcome

After completing this experiment, you will be able to:

* Understand spinlock-based synchronization.
* Protect shared resources using spinlocks.
* Identify critical sections in kernel code.
* Prevent race conditions in SMP systems.
* Understand how kernel threads safely access shared data.

---

# Author

Sethu Raj

Linux Kernel Programming Practice
