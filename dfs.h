#ifndef DFS_H
#define DFS_H

#include "tree.h"

void dfs_preorder(node n, void (*f)(int));
void dfs_inorder(node n, void (*f)(int));
void dfs_postorder(node n, void (*f)(int));

#endif