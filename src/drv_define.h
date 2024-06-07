#ifndef __DRV_DEFINE_H__
#define __DRV_DEFINE_H__

#include "linux/types.h"
#include <linux/fs.h>

typedef enum {
    SUCCESS = 0,
    KMALLOC_DEVICE_ERROR = -1,
    CLASS_REGISTER_ERROR = -2,
    DEVICE_REGISTER_ERROR = -3,

} Enum_Name;

typedef struct {
    struct class* cls;
    struct device* dev;

} Class_Device, *Class_Device_T;

typedef struct {
    void* register_base;

} Registers, *Registers_T;

// 前向声明Hello_Device_T，以便在Functions_Pointer中使用
typedef struct Hello_Device* Hello_Device_T;

// 定义Functions_Pointer结构体，使用前向声明的Hello_Device_T
typedef struct {
    void (*resource_recycle)(Hello_Device_T this, Enum_Name recycle_type);
    int (*chr_class_register)(Hello_Device_T this);
    int (*chr_dev_register)(Hello_Device_T this);
} Functions_Pointer, *Functions_Pointer_T;

// 现在可以完整定义Hello_Device结构体了
typedef struct Hello_Device {
    unsigned int dev_major;
    unsigned int dev_minor;
    // 假设Class_Device和Registers类型已经定义
    Class_Device class_dev;
    Registers registers;
    Functions_Pointer functions_pointer;
    const struct file_operations* fops;
} Hello_Device, *Hello_Device_T; // 注意：这里的Hello_Device_T是重复的，但编译器通常允许

int device_init(Hello_Device_T this, int flags);
void resource_recycle(Hello_Device_T this, Enum_Name recycle_type);
int chr_dev_register(Hello_Device_T this);
#endif // __DRV_DEFINE_H__