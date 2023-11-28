#ifndef HEAPMAX_H
#define HEAPMAX_H

//Estructura del Nodo
typedef struct {
    double value;
    char* nombre; 
} HeapNode;

// Estructura del heap máximo
typedef struct {
    HeapNode* arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity);
void insertarMax(MaxHeap* heap, double value, const char* nombre);
void heapifyUpMax(MaxHeap* heap, int index);
void Mostrar5Max(MaxHeap* heap);
void liberarMaxHeap(MaxHeap* heap);

#endif /* HEAPMAX_H */
