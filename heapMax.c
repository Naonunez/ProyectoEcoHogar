    #include <stdio.h>
    #include <stdlib.h>
    #include "heapMax.h"

    // Estructura para representar el montículo de máximos
    typedef struct MaxHeap MaxHeap;

    struct MaxHeap{
        int *array;     // Array para almacenar los elementos del montículo
        int capacity;   // Capacidad máxima del montículo
        int size;       // Número actual de elementos en el montículo
    };


    // Función para inicializar un montículo de máximos
    MaxHeap* createMaxHeap(int capacity) {
        MaxHeap *maxHeap = (MaxHeap*)malloc(sizeof(MaxHeap));
        maxHeap->capacity = capacity;
        maxHeap->size = 0;
        maxHeap->array = (int*)malloc(capacity * sizeof(int));
        return maxHeap;
    }

    // Función para intercambiar dos elementos en el montículo
    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    // Función para obtener el índice del padre de un nodo
    int getParentIndex(int i) {
        return (i - 1) / 2;
    }

    // Función para obtener el índice del hijo izquierdo de un nodo
    int getLeftChildIndex(int i) {
        return 2 * i + 1;
    }

    // Función para obtener el índice del hijo derecho de un nodo
    int getRightChildIndex(int i) {
        return 2 * i + 2;
    }

    // Función para mantener la propiedad de montículo después de agregar un nuevo elemento
    void maxHeapify(MaxHeap *maxHeap, int i) {
        int left = getLeftChildIndex(i);
        int right = getRightChildIndex(i);
        int largest = i;

        // Comprobar si el hijo izquierdo es mayor que el nodo actual
        if (left < maxHeap->size && maxHeap->array[left] > maxHeap->array[largest]) {
            largest = left;
        }

        // Comprobar si el hijo derecho es mayor que el nodo actual
        if (right < maxHeap->size && maxHeap->array[right] > maxHeap->array[largest]) {
            largest = right;
        }

        // Si el nodo actual no es el más grande, intercambiar con el hijo más grande y seguir recursivamente
        if (largest != i) {
            swap(&maxHeap->array[i], &maxHeap->array[largest]);
            maxHeapify(maxHeap, largest);
        }
    }

    // Función para insertar un nuevo elemento en el montículo
    void insert(MaxHeap *maxHeap, int value) {
        if (maxHeap->size == maxHeap->capacity) {
            printf("El montículo está lleno. No se puede insertar más elementos.\n");
            return;
        }

        // Insertar el nuevo elemento al final del array
        int i = maxHeap->size;
        maxHeap->array[i] = value;
        maxHeap->size++;

        // Mantener la propiedad de montículo
        while (i != 0 && maxHeap->array[getParentIndex(i)] < maxHeap->array[i]) {
            swap(&maxHeap->array[i], &maxHeap->array[getParentIndex(i)]);
            i = getParentIndex(i);
        }
    }

    // Función para extraer el elemento máximo del montículo
    int extractMax(MaxHeap *maxHeap) {
        if (maxHeap->size <= 0) {
            printf("El montículo está vacío. No se puede extraer ningún elemento.\n");
            return -1; // Valor indicativo de error
        }

        // El elemento máximo está en la raíz (índice 0)
        int maxElement = maxHeap->array[0];

        // Reemplazar la raíz con el último elemento y reducir el tamaño del montículo
        maxHeap->array[0] = maxHeap->array[maxHeap->size - 1];
        maxHeap->size--;

        // Mantener la propiedad de montículo
        maxHeapify(maxHeap, 0);

        return maxElement;
    }


