// Implements a list of numbers as a binary search tree

#include <stdio.h>
#include <stdlib.h>

// Represents a node
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;

node *make_node(int number);
void print_tree(node *root);
void free_tree(node *root);

// Tree of size 0
node *tree = NULL;

int main(void)
{
    // Add number to list
    node *n = make_node(2);
    tree = n;

    // Add number to list
    n = make_node(1);
    tree->left = n;

    // Add number to list
    n = make_node(3);
    tree->right = n;

    // Print tree
    print_tree(tree);

    // Free tree
    free_tree(tree);
    return 0;
}

// ----------------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------------

node *make_node(int number) {
    node *n = malloc(sizeof(node));

    if (n == NULL) {
        free_tree(tree);
        exit(1);
    }

    n->number = number;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void free_tree(node *root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(node *root) {
    if (root == NULL) return;

    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}
