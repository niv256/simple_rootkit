obj-m += rootkit.o
rootkit-objs := simple_rootkit.o fops.o keylogger.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
