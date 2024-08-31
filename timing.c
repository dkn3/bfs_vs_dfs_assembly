#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "bfs.h"
#include "dfs.h"
#include "bfs_optimized.h"
#include "dfs_optimized.h"

#define TREE_DEPTH 17
#define NUM_RUNS 3
#define CHILDREN_PER_NODE 3
#define TOTAL_NODES 10000000

void dummy_process(int n) {
    // Do nothing, just to simulate processing
}

node create_large_tree(int depth) {
    if (depth == 0) return NULL;
    
    node root = tree(rand() % 1000, NULL, NULL);
    
    if (depth > 1) {
        root->left = create_large_tree(depth - 1);
        root->right = create_large_tree(depth - 1);
        
        // Add a third child to make the tree larger
        node third_child = create_large_tree(depth - 1);
        if (rand() % 2 == 0) {
            // Attach to left
            node temp = root->left;
            root->left = third_child;
            third_child->left = temp;
        } else {
            // Attach to right
            node temp = root->right;
            root->right = third_child;
            third_child->right = temp;
        }
    }
    
    return root;
}

node create_balanced_tree(int nodes) {
    if (nodes <= 0) return NULL;
    if (nodes == 1) return tree(rand() % 1000, NULL, NULL);
    
    int left_nodes = nodes / 2;
    int right_nodes = nodes - left_nodes - 1;
    
    node root = tree(rand() % 1000, NULL, NULL);
    root->left = create_balanced_tree(left_nodes);
    root->right = create_balanced_tree(right_nodes);
    
    return root;
}

double time_traversal(const char* name, void (*traversal)(node, void (*)(int)), node root) {
    struct timespec start, end;
    double total_time = 0.0;

    for (int i = 0; i < NUM_RUNS; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        traversal(root, dummy_process);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-6; // Convert to milliseconds
        total_time += time_taken;
    }

    double avg_time = total_time / NUM_RUNS;
    printf("%25s took %7.3f ms (avg of %d runs)\n", name, avg_time, NUM_RUNS);
    return avg_time;
}

int count_nodes(node root) {
    if (root == NULL) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}
int main() {
    srand(time(NULL));
    
    node large_tree = create_balanced_tree(TOTAL_NODES);
    //node large_tree = create_large_tree(TREE_DEPTH);
    int node_count = count_nodes(large_tree);
    //printf("Tree created with %d nodes\n\n", node_count);
    printf("Balanced tree created with %d nodes\n\n", node_count);
    
    printf("Unoptimized versions:\n");
    double bfs_time = time_traversal("BFS", bfs, large_tree);
    double dfs_pre_time = time_traversal("DFS pre-order", dfs_preorder, large_tree);
    double dfs_in_time = time_traversal("DFS in-order", dfs_inorder, large_tree);
    double dfs_post_time = time_traversal("DFS post-order", dfs_postorder, large_tree);
    
    printf("\nOptimized versions:\n");
    double bfs_opt_time = time_traversal("BFS (optimized)", bfs_optimized, large_tree);
    double dfs_pre_opt_time = time_traversal("DFS pre-order (optimized)", dfs_preorder_optimized, large_tree);
    double dfs_in_opt_time = time_traversal("DFS in-order (optimized)", dfs_inorder_optimized, large_tree);
    double dfs_post_opt_time = time_traversal("DFS post-order (optimized)", dfs_postorder_optimized, large_tree);
    
    printf("\nPerformance improvements:\n");
    printf("BFS: %.2f%%\n", (bfs_time - bfs_opt_time) / bfs_time * 100);
    printf("DFS pre-order: %.2f%%\n", (dfs_pre_time - dfs_pre_opt_time) / dfs_pre_time * 100);
    printf("DFS in-order: %.2f%%\n", (dfs_in_time - dfs_in_opt_time) / dfs_in_time * 100);
    printf("DFS post-order: %.2f%%\n", (dfs_post_time - dfs_post_opt_time) / dfs_post_time * 100);
    
    destroy_tree(large_tree);
    
    return 0;
}