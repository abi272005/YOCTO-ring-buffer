# Yocto-Compatible Ring Buffer (Dynamic Allocation)

This project implements a simple, efficient ring buffer using dynamic memory allocation.
Designed for kernel-level and embedded use, compatible with Yocto build environments.

## Features
- Dynamic memory allocation with `kmalloc` and `kfree`
- Supports variable-size buffers
- Thread-safe (optional mutex lock can be added)
- Can be used in kernel modules or userspace (with `malloc`)

## Files
- `ring_buffer.c`: Implementation
- `ring_buffer.h`: Header definitions

## Build
```bash
make
