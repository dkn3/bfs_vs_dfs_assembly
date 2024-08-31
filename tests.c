#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "bfs.h"
#include "dfs.h"
#include "bfs_optimized.h"
#include "dfs_optimized.h"

#define MAX_OUTPUT 1000

char output[MAX_OUTPUT];
int output_index = 0;

void reset_output() {
    memset(output, 0, MAX_OUTPUT);
    output_index = 0;
}

void print_to_string(int value) {
    output_index += snprintf(output + output_index, MAX_OUTPUT - output_index, "%d ", value);
}

void compare_outputs(const char* name, const char* unopt, const char* opt) {
    printf("%s:\n", name);
    printf("  Unoptimized: %s\n", unopt);
    printf("    Optimized: %s\n", opt);
    if (strcmp(unopt, opt) == 0) {
        printf("  Result: PASS\n\n");
    } else {
        printf("  Result: FAIL - outputs do not match\n\n");
    }
}

int main() {
    node root = tree(1,
                     tree(2,
                          tree(4,
                               tree(7, NULL, NULL),
                               NULL),
                          tree(5, NULL, NULL)),
                     tree(3,
                          tree(6,
                               tree(8, NULL, NULL),
                               tree(9, NULL, NULL)),
                          NULL));

    char bfs_unopt[MAX_OUTPUT], bfs_opt[MAX_OUTPUT];
    char dfs_pre_unopt[MAX_OUTPUT], dfs_pre_opt[MAX_OUTPUT];
    char dfs_in_unopt[MAX_OUTPUT], dfs_in_opt[MAX_OUTPUT];
    char dfs_post_unopt[MAX_OUTPUT], dfs_post_opt[MAX_OUTPUT];

    // Test BFS
    reset_output();
    bfs(root, print_to_string);
    strcpy(bfs_unopt, output);

    reset_output();
    bfs_optimized(root, print_to_string);
    strcpy(bfs_opt, output);

    compare_outputs("BFS", bfs_unopt, bfs_opt);

    // Test DFS Pre-order
    reset_output();
    dfs_preorder(root, print_to_string);
    strcpy(dfs_pre_unopt, output);

    reset_output();
    dfs_preorder_optimized(root, print_to_string);
    strcpy(dfs_pre_opt, output);

    compare_outputs("DFS Pre-order", dfs_pre_unopt, dfs_pre_opt);

    // Test DFS In-order
    reset_output();
    dfs_inorder(root, print_to_string);
    strcpy(dfs_in_unopt, output);

    reset_output();
    dfs_inorder_optimized(root, print_to_string);
    strcpy(dfs_in_opt, output);

    compare_outputs("DFS In-order", dfs_in_unopt, dfs_in_opt);

    // Test DFS Post-order
    reset_output();
    dfs_postorder(root, print_to_string);
    strcpy(dfs_post_unopt, output);

    reset_output();
    dfs_postorder_optimized(root, print_to_string);
    strcpy(dfs_post_opt, output);

    compare_outputs("DFS Post-order", dfs_post_unopt, dfs_post_opt);

    destroy_tree(root);
    return 0;
}