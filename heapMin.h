#ifndef HEAPMIN_H
#define HEAPMIN_H

//Estructura del Nodo
typedef struct {
    double value;
    char* nombre; 
} HeapNodeMin;

// Estructura del heap mínimo
typedef struct {
    HeapNodeMin* arr;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity);
void insertarMin(MinHeap* heap, double value, const char* nombre);
void heapifyUpMin(MinHeap* heap, int index);
void Mostrar5Min(MinHeap* heap);
void liberarMinHeap(MinHeap* heap);

#endif
