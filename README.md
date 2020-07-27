# simple_rootkit
## A simple LKM kernel space rootkit for v5.x linux with multiple functions.

### How to build and run the LKM
1. Clone the repository to a local folder.
2. cd into src/
3. Run make in order to build the module.
4. Watch the kernel logging with `dmesg -w` in order to see printk messages in real time.
5. Manually get kallsyms_lookup_name function with `sudo cat /proc/kallsyms | grep kallsyms_lookup_name`
6. Insert the module with `sudo insmod rootkit.ko lookup_addr=[INSERT ADDRESS HERE]`.
7. Create the character driver with `sudo mknod /dev/rootkit c [INSERT MAJOR HERE] 0`.  
   You can get the major number from the kernel messages in dmesg.
8. Remove the module with `sudo rmmod rootkit.ko`.


### Currently planned features:
- [x] keylogging.
- [ ] process hiding from ps
- [ ] file hiding from ls.
- [ ] controlling file renaming.
- [ ] providing root access from inside the machine.

### Minor TODO list:
- [x] Make a script for the qemu environment testing.
- [ ] Automate the mknod process.
  
<br>
Built and tested on a 5.7.9 arch linux machine.
