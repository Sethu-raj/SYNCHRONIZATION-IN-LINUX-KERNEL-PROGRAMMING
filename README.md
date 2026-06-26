# Linux Kernel Synchronization Programming

## Overview

This repository contains Linux Kernel Module (LKM) examples demonstrating various synchronization mechanisms used in Linux kernel programming.

The examples are designed for learning Linux Device Drivers and cover synchronization primitives used to safely access shared resources in multi-threaded and multi-core environments.

Each topic includes:

- Theory
- Kernel module source code
- Makefile
- Individual README.md
- Sample execution

---

# Topics Covered

## 1. SMP Basics

- NR_CPUS
- num_online_cpus()
- smp_processor_id()

Purpose:

Learn how Linux identifies CPUs and executes code on multiprocessor systems.

---

## 2. Per-CPU Variables

Topics:

- Static Per-CPU arrays
- DEFINE_PER_CPU()
- DECLARE_PER_CPU()
- get_cpu_var()
- put_cpu_var()

Purpose:

Avoid synchronization by giving each CPU its own copy of data.

---

## 3. Atomic Operations

Topics:

- atomic_t
- atomic64_t
- atomic_inc()
- atomic_dec()
- atomic_add()
- atomic_sub()
- atomic_read()
- Atomic Bit Operations

Purpose:

Protect simple shared variables without using locks.

---

## 4. Spinlocks

Topics:

- spin_lock()
- spin_unlock()
- spin_trylock()
- spin_lock_irqsave()
- spin_unlock_irqrestore()

Purpose:

Protect short critical sections where sleeping is not allowed.

---

## 5. Semaphores

Topics:

- Counting Semaphore
- Binary Semaphore
- down()
- down_interruptible()
- down_trylock()
- down_killable()
- up()

Purpose:

Protect long critical sections where sleeping is allowed.

---

## 6. Mutex

Topics:

- mutex_init()
- mutex_lock()
- mutex_lock_interruptible()
- mutex_trylock()
- mutex_unlock()

Purpose:

Provide mutual exclusion in process context.

---

## 7. Read-Write Locks

### RW Spinlock

- read_lock()
- read_unlock()
- write_lock()
- write_unlock()

### RW Semaphore

- down_read()
- up_read()
- down_write()
- up_write()

Purpose:

Allow multiple readers while providing exclusive access to writers.

---

## 8. Sequential Locks (Seqlock)

Topics:

- seqlock_t
- read_seqbegin()
- read_seqretry()
- write_seqlock()
- write_sequnlock()

Purpose:

Provide fast lock-free readers with retry support.

---

## 9. Read-Copy-Update (RCU)

Topics:

- rcu_read_lock()
- rcu_read_unlock()
- rcu_dereference()
- rcu_assign_pointer()
- synchronize_rcu()

Purpose:

Provide lock-free readers and safe pointer updates.

---

# Repository Structure

```text
SYNCHRONIZATION/

├── SMP/
│
├── PER_CPU/
│
├── ATOMIC_OPERATIONS/
│
├── SPINLOCK/
│
├── SEMAPHORE/
│
├── MUTEX/
│
├── READWRITELOCKS/
│
├── SEQLOCK/
│
├── RCU/
│
└── README.md
```

---

# Build

Navigate to any example directory.

```bash
make
```

---

# Insert Module

```bash
sudo insmod <module_name>.ko
```

Example:

```bash
sudo insmod spinlock_demo.ko
```

---

# View Output

```bash
dmesg -w
```

---

# Remove Module

```bash
sudo rmmod <module_name>
```

Example:

```bash
sudo rmmod spinlock_demo
```

---

# Synchronization Comparison

| Mechanism | Sleeps | Busy Wait | Multiple Readers | Best Use |
|------------|---------|-----------|------------------|-----------|
| Atomic Operations | No | No | N/A | Counters, Flags |
| Spinlock | No | Yes | No | Short Critical Sections |
| Semaphore | Yes | No | Depends on Count | Resource Management |
| Mutex | Yes | No | No | Mutual Exclusion |
| RW Spinlock | No | Yes | Yes | Read-Mostly Data |
| RW Semaphore | Yes | No | Yes | Long Read Operations |
| Seqlock | No | Reader Retries | Yes | Small Read-Mostly Data |
| RCU | No (Readers) | No | Yes | Read-Heavy Pointer-Based Data |

---

# Learning Outcomes

After completing these examples, you will understand:

- Linux SMP concepts
- CPU affinity
- Per-CPU variables
- Atomic operations
- Spinlocks
- Semaphores
- Mutexes
- Read-Write Locks
- Sequential Locks
- Read-Copy-Update (RCU)
- Critical sections
- Race conditions
- Locking strategies in Linux kernel programming

---

# Requirements

- Ubuntu Linux
- Linux Kernel Headers
- GCC
- Make
- Root privileges

Install kernel headers:

```bash
sudo apt install linux-headers-$(uname -r)
```

---

# References

- Linux Kernel Documentation
- Linux Device Drivers (LDD3)
- Linux Kernel Source Code
- Kernel Documentation (Documentation/ directory)

---

# Author

**SETHU RAJ**

Linux Kernel & Embedded Systems Learning Repository

---

# License

This project is intended for educational purposes and is released under the GPL License.
