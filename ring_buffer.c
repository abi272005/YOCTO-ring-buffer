#include <linux/module.h>
#include <linux/init.h>
#include "ring_buffer.h"

static struct ring_buffer rb;

static int __init rb_test_init(void)
{
    int ret;
    char ch;

    printk(KERN_INFO "Ring Buffer Test: Initializing...\n");

    ret = ring_buffer_init(&rb, 8);
    if (ret) {
        printk(KERN_ERR "Failed to allocate ring buffer\n");
        return ret;
    }

    ring_buffer_push(&rb, 'A');
    ring_buffer_push(&rb, 'B');
    ring_buffer_push(&rb, 'C');

    ring_buffer_pop(&rb, &ch);
    printk(KERN_INFO "Popped: %c\n", ch);
    ring_buffer_pop(&rb, &ch);
    printk(KERN_INFO "Popped: %c\n", ch);

    return 0;
}

static void __exit rb_test_exit(void)
{
    ring_buffer_free(&rb);
    printk(KERN_INFO "Ring Buffer Test: Exited.\n");
}

module_init(rb_test_init);
module_exit(rb_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mr_beast");
MODULE_DESCRIPTION("Dynamic memory Ring Buffer for Yocto-based kernel modules");
