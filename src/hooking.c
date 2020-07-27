#include <linux/module.h>
#include "etc.h"
#include "hooking.h"

// table for holding all the requested hooks
static struct hook {
    unsigned long old_func;
    unsigned long new_func;
    int index;
} hook_table[MAX_HOOKS];
int table_index;

// to lock hooking and adding hooks to the table after hook()
int locked;

extern unsigned long (*kallsyms_lookup_name)(const char *);
static unsigned long *syscall_table;

void init_hooking(void) {
	memset(hook_table, 0, sizeof(hook_table));
	table_index = 0;
	locked = 0;
	syscall_table = (unsigned long *) (*kallsyms_lookup_name)("sys_call_table");
	printk(KERN_INFO "syscalltable value: %px", syscall_table);
	//printk(KERN_INFO "syscalltable value: %ln", syscall_table);
}

int exit_hooking(void) {
	int ret = unhook();
	if (ret) {
		memset(hook_table, 0, sizeof(hook_table));
	}

	return ret;
}

// adds a new syscall to the hooking function
// if already hooked, error.
int add_hook(unsigned long new_func,int index){
	if (table_index == MAX_HOOKS) {
		return 1;
	}

	if (locked) {
		return 2;
	}

    for (int i = 0; i < table_index; i++){
        if (index == hook_table[i].index) {
            return 3;
        }
    }

	hook_table[table_index].old_func = syscall_table[index];
	hook_table[table_index].new_func = new_func;
	hook_table[table_index].index = index;
	table_index++;
    return 0;
}

// hooks everything in the hooking table.
// if already hooked, error.
int hook(){
	int syscall_index;

	if (locked) {
		return 1;
	}
	set_addr_rw((unsigned long) syscall_table);
    for(int i = 0; i < table_index; i++){
        syscall_index = hook_table[i].index;
        syscall_table[syscall_index] = hook_table[i].new_func;
    }
	set_addr_ro((unsigned long) syscall_table);
	locked = 1;

	return 0;
}

// unhooks everything in the hooking table.
// if didn't hook already, error.
int unhook(){
	if (!locked) {
		return 1;
	}
	set_addr_rw((unsigned long) syscall_table);
    for(int i = 0; i < table_index; i++){
        int syscall_index = hook_table[i].index;
        syscall_table[syscall_index] = hook_table[i].old_func;
    }
	set_addr_ro((unsigned long) syscall_table);

	return 0;
}

t_syscall get_syscall(int index) {
	return (t_syscall) syscall_table[index];
}
