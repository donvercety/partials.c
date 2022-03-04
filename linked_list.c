#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

void make_node(node *node, int number);
void list_show(node *list);
void list_free(node *list);

int main(void) {

    // initialize list of size 0
    node *list = malloc(sizeof(node));
    make_node(list, 1); 

    // add number to list
    node *n = malloc(sizeof(node));
    make_node(n, 2);
    list->next = n;

    // add number to list
    n = malloc(sizeof(node));
    make_node(n, 3);
    list->next->next = n;

    list_show(list);
    list_free(list);
    return 0;
}

// ----------------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------------

void make_node(node *node, int number) {
    if (node == NULL) exit(1);

    node->number = number;
    node->next = NULL;
}

void list_show(node *list) {
   for (node *tmp = list; tmp != NULL; tmp = tmp->next) {
        printf("%i\n", tmp->number);
    } 
}

void list_free(node *list) {
    while (list != NULL) {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}
