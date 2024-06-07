#include <linux/init.h> // Needed for the macros
#include <linux/module.h> // Needed for all kernel modules
#include "drv_define.h"

// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Frank Wang Module");
MODULE_DESCRIPTION("A simple Hello World kernel module");
MODULE_VERSION("1.0");

// Function called when the module is loaded


static Hello_Device_T hello_device_t;




static int __init hello_init(void)
{
    printk(KERN_INFO "Hello, world!\n");
    return 0; // Return 0 indicates successful load
}

// Function called when the module is removed
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
}

// Macros to register the above functions as module entry and exit points
module_init(hello_init);
module_exit(hello_exit);
