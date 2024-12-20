#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* previous;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* current = *head;
    Node* newNode = createNode(data);

    if(*head == NULL) {
        *head = newNode;
        return;
    }

    while (current->next != NULL) {
        current = current->next;
    }
    
    newNode->previous = current;
    current->next = newNode;
}

void deleteNode(Node** head, int key) {
    Node* current = *head;

    if(current != NULL && current->data == key) {
        current->previous = NULL;
        *head = current->next;
        free(current);
        return;
    }

    while (current != NULL && current->data != key) {
        current = current->next;
    }

    current->previous->next = current->next;
    current->next->previous = current->previous;
    free(current);
}

void printNodeData(Node* node, const char* label) {
    if (node != NULL) {
        printf("%s: %d\n", label, node->data);
    } else {
        printf("%s: NULL\n", label);
    }
}

void printNode(Node* node) {
    
    if (node == NULL) {
        printf("Invalid Node\n");
        return;
    }


    while (node != NULL) {

        if (node->previous != NULL)
            printf("\nPrevious: %d\n", node->previous->data);
        else
            printf("\nPrevious: None\n");
        


        printf("Current: %d\n", node->data);

        if (node->next != NULL)
            printf("Next: %d\n", node->next->data);
        else
            printf("Next: None\n");
        
        
        node = node->next;
    }

}

int main() {
    Node* doubly = createNode(10);
    appendNode(&doubly, 30);
    appendNode(&doubly, 50);
    deleteNode(&doubly, 30);
    printNode(doubly);
    return 0;
}
