#include <stddef.h>
#include <stdlib.h>
#include "bfs.h"

// Queue structure
typedef struct qnode_s {
    struct qnode_s* next;
    node value;
} *qnode;

typedef struct { 
    qnode begin, end; 
} queue;

// Queue operations
void enqueue(queue* q, node n) {
    qnode new_node = malloc(sizeof(struct qnode_s));
    new_node->value = n;
    new_node->next = NULL;
    if (q->end)
        q->end->next = new_node;
    else
        q->begin = new_node;
    q->end = new_node;
}

node dequeue(queue* q) {
    node tmp = q->begin->value;
    qnode second = q->begin->next;
    free(q->begin);
    q->begin = second;
    if (!q->begin)
        q->end = NULL;
    return tmp;
}

int queue_empty(queue* q) {
    return !q->begin;
}

// BFS implementation
void bfs(node n, void (*f)(int)) {
    if (n == NULL) return;

    queue nodequeue = {NULL, NULL};
    enqueue(&nodequeue, n);

    while (!queue_empty(&nodequeue)) {
        node next = dequeue(&nodequeue);
        f(next->value);
        if (next->left)
            enqueue(&nodequeue, next->left);
        if (next->right)
            enqueue(&nodequeue, next->right);
    }
}