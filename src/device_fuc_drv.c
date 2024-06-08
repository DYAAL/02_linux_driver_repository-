
#include "drv_define.h"
#include <asm/uaccess.h>
#include <linux/slab.h> // for kmalloc and kfree



ssize_t dummy_device_write(struct file* file_t, const void* k_buffer, size_t size, loff_t* offset)
{
    // This is a dummy function to simulate device write.
    // Replace this with actual device write logic.
    // For this example, we'll just simulate a write by returning the size.
    return size; // Simulate writing 'size' bytes
}

ssize_t device_write(struct file* file_t, const char __user* u_buffer, size_t size, loff_t* offset)
{
    void* k_buffer;
    ssize_t bytes_written;

    // Allocate kernel buffer
    k_buffer = kmalloc(size, GFP_KERNEL);
    if (!k_buffer) {
        return -ENOMEM; // Return error if allocation fails
    }

    // Copy data from user buffer to kernel buffer
    if (copy_from_user(k_buffer, u_buffer, size)) {
        kfree(k_buffer);
        return -EFAULT; // Return error if copy from user space fails
    }

    // Perform the actual write to the device (dummy write in this example)
    // This part should be replaced with actual device write logic
    bytes_written = dummy_device_write(file_t, k_buffer, size, offset);
    if (bytes_written < 0) {
        kfree(k_buffer);
        return bytes_written; // Return error if device write fails
    }

    // Free kernel buffer
    kfree(k_buffer);

    // Return number of bytes written
    return bytes_written;
}
// /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */ kernel write

ssize_t dummy_device_read(struct file* file_t, void* k_buffer, size_t size, loff_t* offset)
{
    // This is a dummy function to simulate device read.
    // Replace this with actual device read logic.
    // For this example, we'll just zero the buffer and simulate a read.
    memset(k_buffer, 0, size);
    return size; // Simulate reading 'size' bytes
}

ssize_t device_read(struct file* file_t, char __user* u_buffer, size_t size, loff_t* offset)
{
    void* k_buffer;
    ssize_t bytes_read;

    // Allocate kernel buffer
    k_buffer = kmalloc(size, GFP_KERNEL);
    if (!k_buffer) {
        return -ENOMEM; // Return error if allocation fails
    }

    // Perform the actual read from the device (dummy read in this example)
    // This part should be replaced with actual device read logic
    bytes_read = dummy_device_read(file_t, k_buffer, size, offset);
    if (bytes_read < 0) {
        kfree(k_buffer);
        return bytes_read; // Return error if device read fails
    }

    // Copy data from kernel buffer to user buffer
    if (copy_to_user(u_buffer, k_buffer, bytes_read)) {
        kfree(k_buffer);
        return -EFAULT; // Return error if copy to user space fails
    }

    // Free kernel buffer
    kfree(k_buffer);

    // Return number of bytes read
    return bytes_read;
}

// /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */ kernel read