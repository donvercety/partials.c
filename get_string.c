#include <stdio.h>
#define MAX_STRING_LENGTH 256

char *get_string(char* buffer, int buffer_size) {
	char* p = buffer;
	int count = 0;

	do {
		char c;
		scanf("%c", &c);

		// break on end of line, string terminating NUL, or end of file
		if (c == '\r' || c == '\n' || c == 0 || c == EOF) {
			*p = 0;
			break;
		}

		*p++ = c; // add the valid character into the buffer
		count++;

	} while (count < buffer_size - 1); // don't overrun the buffer

	// ensure the string is null terminated
	buffer[buffer_size - 1] = 0;
	return buffer;
}

int main(int argc, char const *argv[]) {
	char str[MAX_STRING_LENGTH];

	printf("get: ");
	get_string(str, MAX_STRING_LENGTH);
	printf("got: %s\n", str);
}
