#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct PQueue {
    Node* front;
    char* type;
} PQueue;

PQueue* createPQueue(char* type) {
    PQueue* queue = (PQueue*) malloc(sizeof(PQueue));
    if (queue == NULL) {
        printf("The queue is empty!\n");
        exit(1);
    }
    queue->front = NULL;
    queue->type = type;
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
    
    if(queuePointer->type == "<" || queuePointer->type == NULL) {
        while(current != NULL && current->value <= value) {
            prev = current;
            current = current->next;
        }
    } else if (queuePointer->type == ">") {
        while(current != NULL && current->value >= value) {
            prev = current;
            current = current->next;
        }
    }

    if (prev == NULL) {
        newNode->next = queuePointer->front;
        queuePointer->front = newNode;
        return;
    }

    prev->next = newNode;
    newNode->next = current;
    
}

Node* dequeue(PQueue** queue) {
    PQueue* queuePointer = *queue;
    if (queuePointer->front == NULL) {
        printf("The Priority Queue is empty!\n");
        return NULL;
    }
    Node* removedNode = queuePointer->front;
    queuePointer->front = queuePointer->front->next;
    return removedNode;
}

int main() {

    // '<' least to greater
    // '>' greater to least
        
    PQueue* queue = createPQueue(">");
    enqueue(&queue, 2);
    enqueue(&queue, 8);
    enqueue(&queue, 4);
    enqueue(&queue, 1);
    printf("Primeiro valor: %d\n", queue->front->value);
    printf("Segundo valor: %d\n", queue->front->next->value);
    printf("Terceiro valor: %d\n", queue->front->next->next->value);
    printf("Quarto valor: %d\n", queue->front->next->next->next->value);
    return 0;
}