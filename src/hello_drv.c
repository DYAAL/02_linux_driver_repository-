
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/module.h> /* Needed by all modules */
#include "add.h"
#include "linux/compiler.h"

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello world.\n");
    /*
     * A non 0 return means init_module failed; module can't be loaded.
     */
     __user
    int c = add(1, 2);
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye world.\n");

}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");