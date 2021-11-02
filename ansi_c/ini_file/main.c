#include <stdio.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	argc < 2 ? interactive() : direct(argv[1]);
	return 0;
}

int interactive(){
	char first_run = 1;
	char quit;
	char action;

	do {
		system("cls");

		if (first_run) {
			printf("This program will create an INI file -- 'db.ini'.\n");
			printf("You will be able to Read, Write, Delete & List entries.\n\n");
		}

		first_run = 0;

		printf("Do you want to:\n");
		printf("\n [ R ] Read");
		printf("\n [ W ] Write");
		printf("\n [ D ] Delete");
		printf("\n [ L ] List");
		printf("\n [ Q ] Quit\n\n");

		do {
			printf("Enter first letter: ");
			scanf("%s", &action);
			action = toupper(action);

		} while (
			action != 'R' && action != 'W' &&
			action != 'D' && action != 'L' &&
			action != 'Q'
		);

		switch (action) {
			case 'R':
				system("cls");
				printf("\n[ %c ] -- READ\n\n", action);
				ini_read();
				break;

			case 'W':
				system("cls");
				printf("\n[ %c ] -- WRITE\n\n", action);
				ini_write();
				break;

			case 'D':
				system("cls");
				printf("\n[ %c ] -- DELETE\n\n", action);
				ini_list();
				ini_delete();
				break;

			case 'L':
				system("cls");
				printf("\n[ %c ] -- LIST\n\n", action);
				ini_list();
				break;

			case 'Q':
				return 0;
				break;
		}

		printf("\n\nPress any key to continue or Q to quit.");
		quit = getch();

		quit = toupper(quit);
	} while (quit != 'Q');

	return 0;
}

int direct(char *action) {
	if (strcmp("-r", action) == 0) {
		printf("\n[%s] -- READ\n\n", action);
		ini_read();

	} else if (strcmp("-w", action) == 0) {
		printf("\n[%s] -- WRITE\n\n", action);
		ini_write();

	} else if (strcmp("-d", action) == 0) {
		printf("\n[%s] -- DELETE\n\n", action);
		ini_list();
		ini_delete();

	} else if (strcmp("-l", action) == 0) {
		printf("\n[%s] -- LIST\n\n", action);
		ini_list();

	} else if (strcmp("-v", action) == 0) {
		printf("ini_db v1.0\n");

	} else{
		printf("Use: program <flag>\n\nflags:");
		printf("\n   -r Read");
		printf("\n   -w Write");
		printf("\n   -d Delete");
		printf("\n   -l List\n");
	}
}
