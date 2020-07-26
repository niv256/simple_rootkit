#include <asm/paravirt.h>
#include "etc.h"

unsigned long (*kallsyms_lookup_name)(const char *);

static long long old_cr0;
static int protected;

void init_etc(unsigned long lookup_addr) {
	protected = 1;
	kallsyms_lookup_name = (void *) lookup_addr;
}

void exit_etc(void) {
	if (!protected) {
		protect_memory();
	}
}

// turn off the wp bit in cr0, to turn off read only page protection
inline int unprotect_memory(void) {
	if (!protected) {
		return 1;
	}

	old_cr0 = read_cr0();
	write_cr0(old_cr0 & (~0x10000));
	protected = 0;

	return 0;
}

// revert cr0 to before turning off protection
inline int protect_memory(void) {
	if (protected) {
		return 1;
	}

	write_cr0(old_cr0);
	protected = 1;

	return 0;
}
