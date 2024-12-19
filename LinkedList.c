#include <stdlib.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("It was not possible to allocate a memory.");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

void insertNode(struct Node** head, size_t pos, int data) {
    struct Node* newNode = createNode(data);
    struct Node* current = *head;

    if (pos == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    for (int i = 0; i < pos - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Invalid position\n");
        return;
    }

    newNode->next = current->next;
    current->next = newNode;

}

void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Element %d not found in LinkedList\n", key);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    };
    printf("NULL\n");
}

int main() {
    struct Node* head = createNode(1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    insertNode(&head, 0, 30);
    printList(head);
    return 0;
}