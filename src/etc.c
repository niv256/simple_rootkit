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

// set page holding _addr to read write
int set_addr_rw(unsigned long _addr) {

        unsigned int level;
        pte_t *pte;

        pte = lookup_address(_addr, &level);

        if (pte->pte &~ _PAGE_RW) {
                pte->pte |= _PAGE_RW;
        }

        return 0;
}

// set page holding _addr to read only
int set_addr_ro(unsigned long _addr) {

        unsigned int level;
        pte_t *pte;

        pte = lookup_address(_addr, &level);
        pte->pte = pte->pte &~_PAGE_RW;

        return 0;
}
