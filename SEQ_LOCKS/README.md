# Sequential Lock (Seqlock) Demo

## Objective

This module demonstrates the working of **Sequential Locks (Seqlocks)** in the Linux kernel.

It shows how:

- Multiple readers can read shared data without blocking.
- Writers obtain exclusive access while updating shared data.
- Readers automatically retry if the data changes during a read.

---

## Concepts Covered

- seqlock_t
- Reader retry mechanism
- Writer exclusive access
- Sequence counter
- Reader and Writer kernel threads

---

## APIs Used

### Initialization

```c
seqlock_init()
```

### Reader APIs

```c
read_seqbegin()
read_seqretry()
```

### Writer APIs

```c
write_seqlock()
write_sequnlock()
```

---

## Program Workflow

### Reader Thread

1. Start reading using `read_seqbegin()`.
2. Read the shared variable.
3. Verify whether a writer modified the data using `read_seqretry()`.
4. If the sequence changed, retry the read.
5. Otherwise, print the value.

```text
read_seqbegin()
      │
Read shared_data
      │
read_seqretry()
      │
No Retry? → Print Value
Retry?    → Read Again
```

---

### Writer Thread

Every 5 seconds:

1. Acquire the write lock.
2. Update the shared variable.
3. Release the write lock.

```text
write_seqlock()
      │
Update Data
      │
write_sequnlock()
```

---

## Build

```bash
make
```

---

## Insert Module

```bash
sudo insmod seqlock_demo.ko
```

---

## View Output

```bash
dmesg -w
```

---

## Sample Output

```text
Seqlock Demo Module Loaded

Reader-1 : shared_data = 0
Reader-2 : shared_data = 0

Writer : Updated shared_data = 1

Reader-1 : shared_data = 1
Reader-2 : shared_data = 1

Writer : Updated shared_data = 2

Reader-1 : shared_data = 2
Reader-2 : shared_data = 2
```

---

## Remove Module

```bash
sudo rmmod seqlock_demo
```

---

## Advantages

- Readers never block.
- Very fast for read-heavy workloads.
- Simple implementation.
- Low synchronization overhead.

---

## Limitations

- Readers may retry multiple times if writes are frequent.
- Not suitable for write-heavy workloads.
- Cannot protect data structures containing pointers that writers may free or replace.

---

## Applications

Seqlocks are commonly used for:

- System time (jiffies, clocks)
- Statistics
- Performance counters
- Frequently read kernel values

---

## Files

```text
seqlock_demo.c    -> Kernel module source
Makefile          -> Build script
README.md         -> Documentation
```

---

## Learning Outcome

After completing this program, you will understand:

- What a Seqlock is
- Why Seqlocks are used
- Reader retry mechanism
- Exclusive writer access
- Sequence counter concept
- Basic Seqlock APIs in the Linux kernel

---

## Conclusion

Sequential Locks (Seqlocks) provide an efficient synchronization mechanism for **read-mostly data**. Readers execute without blocking and only retry if a writer updates the data during the read operation. This makes Seqlocks suitable for protecting small shared data structures that are read frequently and updated infrequently.

##AUTHOR
SETHU RAJ
