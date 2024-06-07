#include "asm-generic/errno.h"
#include "drv_define.h"
#include "linux/gfp.h"
#include "linux/kern_levels.h"
#include <linux/fs.h>
#include <linux/slab.h>

ssize_t device_write(struct file*, const char __user*, size_t, loff_t*)
{
    // TODO fix this!!
    return 0;
}

ssize_t device_read(struct file*, char __user*, size_t, loff_t*)
{
    // TODO fix this!!
    return 0;
}

static const struct file_operations device_fops = {
    .owner = THIS_MODULE,
    .read = device_read,
    .write = device_write,
    // ... 其他操作函数 ...
};
void resource_recycle(Hello_Device_T this, int recycle_type)
{
    
    // TODO fix this!!
}
int chr_dev_register(Hello_Device_T this)
{
    // TODO fix this!!
}

int device_init(Hello_Device_T this, int flags)
{
    // Initialize the device here
    this = kmalloc(sizeof(*this), GFP_KERNEL);
    if (this == NULL) {
        printk(KERN_ERR "Failed to allocate memory for device\n");
        return -ENOMEM;
    }
    this->dev_major = 0;
    this->dev_minor = 0;

    this->fops = &device_fops;
    this->functions_pointer.resource_recycle = resource_recycle;
    this->functions_pointer.chr_dev_register = chr_dev_register;

    return 0;
}
