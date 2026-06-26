# Semaphore Demo in Linux Kernel

## Objective

This module demonstrates the use of a **Binary Semaphore** in the Linux Kernel.

The example creates two kernel threads that compete for a shared semaphore. One thread acquires the semaphore and sleeps for a few seconds, while the other thread waits until the semaphore is released.

This demonstrates that semaphores use a **sleep-and-wakeup mechanism** instead of busy waiting.

---

## Concepts Covered

* Binary Semaphore
* `sema_init()`
* `down()`
* `up()`
* Kernel Threads
* `msleep()`
* Critical Sections
* Process Context Synchronization

---

## Files

```text
semaphore_demo.c
Makefile
README.md
```

---

## Semaphore Initialization

```c
static struct semaphore sem;

sema_init(&sem, 1);
```

A value of `1` creates a Binary Semaphore.

Only one thread can enter the critical section at a time.

---

## Working

### Thread 1

1. Acquires the semaphore using `down()`.
2. Enters the critical section.
3. Sleeps for 5 seconds.
4. Releases the semaphore using `up()`.

### Thread 2

1. Attempts to acquire the semaphore.
2. Since Thread 1 already owns it, Thread 2 goes to sleep.
3. When Thread 1 releases the semaphore, Thread 2 wakes up.
4. Enters the critical section.
5. Releases the semaphore.

---

## Build the Module

```bash
make
```

---

## Insert the Module

```bash
sudo insmod semaphore_demo.ko
```

---

## View Kernel Messages

```bash
dmesg -w
```

Expected Output:

```text
Semaphore Module Loaded

Thread1: Waiting for semaphore
Thread1: Acquired semaphore

Thread2: Waiting for semaphore

Thread1: Releasing semaphore

Thread2: Acquired semaphore

Thread2: Releasing semaphore
```

---

## Remove the Module

```bash
sudo rmmod semaphore_demo
```

---

## Clean Build Files

```bash
make clean
```

---

## Important Notes

### Semaphore Allows Sleeping

The following is valid:

```c
down(&sem);

msleep(5000);

up(&sem);
```

Semaphores are suitable for long critical sections.

---

### Process Context Only

Semaphores can be used in:

* Read Functions
* Write Functions
* IOCTL Handlers
* Kernel Threads

---

### Not Allowed in Interrupt Context

Interrupt handlers cannot sleep.

Therefore:

```c
down(&sem);
```

must never be called inside an ISR.

---

## Semaphore vs Spinlock

| Semaphore              | Spinlock                |
| ---------------------- | ----------------------- |
| Sleeping Lock          | Busy-Wait Lock          |
| Long Critical Sections | Short Critical Sections |
| Sleeping Allowed       | Sleeping Not Allowed    |
| Process Context Only   | Can Be Used in ISR      |
| Better CPU Utilization | CPU Busy Waiting        |

---

## Conclusion

This example demonstrates how a semaphore protects a shared resource while allowing waiting threads to sleep. It highlights the key advantage of semaphores over spinlocks for long-duration critical sections.
