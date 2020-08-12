ccflags-y := -std=gnu99
obj-m += rootkit.o
rootkit-objs := simple_rootkit.o fops.o keylogger.o etc.o hooking.o root_access.o hide_proc.o hide_file.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
