# Counting Semaphore Demo

## Objective

This module demonstrates the use of a **Counting Semaphore** in the Linux Kernel.

Unlike a Binary Semaphore, a Counting Semaphore allows multiple threads to access a shared resource simultaneously.

In this example:

* Semaphore Count = 3
* Number of Threads = 5

Only three threads can enter the critical section at the same time.

---

## Concepts Covered

* Counting Semaphore
* `sema_init()`
* `down()`
* `up()`
* Kernel Threads
* Resource Limiting
* Wait Queue
* Sleeping Synchronization

---

## Files

```text
counting_semaphore_demo.c
Makefile
README.md
```

---

## Semaphore Initialization

```c
sema_init(&sem, 3);
```

This means:

```text
Maximum 3 threads can access
the resource simultaneously.
```

---

## Working

Five kernel threads are created.

### First Three Threads

```text
Thread-1 Acquired
Thread-2 Acquired
Thread-3 Acquired
```

They enter the critical section immediately.

### Remaining Threads

```text
Thread-4 Waiting
Thread-5 Waiting
```

These threads are placed into the semaphore wait queue.

When one of the first three threads releases the semaphore:

```text
Thread-1 Releases
        ↓
Thread-4 Acquires
```

The waiting thread is awakened automatically.

---

## Build

```bash
make
```

---

## Insert Module

```bash
sudo insmod counting_semaphore_demo.ko
```

---

## View Output

```bash
dmesg -w
```

Example Output:

```text
Thread-1: Acquired semaphore
Thread-2: Acquired semaphore
Thread-3: Acquired semaphore

Thread-4: Waiting for semaphore
Thread-5: Waiting for semaphore

Thread-1: Releasing semaphore
Thread-4: Acquired semaphore

Thread-2: Releasing semaphore
Thread-5: Acquired semaphore
```

---

## Remove Module

```bash
sudo rmmod counting_semaphore_demo
```

---

## Clean

```bash
make clean
```

---

## Binary vs Counting Semaphore

| Binary Semaphore   | Counting Semaphore    |
| ------------------ | --------------------- |
| Count = 1          | Count = N             |
| One Thread Allowed | N Threads Allowed     |
| Mutual Exclusion   | Resource Management   |
| Similar to Mutex   | Resource Pool Control |

---

## Real World Examples

Counting Semaphores are used for:

* DMA Channel Pools
* Buffer Pools
* Connection Pools
* Hardware Resource Pools
* Shared Resource Management

---

## Conclusion

This example demonstrates how a Counting Semaphore controls access to a limited number of resources. Multiple threads can enter simultaneously until the semaphore count reaches zero. Additional threads are blocked and placed into a wait queue until resources become available.

##AUTHOR
SETHU RAJ

