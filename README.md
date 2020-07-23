# simple_rootkit
## A simple LKM kernel space rootkit for v5.x linux with multiple functions.

### How to build and run the LKM
1. Clone the repository to a local folder.
2. Run make in order to build the module.
3. Watch the kernel logging with `dmesg -Hw` in order to see printk messages in real time.
4. Insert the module with `sudo insmod rootkit.ko`.
5. Create the character driver with `sudo mknod /dev/rootkit c [INSERT MAJOR HERE] 0`.  
   You can get the major number from the kernel messages in dmesg.
6. Remove the module with `sudo rmmod rootkit.ko`.


### Currently planned features:
- [ ] process hiding from ps.
- [ ] file hiding from ls.
- [ ] controlling file renaming.
- [ ] providing root access from inside the machine.
- [ ] keylogging.

### Minor TODO list:
- [ ] Automate the mknod process.
- [ ] Make a script for the qemu environment testing.
  
<br>
Built and tested on a 5.7.9 arch linux machine.
