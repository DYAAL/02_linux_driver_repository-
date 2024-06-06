ifeq ($(KERNELRELEASE),)
# Define the kernel source directory
KERNEL_DIR := /home/book/100ask_imx6ull-sdk/Linux-4.9.88
# Current directory
CRU_DIR := $(shell pwd)
# NFS directory for the target system
NFS_DIR := /home/book/remote/mnt_imx6ull

.PHONY: all clean install

# Build the kernel module
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(CRU_DIR) modules

# Clean the module build files
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(CRU_DIR) clean

# Install the module to the NFS directory
install:
	cp -rf *.ko $(NFS_DIR)

else
# If KERNELRELEASE is set, we are being called from the kernel build system
# Define the object file for the module
hello_drv-objs := hello.o
# Add the module to the list of modules to be built
obj-m += hello_drv.o

endif
