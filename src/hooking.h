#ifndef _HOOKING_H
#define _HOOKING_H

typedef asmlinkage long (*t_syscall)(const struct pt_regs *);

int init_hooking(void);
int exit_hooking(void);

int add_hook(unsigned long, int);
int hook(void);

t_syscall get_syscall(int);

#define MAX_HOOKS 7

#endif
