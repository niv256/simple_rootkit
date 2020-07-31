# simple_rootkit
## A simple LKM kernel space rootkit for < v5.7 linux with multiple functions.
## Warning: due to the unexport of kallsyms_lookup functions from the kernel introduced in v5.7, this rootkit will NOT work on this version onwards.

### How to build and run the LKM
1. Clone the repository to a local folder.
2. cd into src/
3. Run make in order to build the module.
4. Watch the kernel logging with `dmesg -w` in order to see printk messages in real time.
5. Insert the module with `sudo insmod rootkit.ko`.
6. Create the character driver with `sudo mknod /dev/rootkit c [INSERT MAJOR HERE] 0`.  
   You can get the major number from the kernel messages in dmesg.
7. Remove the module with `sudo rmmod rootkit.ko`.

### How to hide a chosen pid:
1. When inserting the module, pass the chosen pid as a parameter to the insmod function, like this:
   `sudo insmod rookit.ko pid="6375"'
   To hide pid 6375.


### How to read the user's keystrokes:
1. Make sure you have created the character device from step 6 above.
2. Read from `/dev/rootkit` file, for example, with `cat /dev/rootkit`.

### How to spawn a root shell as a normal user once the rootkit has loaded:
1. Execute the get_root program (in get_root folder) or anything similar which changes a file's name from "please_give" to "me_root_priv" and spawns a shell.
2. Execute the `id` program to make sure you are root.
3. Enjoy unlimited capabilities!

### Currently planned features:
- [x] keylogging.
- [x] controlling file renaming.
- [x] providing root access from inside the machine.
- [x] process hiding from ps
- [ ] file hiding from ls.

### Minor TODO list:
- [x] Make a script for the qemu environment testing.
- [ ] Automate the mknod process.
  
<br>
Built and tested on a 18.04 ubuntu machine (kernel version 5.3.0).
qemu environment runs 5.6.18 kernel version.
