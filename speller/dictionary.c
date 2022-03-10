#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
	char word[LENGTH + 1];
	struct node *next;
}
node;

// Choose number of buckets in hash table
#define N 26

// Hash table
node *table[N];

unsigned int words_count = 0;

// ----------------------------------------------------------------------------
// Helpers Functions
// ----------------------------------------------------------------------------

/**
 * Recursively free memory from a linked list.
 */
void _free_llist(node *list) {
    while (list != NULL) {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}

// ----------------------------------------------------------------------------
// External Functions
// ----------------------------------------------------------------------------

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
	int h = hash(word);

	// empty location, than no word match can be achieved
	if (table[h] == NULL) {
		return false;
	}

	for (node *tmp = table[h]; tmp != NULL; tmp = tmp->next) {
		if (strcasecmp(tmp->word, word) == 0) {
			return true;
		}
    }

	return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
	// Improve this hash function...?
	return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
	FILE *file = fopen(dictionary, "r");
	if (file == NULL) {
		return false;
	}

	char word[LENGTH + 1];
	while (fscanf(file, "%s", word) != EOF) {
		words_count++;

		// create new node
		node *n = malloc(sizeof(node));

		// set node values
		strcpy(n->word, word);
		n->next = NULL;

		// calculate hash value
		int h = hash(word);

		// add fist node to hash-table
		if (table[h] == NULL) {
			table[h] = n;

		// push node to hash-table to a linked list
		} else {
			n->next = table[h];
			table[h] = n;
		}
	}

	fclose(file);
	return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
	return words_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	for (int i = 0; i < N; i++) {
		if (table[i] != NULL) {
			_free_llist(table[i]);
		}
	}

	return true;
}
