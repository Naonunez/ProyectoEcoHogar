#ifndef HEAPMIN_H
#define HEAPMIN_H

#define MAX_HEAP_SIZE 100

typedef struct {
    int *array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity);

void destroyMinHeap(MinHeap* heap);

void insertMinHeap(MinHeap* heap, int value);

int extractMin(MinHeap* heap);

void heapify(MinHeap* heap, int index);

void decreaseKey(MinHeap* heap, int index, int newValue);

#endif
