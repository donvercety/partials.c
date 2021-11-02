#include <stdio.h>  // printf()
#include <time.h>	// clock()
#include "fx.h"

/**
 * Examples/Practice from the C Book.
 */
void ex_book() {
	printf("..ex_book\n");
	bubble_sort();
}

// ----------------------------------------------------------------------------
// :: Main Function Only
// ----------------------------------------------------------------------------
//
//

int main(int argc, char *argv[]) {
	int start = clock();

//	ex_002();
//	ex_001();

	ex_book();

	printf("\nclock: %dms\n", clock() - start);
	return 0;
}

// ----------------------------------------------------------------------------
// :: Example functions.
// ----------------------------------------------------------------------------
//
//

/**
 * Simple printf examples.
 */
int ex_001() {
	beep();
	print_ascii();
	printf("\n\n");
	beep();
	print_hex();
}

/**
 * Get string from scan in another finction.
 * Also 'take_input_string' can take spaces as an imput.
 */
int ex_002() {
	char str_ptr[256];

	do {
		system("cls");
		take_input_string(str_ptr);
		printf("%s\n", str_ptr);
		printf("\nAgain [y/n]:");

	} while (getche() == 'y');

	return 0;
}
