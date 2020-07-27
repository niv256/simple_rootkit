#ifndef _HOOKING_H
#define _HOOKING_H

typedef asmlinkage long (*t_syscall)(const struct pt_regs *);

void init_hooking(void);
int exit_hooking(void);

int add_hook(unsigned long, int);
int hook(void);
int unhook(void);

t_syscall get_syscall(int);

#define MAX_HOOKS 5

#endif
