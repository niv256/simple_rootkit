#ifndef _ETC_H
#define _ETC_H

void init_etc(unsigned long lookup_addr);
void exit_etc(void);

inline int protect_memory(void);
inline int unprotect_memory(void);

#endif
