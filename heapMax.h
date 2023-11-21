#ifndef HEAPMAX_H
#define HEAPMAX_H

typedef struct MaxHeap MaxHeap;

MaxHeap* createMaxHeap(int capacity);
void maxHeapify(MaxHeap *maxHeap, int i);
void insert(MaxHeap *maxHeap, int value);
int extractMax(MaxHeap *maxHeap);


#endif /* HEAPMAX_H */
