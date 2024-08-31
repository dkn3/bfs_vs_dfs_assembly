#include <stddef.h>
#include "dfs.h"

void dfs_preorder(node n, void (*f)(int)) {
    if (n == NULL) return;
    f(n->value);
    dfs_preorder(n->left, f);
    dfs_preorder(n->right, f);
}

void dfs_inorder(node n, void (*f)(int)) {
    if (n == NULL) return;
    dfs_inorder(n->left, f);
    f(n->value);
    dfs_inorder(n->right, f);
}

void dfs_postorder(node n, void (*f)(int)) {
    if (n == NULL) return;
    dfs_postorder(n->left, f);
    dfs_postorder(n->right, f);
    f(n->value);
}