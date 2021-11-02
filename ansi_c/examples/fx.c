#include <stdio.h>
#include <time.h>
#include "fx.h"

int print_ascii() {
	int i;
	for (i = 33; i < 256; i++) {
		printf("%c ", i);
		if (i % 32 == 0) printf("\n");
		sleep(0.05);
	}
}

int print_hex() {
	int i;
	for (i = 1; i < 256; i++) {
		printf("%02X ", i);
		if (i % 16 == 0) printf("\n");
		sleep(0.05);
	}
}

int take_input_string(char *prt) {
	printf("Waiting for input: ");
	scanf(" %[^\n]s", prt); // this can take space character
	return 0;
}

void beep() {
	printf("\a");
}

void sleep(float number_of_seconds) {
    // converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

int bubble_sort(void) {
	int item[256];
	int a, b , t;
	int count;
	
	printf("[MAX 256] How many numbers? ");
	scanf("%d", &count);
	for (a = 0; a < count; a++) {
		printf("Input number %d: ", a + 1);
		scanf("%d", &item[a]);
	}

	// sorting
	for (a = 1; a < count; ++a) {
		for (b = count - 1; b >= a; --b) {

			if (item[b - 1] > item[b]){
				t = item[b - 1];
				item[b - 1] = item[b];
				item[b] = t;
			}
		}
	}
	
	printf("\nResult:\n");
	
	// show
	for (t = 0; t < count; t++) printf("%d ", item[t]);
}










