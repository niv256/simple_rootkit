#ifndef _HOOKING_H
#define _HOOKING_H

void init_hooking(void);
int exit_hooking(void);

int add_hook(unsigned long *new_func, int index);
int hook(void);
int unhook(void);

#define MAX_HOOKS 5

#endif
