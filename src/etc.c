#include <asm/paravirt.h>
#include "etc.h"

// set page holding _addr to read write
int set_addr_rw(unsigned long _addr) {

	unsigned int level;
	pte_t *pte;

	pte = lookup_address(_addr, &level);

	// set read write in page attributes
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

	// unset read write in page attributes
	pte->pte = pte->pte &~_PAGE_RW;

	return 0;
}
