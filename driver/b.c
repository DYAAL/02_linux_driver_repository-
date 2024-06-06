// #include "add.h"
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/module.h> /* Needed by all modules */
static int __init hello_init(void)
{
    int ret = 0;
    int a = 1;
    int b = 2;
    // ret = func_add(a, b);
    printk(KERN_INFO "Hello world.\n");
    /*
     * A non 0 return means init_module failed; module can't be loaded.
     */
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye world.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");