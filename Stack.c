#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if(stack == NULL) {
        printf("It was not possible to allocate a memory.");
        exit(1);
    }
    stack->top = NULL;
    return stack;
}

void pushToStack(Stack* stack, int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("It was not possible to allocate a memory.");
        exit(1);
    }
    newNode->value = value;
    newNode->next = stack->top;
    stack->top = newNode;
    return;
}

Node* popStack(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty\n");
        return NULL;
    }

    Node* currentTop = stack->top;
    stack->top = currentTop->next;
    return currentTop;
}

int main() {
    Stack* stack = createStack();
    pushToStack(stack, 1);
    pushToStack(stack, 2);
    pushToStack(stack, 3);

    Node* poppedNode = popStack(stack);
    if(poppedNode) {
        printf("Stack Top Element Popped: %d\n", poppedNode->value);
        free(poppedNode);
    }

    if(stack->top) {
        printf("Stack top: %d\n", stack->top->value);
    }

    while(stack->top) {
        Node* temp = popStack(stack);
        free(temp);
    }

    free(stack);
    return 0;
}