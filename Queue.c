#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if(queue == NULL) {
        printf("It was not possible to allocate a memory.");
        exit(1);
    }
    queue->front = NULL;
    return queue;
}

Node* createNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if(node == NULL) {
        printf("It was not possible to allocate a memory.");
        exit(1);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

void enqueue(Queue** queue, int value) {
    Queue* queuePointer = *queue;
    Node* newNode = createNode(value);
    
    if (queuePointer->front == NULL) {
        queuePointer->front = newNode;
        return;
    }

    Node* current = queuePointer->front;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

Node* dequeue(Queue** queue) {
    Queue* queuePointer = *queue;
    
    if (queuePointer->front == NULL) {
        printf("The queue is empty!\n");
        return NULL;
    }

    Node* removedNode = queuePointer->front;

    queuePointer->front = queuePointer->front->next;
    return removedNode;
}

void removeElementInQueue(Queue** queue, int key) {
    Queue* queuePointer = *queue;
    Node* prev = NULL;
    if (queuePointer->front == NULL) {
        printf("The queue is empty!\n");
        return;
    }
    
    Node* current = queuePointer->front;
    
    if (current != NULL && current->value == key) {
        queuePointer->front = current->next;
        free(current);
        return;
    }

    while(current != NULL && current->value != key) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Element %d not found in queue\n", key);
        return;
    }

    prev->next = current->next;
    free(current);
}