# Mutex Demo in Linux Kernel

## Objective

This module demonstrates the use of a **Mutex** in the Linux Kernel.

The example creates two kernel threads that compete for a shared mutex. One thread acquires the mutex and enters the critical section, while the other thread waits until the mutex is released.

This demonstrates **Mutual Exclusion**, ensuring that only one thread accesses the shared resource at a time.

---

## Concepts Covered

* Mutex
* Mutual Exclusion
* `mutex_init()`
* `mutex_lock()`
* `mutex_unlock()`
* Kernel Threads
* Critical Sections
* Sleeping Locks

---

## Files

```text
mutex_demo.c
Makefile
README.md
```

---

## Mutex Initialization

```c
static struct mutex my_mutex;

mutex_init(&my_mutex);
```

A mutex can only be held by one thread at a time.

---

## Working

### Thread 1

1. Acquires the mutex using `mutex_lock()`.
2. Enters the critical section.
3. Sleeps for 5 seconds.
4. Releases the mutex using `mutex_unlock()`.

### Thread 2

1. Attempts to acquire the mutex.
2. Since Thread 1 already owns it, Thread 2 goes to sleep.
3. When Thread 1 releases the mutex, Thread 2 wakes up.
4. Acquires the mutex.
5. Executes its critical section.
6. Releases the mutex.

---

## Build the Module

```bash
make
```

---

## Insert the Module

```bash
sudo insmod mutex_demo.ko
```

---

## View Kernel Messages

```bash
dmesg -w
```

Expected Output:

```text
Mutex Module Loaded

Thread1: Waiting for mutex
Thread1: Acquired mutex

Thread2: Waiting for mutex

Thread1: Releasing mutex

Thread2: Acquired mutex

Thread2: Releasing mutex
```

---

## Remove the Module

```bash
sudo rmmod mutex_demo
```

---

## Clean Build Files

```bash
make clean
```

---

## Important Rules While Using Mutex

### 1. Process Context Only

Mutexes can be used in:

* System Calls
* Kernel Threads
* Read/Write Functions
* IOCTL Handlers

Mutexes cannot be used in:

* Interrupt Handlers (ISR)
* SoftIRQs
* Tasklets

Reason:

```text
Mutex may sleep.
Interrupt handlers cannot sleep.
```

---

### 2. Ownership Rule

The thread that acquires the mutex must release it.

Correct:

```text
Thread A -> mutex_lock()
Thread A -> mutex_unlock()
```

Incorrect:

```text
Thread A -> mutex_lock()
Thread B -> mutex_unlock()
```

---

### 3. No Recursive Locking

Wrong:

```c
mutex_lock(&my_mutex);
mutex_lock(&my_mutex);
```

Result:

```text
Deadlock
```

A thread cannot acquire the same mutex twice.

---

### 4. Sleeping is Allowed

Mutexes are sleeping locks.

Example:

```c
mutex_lock(&my_mutex);

msleep(5000);

mutex_unlock(&my_mutex);
```

This is valid.

---

## Mutex vs Semaphore

| Mutex                | Semaphore               |
| -------------------- | ----------------------- |
| Ownership Exists     | No Ownership            |
| Count = 1            | Count = N               |
| Mutual Exclusion     | Resource Counting       |
| Preferred in Drivers | Used for Resource Pools |
| Better Performance   | More Generic            |

---

## Advantages of Mutex

* Simple API
* Mutual Exclusion
* Ownership Tracking
* Better Debugging Support
* No Busy Waiting
* Preferred in Modern Linux Drivers

---

## Conclusion

This example demonstrates how a mutex protects a critical section and guarantees mutual exclusion. Only one thread can hold the mutex at a time, while other threads sleep until the mutex becomes available.

##AUTHOR
SETHU RAJ

