#include <stdlib.h>
#include "tree.h"

node tree(int v, node l, node r) {
    node n = malloc(sizeof(struct node_s));
    n->value = v;
    n->left  = l;
    n->right = r;
    return n;
}

void destroy_tree(node n) {
    if (n == NULL) return;
    destroy_tree(n->left);
    destroy_tree(n->right);
    free(n);
}