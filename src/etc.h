#ifndef _ETC_H
#define _ETC_H

void init_etc(unsigned long lookup_addr);
void exit_etc(void);

inline int protect_memory(void);
inline int unprotect_memory(void);

int set_addr_rw(unsigned long _addr);
int set_addr_ro(unsigned long _addr);
#endif
