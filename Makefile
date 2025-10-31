# This tells the kernel build system we are building one module
# named "ringbuffer-mod.ko"
obj-m := ringbuffer-mod.o

# This tells the build system that "ringbuffer-mod.o" is made
# from two other C files: main.c and ring_buffer.c
ringbuffer-mod-objs := main.o ring_buffer.o

# Standard kernel module build commands
PWD := $(CURDIR)
KBUILD_DIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KBUILD_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KBUILD_DIR) M=$(PWD) clean
