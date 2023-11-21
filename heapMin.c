#include "heapMin.h"
#include <stdlib.h>

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroyMinHeap(MinHeap* heap) {
    free(heap->array);
    free(heap);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertMinHeap(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        // Heap is full
        return;
    }

    // Insert at the end
    int index = heap->size;
    heap->array[index] = value;
    heap->size++;

    // Fix the min heap property
    while (index > 0 && heap->array[index] < heap->array[(index - 1) / 2]) {
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        // Heap is empty
        return -1;  // Or any appropriate value to indicate an error
    }

    // Extract the minimum value
    int minValue = heap->array[0];

    // Replace the root with the last element
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // Fix the min heap property
    heapify(heap, 0);

    return minValue;
}

void heapify(MinHeap* heap, int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // Find the smallest among the root, left child, and right child
    if (leftChild < heap->size && heap->array[leftChild] < heap->array[smallest]) {
        smallest = leftChild;
    }

    if (rightChild < heap->size && heap->array[rightChild] < heap->array[smallest]) {
        smallest = rightChild;
    }

    // If the smallest is not the root, swap and continue heapifying
    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

void decreaseKey(MinHeap* heap, int index, int newValue) {
    if (index >= heap->size) {
        // Invalid index
        return;
    }

    heap->array[index] = newValue;

    // Fix the min heap property
    while (index > 0 && heap->array[index] < heap->array[(index - 1) / 2]) {
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}
