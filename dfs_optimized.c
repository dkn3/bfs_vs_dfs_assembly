#include <stddef.h>
#include "dfs_optimized.h"


// Tail-recursive DFS pre-order
static void dfs_preorder_tail(node n, void (*process)(int)) {
    while (n) {
        process(n->value);
        dfs_preorder_tail(n->left, process);
        n = n->right;  // Tail recursion optimization
    }
}

void dfs_preorder_optimized(node root, void (*process)(int)) {
    dfs_preorder_tail(root, process);
}

// Iterative DFS in-order
void dfs_inorder_optimized(node root, void (*process)(int)) {
    node current = root;
    node stack[100];  // Fixed-size stack, assuming max depth of 100
    int top = -1;

    while (current || top >= 0) {
        while (current) {
            stack[++top] = current;
            current = current->left;
        }
        
        current = stack[top--];
        process(current->value);
        current = current->right;
    }
}

// Iterative DFS post-order
void dfs_postorder_optimized(node root, void (*process)(int)) {
    if (!root) return;

    node stack[100];  // Fixed-size stack, assuming max depth of 100
    int top = -1;
    node current = root;
    node last_visited = NULL;

    while (current || top >= 0) {
        if (current) {
            stack[++top] = current;
            current = current->left;
        } else {
            node peek = stack[top];
            if (peek->right && last_visited != peek->right) {
                current = peek->right;
            } else {
                process(peek->value);
                last_visited = peek;
                top--;
            }
        }
    }
}