#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    char* value;
    char* key;
    struct Node* next;
} Node;

typedef struct HashTable {
    size_t capacity;
    size_t size;
    Node** lists;
} HashTable;

HashTable* createHashTable(size_t initial_capacity) {
    HashTable* newHashTable = (HashTable*) malloc(sizeof(HashTable));
    if (newHashTable == NULL) {
        printf("It was not possible to allocate memory\n");
        exit(1);
    }
    newHashTable->lists = (Node**) malloc(initial_capacity * sizeof(Node*));
    newHashTable->size = 0;
    newHashTable->capacity = initial_capacity;
    return newHashTable;
}

Node* createNode(char* key, char* value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("It was not possible to allocate memory\n");
        exit(1);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int hash(char* key) {
    double result = (strlen(key) * (strlen(key) * 9)) % 19;
    return round(result);
}

void appendNode(Node** node, Node** newNode) {
    
    if (*node == NULL) {
        *node = *newNode;
        return;
    }
    
    Node* current = *node;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = *newNode;
}

void removeNode(Node** head, char* key) {
    struct Node* current = *head;
    struct Node* prev = NULL;

    if (current != NULL && current->key == key) {
        *head = current->next;
        free(current);
        return;
    }

    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
    }

    prev->next = current->next;
    free(current);
}

Node* getNode(Node** head, char* key) {
    struct Node* current = *head;

    if (current != NULL && current->key == key) {
        return current;
    }

    while (current != NULL && current->key != key) {
        current = current->next;
    }

    return current;
}

void resizeHashTable(HashTable** ht, size_t newCapacity) {
    Node** newLists = (Node**) malloc(newCapacity * (sizeof(Node*)));
    memcpy(newLists, (*ht)->lists, (*ht)->size * sizeof(Node*));
    free((*ht)->lists);
    (*ht)->lists = newLists;
    (*ht)->capacity = newCapacity;
}


void insert(HashTable** hashTable, char* key, char* value) {
    if (key == NULL || value == NULL) {
        printf("Any value shouldn't be NULL\n");
        return;
    }
    
    HashTable* ht = *hashTable;

    if (ht->size >= ht->capacity) {
        resizeHashTable(&ht, ht->capacity * 2);
    }

    Node* newElement = createNode(key, value);
    int index = hash(key);

    appendNode(&ht->lists[index], &newElement);
    ht->size++;
}

Node* get(HashTable** hashTable, char* key) {
    HashTable* ht = *hashTable;
    
    if (ht == NULL) {
        printf("HashTable can't be NULL\n");
        return NULL;
    }

    if (ht->lists[hash(key)] == NULL) {
        printf("The '%s' does not exist\n", key);
        return NULL;
    }

    return getNode(&ht->lists[hash(key)], key);
}


void removeKey(HashTable** hashTable, char* key) {
    HashTable* ht = *hashTable;

    if (ht == NULL) {
        printf("HashTable can't be NULL\n");
        return;
    }

    if (ht->lists[hash(key)] == NULL) {
        printf("The '%s' does not exist\n", key);
        return;
    }

    return removeNode(&(*hashTable)->lists[hash(key)], key);
}

int main() {
    HashTable* ht = createHashTable(32);
    insert(&ht, "key", "123");
    removeKey(&ht, "key");
    return 0;
}