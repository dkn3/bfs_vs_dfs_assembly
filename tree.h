#ifndef TREE_H
#define TREE_H

typedef struct node_s {
    int value;
    struct node_s* left;
    struct node_s* right;
} *node;

node tree(int v, node l, node r);
void destroy_tree(node n);

#endif

