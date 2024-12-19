/**
 * STATIC ARRAY
 * int capacity
 * int size
 * int* data
 * 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    size_t capacity;
    size_t size;
    int* data;
} StaticArray;

StaticArray createStaticArray(size_t capacity) {
    StaticArray array;
    array.data = (int*) malloc(capacity * sizeof(int));
    array.capacity = capacity;
    array.size = 0;
    return array;
}

bool addElement(StaticArray* array, int value) {
    if (array->size >= array->capacity) {
        return NULL;
    }

    array->data[array->size++] = value;
    return true;
}

bool getElement(StaticArray* array, size_t index, int* value) {
    if (index >= array->size) {
        return false;
    }
    *value = array->data[index];
    return true;
}

bool setElement(StaticArray* array, size_t index, int value) {
    if (index >= array->size) {
        return false;
    }
    array->data[index] = value;
    return true;
}

int* accessElement(StaticArray* array, size_t index) {
    if (index >= array->size) {
        return NULL;
    }
    return &array->data[index];
}

void destroyStaticArray(StaticArray* array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

int main() {
    StaticArray array = createStaticArray(2);
    addElement(&array, 10);
    addElement(&array, 20);
    addElement(&array, 30);
    
    if (setElement(&array, 1, 50)) {
        printf("Element at index 1 become 50\n");
    }
    
    for (size_t i = 0; i < array.size; i++) {
        int value;
        if(getElement(&array, i, &value)) {
            printf("Index: %zu -- Value: %d\n", i, value);
        }
    }
    
    int* value_ptr = accessElement(&array, 1);
    if (value_ptr != NULL) {
        printf("Direct access to element at index 1: %d\n", *value_ptr);
    }
    
    printf("capacity: %zu\n", array.capacity);
    printf("size: %zu\n", array.size);

    destroyStaticArray(&array);
    return 0;

}