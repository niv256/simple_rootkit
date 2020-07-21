#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

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
