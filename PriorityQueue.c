#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct PQueue {
    Node* front;
} PQueue;

PQueue* createPQueue() {
    PQueue* queue = (PQueue*) malloc(sizeof(PQueue));
    if (queue == NULL) {
        printf("The queue is empty!\n");
        exit(1);
    }
    queue->front = NULL;
    return queue;
}

Node* createNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        printf("The queue is empty!\n");
        exit(1);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

void enqueue(PQueue** queue, int value) {
    PQueue* queuePointer = *queue; 
    Node* newNode = createNode(value);
    Node* prev = NULL;

    if(queuePointer->front == NULL) {
        queuePointer->front = newNode;
        return;
    }

    Node* current = queuePointer->front;
    
    while(current != NULL && current->value <= value) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        newNode->next = queuePointer->front;
        queuePointer->front = newNode;
        return;
    }

    prev->next = newNode;
    newNode->next = current;
    
}

int main() {
    PQueue* queue = createPQueue();
    enqueue(&queue, 2);
    enqueue(&queue, 1);
    printf("Segundo valor: %d\n", queue->front->next->value);
}