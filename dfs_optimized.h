#ifndef DFS_OPTIMIZED_H
#define DFS_OPTIMIZED_H

#include "tree.h"

void dfs_preorder_optimized(node root, void (*process)(int));
void dfs_inorder_optimized(node root, void (*process)(int));
void dfs_postorder_optimized(node root, void (*process)(int));

#endif