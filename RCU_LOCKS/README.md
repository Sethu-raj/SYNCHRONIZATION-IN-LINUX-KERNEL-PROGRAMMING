# RCU (Read-Copy-Update) Demo

## Objective

This module demonstrates the basic working of **RCU (Read-Copy-Update)** in the Linux kernel.

It shows how:
- Readers access shared data without blocking.
- Writers safely update shared data by creating a new copy.
- Old memory is freed only after all readers finish.

---

## Concepts Covered

- RCU synchronization
- Lock-free readers
- Pointer replacement
- Grace Period
- Reader and Writer kernel threads

---

## APIs Used

### Reader APIs

```c
rcu_read_lock()
rcu_dereference()
rcu_read_unlock()
```

### Writer APIs

```c
rcu_assign_pointer()
synchronize_rcu()
```

### Memory Management

```c
kmalloc()
kfree()
```

---

## Program Workflow

### Reader Thread

1. Enter RCU read-side critical section.
2. Read the shared pointer safely.
3. Print the current value.
4. Exit the RCU read-side critical section.
5. Sleep for 1 second.

```text
rcu_read_lock()
        │
rcu_dereference()
        │
Read Value
        │
rcu_read_unlock()
```

---

### Writer Thread

Every 5 seconds:

1. Allocate a new object.
2. Copy/modify the data.
3. Replace the global pointer.
4. Wait for all readers to finish.
5. Free the old object.

```text
kmalloc()
     │
Modify Data
     │
rcu_assign_pointer()
     │
synchronize_rcu()
     │
kfree(old_object)
```

---

## Build the Module

```bash
make
```

---

## Insert Module

```bash
sudo insmod rcu_demo.ko
```

---

## View Kernel Messages

```bash
dmesg -w
```

---

## Sample Output

```text
RCU Demo Module Loaded

Reader : value = 0
Reader : value = 0

Writer : updating value to 1

Reader : value = 1
Reader : value = 1

Writer : updating value to 2

Reader : value = 2
Reader : value = 2
```

---

## Remove Module

```bash
sudo rmmod rcu_demo
```

---

## Expected Behavior

- Multiple readers access the shared data concurrently.
- Readers never block each other.
- Writer creates a new object instead of modifying the existing one.
- Writer atomically updates the shared pointer.
- Old object is freed only after all readers have completed.

---

## RCU Workflow

```text
                Reader
                   │
          rcu_read_lock()
                   │
        Read Shared Pointer
                   │
        rcu_read_unlock()


                Writer
                   │
        Allocate New Object
                   │
          Modify New Object
                   │
      rcu_assign_pointer()
                   │
        synchronize_rcu()
                   │
          Free Old Object
```

---

## Advantages

- Lock-free readers
- Very fast read performance
- Excellent scalability on multicore systems
- Readers do not wait for writers
- Ideal for read-mostly workloads

---

## Limitations

- More complex than mutexes or spinlocks
- Writers are slower
- Requires additional memory during updates
- Not suitable for write-intensive workloads

---

## Applications

RCU is widely used in:

- Routing tables
- Kernel linked lists
- Process lists
- File descriptor tables
- Networking subsystem
- Virtual File System (VFS)

---

## Files

```text
rcu_demo.c      -> Kernel module source
Makefile        -> Build script
README.md       -> Documentation
```

---

## Learning Outcome

After completing this program, you will understand:

- What RCU is
- Why RCU is used
- How readers access data without locking
- How writers safely update shared data
- Grace Period
- Pointer replacement using RCU
- Basic RCU APIs in the Linux kernel

---

## Conclusion

RCU (Read-Copy-Update) is a high-performance synchronization mechanism designed for **read-mostly workloads**. It allows readers to execute with minimal overhead while writers safely update shared data by creating a new copy, updating the shared pointer atomically, waiting for a grace period, and then reclaiming the old memory.
##AUTHOR
SETHU RAJ
