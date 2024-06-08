
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

int device_ioremap(Hello_Device_T this, void* virt_addr, unsigned long phys_addr, unsigned long size)
{
    virt_addr = ioremap(phys_addr, size);
    if (IS_ERR(virt_addr)) {
        printk(KERN_ERR "ioremap failed with %ld\n", PTR_ERR(virt_addr));
        resource_recycle(this, IOREMAP_ERROR);
        return PTR_ERR(this->virt_registers.virt_register_base);
    }
    return 0;
}

int device_iounmap(Hello_Device_T this, void* virt_addr)
{
    iounmap(virt_addr);
    return 0;
}
int device_exit(Hello_Device_T this)
{
    device_iounmap(this, this->virt_registers.virt_register_base);
    resource_recycle(this, IOREMAP_ERROR);
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
    this->functions_pointer.class_dev_register = class_dev_register;
    this->functions_pointer.device_ioremap = device_ioremap;
    this->functions_pointer.device_iounmap = device_iounmap;
    this->functions_pointer.device_exit = device_exit;
    return 0;
}
