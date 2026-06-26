# RW Semaphore Demo

## Objective

Demonstrate Read-Write Semaphores in Linux Kernel.

## Concepts Covered

- struct rw_semaphore
- down_read()
- up_read()
- down_write()
- up_write()

## Working

Two reader threads continuously read shared data.

One writer thread updates shared data.

Readers can execute simultaneously.

Writer gets exclusive access.

Unlike RW Spinlocks, sleeping is allowed.

## Build

```bash
make
```

## Insert

```bash
sudo insmod rw_semaphore_demo.ko
```

## View Output

```bash
dmesg -w
```

## Remove

```bash
sudo rmmod rw_semaphore_demo
```

## Important

RW Semaphores:

- Multiple readers allowed
- One writer allowed
- Sleeping allowed
- Process context only
- Suitable for long critical sections

## APIs Used

```c
down_read()
up_read()

down_write()
up_write()
```

##AUTHOR

SETHU RAJ
