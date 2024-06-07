#ifndef __DRV_DEFINE_H__
#define __DRV_DEFINE_H__

#include <linux/fs.h>

typedef enum {
    SUCCESS = 0,
    KMALLOC_DEVICE_ERROR,
    CHR_DEV_REGISTER_ERROR,
    CLASS_REGISTER_ERROR,
    DEVICE_REGISTER_ERROR,
    IOREMAP_ERROR,

} Enum_Name;

typedef struct {
    struct class* cls;
    struct device* dev;

} Class_Device, *Class_Device_T;

typedef struct {
    unsigned int register_base;

} Registers, *Registers_T;

typedef struct {
    void* virt_register_base;

} Virt_Registers, *Virt_Registers_T;

// 前向声明Hello_Device_T，以便在Functions_Pointer中使用
typedef struct Hello_Device* Hello_Device_T;

// 定义Functions_Pointer结构体，使用前向声明的Hello_Device_T
typedef struct {
    void (*resource_recycle)(Hello_Device_T this, Enum_Name recycle_type);
    int (*chr_dev_register)(Hello_Device_T this);
    int (*class_dev_register)(Hello_Device_T this);
    int (*device_ioremap)(Hello_Device_T this, unsigned long phys_addr, unsigned long size);
    int (*device_iounmap)(Hello_Device_T this, void* virt_addr);
} Functions_Pointer, *Functions_Pointer_T;

// 现在可以完整定义Hello_Device结构体了
struct Hello_Device {
    unsigned int dev_major;
    unsigned int dev_minor;
    char* chr_dev_name;
    char* class_name;
    char* dev_name;
    // 假设Class_Device和Registers类型已经定义
    Class_Device class_dev;
    Registers registers;
    Virt_Registers virt_registers;
    Functions_Pointer functions_pointer;
    const struct file_operations* fops;
}; // 注意：这里的Hello_Device_T是重复的，但编译器通常允许

int device_init(Hello_Device_T this, int flags);
void resource_recycle(Hello_Device_T this, Enum_Name recycle_type);
int chr_dev_register(Hello_Device_T this);
int class_dev_register(Hello_Device_T this);
int device_ioremap(Hello_Device_T this, unsigned long phys_addr, unsigned long size);
#endif // __DRV_DEFINE_H__