#include <stdio.h>
#include <windows.h>
#include "functions.h"

#define SECTION		"data"
#define INI_FILE	"./db.ini"
#define STRING_SCAN " %[^\n]s"  // https://stackoverflow.com/a/46390540
#define MAX_KEY_LEN 128
#define MAX_VAL_LEN 128
#define MAX_BUF_LEN 65535		// 65kb max file size to read

int ini_read() {
	char key[MAX_KEY_LEN];
	char val[MAX_VAL_LEN];

	printf("Key: ");
	scanf(STRING_SCAN, &key);

	// doc: https://bit.ly/38JNT3U
	GetPrivateProfileString(SECTION, key, "NOT_FOUND", val, sizeof(key), INI_FILE);
	printf("Val: %s", val);
}

int ini_write() {
	char key[MAX_KEY_LEN];
	char val[MAX_VAL_LEN];

	printf("Key: ");
	scanf(STRING_SCAN, &key);

	printf("Val: ");
	scanf(STRING_SCAN, &val);

	// doc: https://bit.ly/2X03WrB
	return WritePrivateProfileString(SECTION, key, val, INI_FILE);
}

int ini_delete() {
	char key[MAX_KEY_LEN];

	printf("\n\nKey: ");
	scanf(STRING_SCAN, &key);

	// doc: https://bit.ly/2X03WrB
	return WritePrivateProfileString(SECTION, key, NULL, INI_FILE);
}

int ini_list() {
	char buffer[MAX_BUF_LEN];

	// doc: https://bit.ly/3BNI2XJ
	GetPrivateProfileSection(SECTION, buffer, MAX_BUF_LEN, INI_FILE);

	char separator = '\n';
	int i;

	// start with null-terminated -- empty string
	if (buffer[0] != '\0') {

		// convert null-terminated array of null-terminated strings
		// to newline-delimited list
		for (i = 0; i < MAX_BUF_LEN; i++){
			if (buffer[i] == '\0' && buffer[i + 1] != '\0') {
				buffer[i] = separator;

			} else if (buffer[i] == '\0' && buffer[i + 1] == '\0') {
				break;

			} else {
				buffer[i] = buffer[i];
			}
		}
	}

	printf("%s", buffer);
}

