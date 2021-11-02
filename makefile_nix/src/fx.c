#include <stdio.h>
#include <unistd.h>

int print_hex() {

    printf("\n");
	for (int i = 0; i < 256; i++) {
		printf("%02X ", i);
		fflush(stdout);

		if ((i + 1) % 16 == 0) printf("\n");
		usleep(100000);
	}

	printf("\n");
	return 0;
}
