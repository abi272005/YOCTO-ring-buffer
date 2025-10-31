#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <linux/slab.h>   // for kmalloc, kfree
#include <linux/spinlock.h>

struct ring_buffer {
    char *buffer;
    size_t size;
    size_t head;
    size_t tail;
    spinlock_t lock;
};

// Initialize ring buffer with given size
static inline int ring_buffer_init(struct ring_buffer *rb, size_t size)
{
    rb->buffer = kmalloc(size, GFP_KERNEL);
    if (!rb->buffer)
        return -ENOMEM;

    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
    spin_lock_init(&rb->lock);
    return 0;
}

// Free allocated memory
static inline void ring_buffer_free(struct ring_buffer *rb)
{
    kfree(rb->buffer);
    rb->buffer = NULL;
    rb->size = rb->head = rb->tail = 0;
}

// Check if buffer is full
static inline int ring_buffer_is_full(struct ring_buffer *rb)
{
    return ((rb->head + 1) % rb->size) == rb->tail;
}

// Check if buffer is empty
static inline int ring_buffer_is_empty(struct ring_buffer *rb)
{
    return rb->head == rb->tail;
}

// Push one byte into buffer
static inline int ring_buffer_push(struct ring_buffer *rb, char data)
{
    unsigned long flags;
    spin_lock_irqsave(&rb->lock, flags);

    if (ring_buffer_is_full(rb)) {
        spin_unlock_irqrestore(&rb->lock, flags);
        return -ENOSPC; // No space
    }

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->size;

    spin_unlock_irqrestore(&rb->lock, flags);
    return 0;
}

// Pop one byte from buffer
static inline int ring_buffer_pop(struct ring_buffer *rb, char *data)
{
    unsigned long flags;
    spin_lock_irqsave(&rb->lock, flags);

    if (ring_buffer_is_empty(rb)) {
        spin_unlock_irqrestore(&rb->lock, flags);
        return -ENOENT; // No data
    }

    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;

    spin_unlock_irqrestore(&rb->lock, flags);
    return 0;
}

#endif // RING_BUFFER_H
