
#include "drv_define.h"
#include "linux/err.h"
#include "linux/gfp.h"
#include "linux/kdev_t.h"
#include "linux/kern_levels.h"
#include "linux/printk.h"
#include <asm/io.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/slab.h>

ssize_t device_write(struct file* file_t, const char __user* u_buffer, size_t size, loff_t* offset)
{
    // TODO fix this!!
    return 0;
}

ssize_t device_read(struct file* file_t, char __user* u_buffer, size_t size, loff_t* offset)
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
void resource_recycle(Hello_Device_T this, Enum_Name recycle_type)
{
    switch (recycle_type) {
    case KMALLOC_DEVICE_ERROR:
        break;

    case CHR_DEV_REGISTER_ERROR:
        kfree(this);
        break;
    case CLASS_REGISTER_ERROR:
        unregister_chrdev(this->dev_major, this->chr_dev_name);
        kfree(this);
        break;
    case DEVICE_REGISTER_ERROR:
        class_destroy(this->class_dev.cls);
        unregister_chrdev(this->dev_major, this->chr_dev_name);
        kfree(this);
        break;
    case IOREMAP_ERROR:
        device_destroy(this->class_dev.cls, MKDEV(this->dev_major, this->dev_minor));
        class_destroy(this->class_dev.cls);
        unregister_chrdev(this->dev_major, this->chr_dev_name);
        kfree(this);

        break;
    default:
        break;
    }
}
int chr_dev_register(Hello_Device_T this)
{
    this->dev_major = register_chrdev(this->dev_major, this->chr_dev_name, this->fops);
    if (this->dev_major < 0) {
        printk(KERN_ERR "register_chrdev failed with %d\n", this->dev_major);
        resource_recycle(this, CHR_DEV_REGISTER_ERROR);
        return -ENODEV;
    }
    return 0;
}

int device_init(Hello_Device_T this, int flags)
{
    // Initialize the device here
    this = kmalloc(sizeof(*this), GFP_KERNEL);
    if (this == NULL) {
        printk(KERN_ERR "Failed to allocate memory for device\n");
        resource_recycle(this, KMALLOC_DEVICE_ERROR);
        return -ENOMEM;
    }
    this->dev_major = 0;
    this->dev_minor = 0;

    this->fops = &device_fops;
    this->functions_pointer.resource_recycle = resource_recycle;
    this->functions_pointer.chr_dev_register = chr_dev_register;

    return 0;
}

int class_dev_register(Hello_Device_T this)
{
    this->class_dev.cls = class_create(THIS_MODULE, this->class_name);
    if (IS_ERR(this->class_dev.cls)) {
        printk(KERN_ERR "class_create failed with %ld\n", PTR_ERR(this->class_dev.cls));
        resource_recycle(this, CLASS_REGISTER_ERROR);
        return PTR_ERR(this->class_dev.cls);
    }
    this->class_dev.dev = device_create(this->class_dev.cls, NULL, MKDEV(this->dev_major, this->dev_minor), NULL, this->chr_dev_name);
    if (IS_ERR(this->class_dev.dev)) {
        printk(KERN_ERR "device_create failed with %ld\n", PTR_ERR(this->class_dev.dev));
        resource_recycle(this, DEVICE_REGISTER_ERROR);
        return PTR_ERR(this->class_dev.dev);
    }
    return 0;
}

int device_ioremap(Hello_Device_T this, unsigned long phys_addr, unsigned long size)
{
    this->virt_registers.virt_register_base = ioremap(this->registers.register_base, sizeof(this->registers.register_base));
    if (IS_ERR(this->virt_registers.virt_register_base)) {
        printk(KERN_ERR "ioremap failed with %ld\n", PTR_ERR(this->virt_registers.virt_register_base));
        resource_recycle(this, IOREMAP_ERROR);
        return PTR_ERR(this->virt_registers.virt_register_base);
    }
    return 0;
}
