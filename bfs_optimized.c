#define QUEUE_INITIAL_CAPACITY 1024  // Pre-allocate space for 1024 nodes
#include <stddef.h>
#include <stdlib.h>
#include "bfs_optimized.h"


typedef struct {
    node* data;  // Array-based queue instead of linked list
    size_t front;
    size_t rear;
    size_t capacity;
} Queue;

// Inline functions to reduce function call overhead
static inline void queue_init(Queue* q) {
    // Pre-allocate memory for the queue
    q->data = malloc(QUEUE_INITIAL_CAPACITY * sizeof(node));
    q->front = q->rear = 0;
    q->capacity = QUEUE_INITIAL_CAPACITY;
}

static inline void queue_push(Queue* q, node n) {
    // Dynamic resizing to avoid frequent reallocations
    if (q->rear == q->capacity) {
        q->capacity *= 2;
        q->data = realloc(q->data, q->capacity * sizeof(node));
    }
    q->data[q->rear++] = n;  // Direct array access
}

static inline node queue_pop(Queue* q) {
    return q->data[q->front++];  // Direct array access
}

static inline int queue_empty(Queue* q) {
    return q->front == q->rear;
}

void bfs_optimized(node root, void (*process)(int)) {
    if (!root) return;

    Queue q;
    queue_init(&q);
    queue_push(&q, root);

    while (!queue_empty(&q)) {
        node current = queue_pop(&q);
        process(current->value);
        if (current->left) queue_push(&q, current->left);
        if (current->right) queue_push(&q, current->right);
    }

    free(q.data);  // Single deallocation instead of multiple for linked list
}