#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "simple_rootkit.h"
#include "fops.h"

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

static int __init rootkit_init(void) {
	printk(KERN_INFO "[+] Module loaded, inside %s.\n", __FUNCTION__);
	init_fops();
	return 0;
}

static void __exit rootkit_exit(void) {
	 printk(KERN_INFO "[-] Module unloaded, inside %s.\n", __FUNCTION__);
	 exit_fops();
	 return;
}

module_init(rootkit_init);
module_exit(rootkit_exit);
