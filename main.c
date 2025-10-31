#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "ring_buffer.h" // Your header file

MODULE_LICENSE("MIT"); // Use the same license as your repo
MODULE_AUTHOR("abc12005");
MODULE_DESCRIPTION("Yocto Ring Buffer Kernel Module");

// A test buffer pointer
static struct ring_buffer *test_rb;

static int __init ringbuffer_mod_init(void) {
    pr_info("Ring buffer module loading...\n");
    
    // Initialize your ring buffer (e.g., with 1024 bytes)
    test_rb = ring_buffer_init(1024);
    if (!test_rb) {
        pr_err("Failed to initialize ring buffer\n");
        return -ENOMEM;
    }

    pr_info("Ring buffer initialized successfully.\n");
    // You can add other function calls here to test
    
    return 0; // 0 indicates success
}

static void __exit ringbuffer_mod_exit(void) {
    // Free the memory on exit
    if (test_rb) {
        ring_buffer_free(test_rb);
    }
    pr_info("Ring buffer module unloaded.\n");
}

module_init(ringbuffer_mod_init);
module_exit(ringbuffer_mod_exit);
