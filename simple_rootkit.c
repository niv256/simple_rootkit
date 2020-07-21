#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define DRIVER_NAME "simple_rootkit"
#define DRIVER_AUTHOR "Niv Meiran and Tal Gorbunov"
#define DRIVER_DESC "A simple, multi-functional, linux rootkit"
#define DRIVER_LICENSE "GPL"

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

static int __init rootkit_init(void) {
	printk(KERN_INFO "[+] Module loaded, inside %s.\n", __FUNCTION__);
	return 0;
}

static void __exit rootkit_exit(void) {
	printk(KERN_INFO "[-] Module unloaded, inside %s.\n", __FUNCTION__);
	return;
}

module_init(rootkit_init);
module_exit(rootkit_exit);
