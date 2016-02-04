#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

// modified https://robin-thomas.github.io/min-heap/
//TODO stop resizing constantly, fix memory leak - astar_node*

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct node {
    int data ;
    astar_node* astar_node;
} node ;

typedef struct minHeap {
    int size ;
    node *elem ;
} minHeap ;

minHeap initMinHeap(void);
void heapify(minHeap *hp, int i);
void buildMinHeap(minHeap *hp, int* arrData, astar_node* arrNodes, int size);
void insertNode(minHeap *hp, int data, astar_node* astar_node);
void deleteNode(minHeap *hp);
astar_node* popNode(minHeap* hp);
int getMaxNode(minHeap *hp, int i);
void deleteMinHeap(minHeap *hp);
void inorderTraversal(minHeap *hp, int i);
void preorderTraversal(minHeap *hp, int i);
void postorderTraversal(minHeap *hp, int i);
void levelorderTraversal(minHeap *hp);

#endif /* MIN_HEAP_H_ */
