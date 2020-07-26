# simple_rootkit
## A simple LKM kernel space rootkit for v5.x linux with multiple functions.

### How to build and run the LKM
1. Clone the repository to a local folder.
2. cd into src/
3. Run make in order to build the module.
4. Watch the kernel logging with `dmesg -Hw` in order to see printk messages in real time.
5. Insert the module with `sudo insmod rootkit.ko`.
6. Create the character driver with `sudo mknod /dev/rootkit c [INSERT MAJOR HERE] 0`.  
   You can get the major number from the kernel messages in dmesg.
7. Remove the module with `sudo rmmod rootkit.ko`.


### Currently planned features:
- [x] keylogging.
- [ ] process hiding from ps
- [ ] file hiding from ls.
- [ ] controlling file renaming.
- [ ] providing root access from inside the machine.

### Minor TODO list:
- [ ] Automate the mknod process.
- [ ] Make a script for the qemu environment testing.
  
<br>
Built and tested on a 5.7.9 arch linux machine.
