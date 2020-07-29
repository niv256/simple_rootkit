#include <stdio.h>
#include <stdlib.h>

int main() {
	rename("please_give", "me_root_priv");	// rename the file
	printf("[+] root shell:\n");
	system("/bin/bash");
}
