# RW Spinlock Demo

## Objective

Demonstrate Read-Write Spinlocks in Linux Kernel.

## Concepts Covered

- rwlock_t
- read_lock()
- read_unlock()
- write_lock()
- write_unlock()

## Working

Two reader threads continuously read a shared variable.

One writer thread periodically updates the variable.

Multiple readers can execute simultaneously.

Only one writer can modify data.

## Build

```bash
make
```

## Insert

```bash
sudo insmod rw_spinlock_demo.ko
```

## View Output

```bash
dmesg -w
```

## Remove

```bash
sudo rmmod rw_spinlock_demo
```

## Important

RW Spinlocks:

- Allow multiple readers
- Allow only one writer
- Busy wait
- Cannot sleep
- Suitable for short critical sections

##AUTHOR
SETHU RAJ

