#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int* data;
    size_t capacity;
    size_t size;
} Vector;

Vector createVector(size_t initial_capacity) {
    Vector vector;
    vector.data = (int *) malloc(initial_capacity * sizeof(int));
    vector.size = 0;
    vector.capacity = initial_capacity;
    return vector;
}

bool resizeVector(Vector* vector, size_t new_capacity) {
    int* new_data = (int*) malloc(new_capacity * sizeof(int));
    if (new_data == NULL) return false;
    memcpy(new_data, vector->data, vector->size * sizeof(int));
    free(vector->data);
    vector->data = new_data;
    vector->capacity = new_capacity;
    return true;
}

bool addElement(Vector* vector, int value) {
    if(vector->size >= vector->capacity) {
        size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;
        if(!resizeVector(vector, new_capacity)) {
            return false;
        }
    }
    vector->data[vector->size++] = value;
    return true;
}

bool getElement(Vector* vector, size_t index, int* value) {
    if(index >= vector->size) {
        return false;
    }
    *value = vector->data[index];
    return true;
}

bool setElement(Vector* vector, size_t index, int value) {
    if(index >= vector->size) {
        printf("Index %zu does not exists\n", index);
        return false;
    }
    vector->data[index] = value;
    return true;
}

int* accessElement(Vector* vector, size_t index) {
    if (index >= vector->size) {
        printf("Index %zu does not exists\n", index);
        return NULL;
    }
    return &vector->data[index];
}

void destroyVector(Vector* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

int main() {
    Vector vector = createVector(2);
    addElement(&vector, 1);
    addElement(&vector, 2);
    addElement(&vector, 3);
    printf("Capacity: %zu\n", vector.capacity);

    for(size_t i = 0; i < vector.size; i++) {
        int value;
        if(getElement(&vector, i, &value)) {
            printf("Index: %zu -- Value: %d\n", i, value);
        }
    }
    destroyVector(&vector);
    return 0;
}