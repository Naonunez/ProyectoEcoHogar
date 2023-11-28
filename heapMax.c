#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heapMax.h"

// Función para crear un heap máximo
MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->arr = (HeapNode*)malloc(sizeof(HeapNode) * (size_t)capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Función para mantener la propiedad del heap máximo hacia arriba
void heapifyUpMax(MaxHeap* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->arr[index].value > heap->arr[parent].value) {
        // Intercambiar elementos y sus identificadores
        HeapNode temp = heap->arr[index];
        heap->arr[index] = heap->arr[parent];
        heap->arr[parent] = temp;

        index = parent;
        parent = (index - 1) / 2;
    }
}

// Función para insertar un elemento en el heap máximo
void insertarMax(MaxHeap* heap, double value, const char* nombre) {
    if (heap->size == heap->capacity) {
        printf("El heap está lleno. No se puede insertar más elementos.\n");
        return;
    }

    heap->arr[heap->size].value = value;
    
    // Asignar memoria y copiar el identificador
    heap->arr[heap->size].nombre = (char*)malloc(strlen(nombre) + 1);
    strcpy(heap->arr[heap->size].nombre, nombre);

    heapifyUpMax(heap, heap->size);

    heap->size++;
}

// Función para mostrar los 5 elementos máximos del heap
void Mostrar5Max(MaxHeap* heap) {
    int i;
    printf("Tus 5 dispositivos que mas consumen son:\n");
    for (i = 0; i < heap->size && i < 5; i++) {
        printf("(%.2lf, %s \n) ", heap->arr[i].value, heap->arr[i].nombre);
    }
    printf("\n");
}

void liberarMaxHeap(MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        free(heap->arr[i].nombre);
    }
    free(heap->arr);
    free(heap);
}