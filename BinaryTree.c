#include <stdlib.h>
#include <stdio.h>

typedef struct Leaf {
    int value;
    struct Leaf* left;
    struct Leaf* right;
} Leaf;

typedef struct BinarySearchTree {
    struct Leaf* root;
} BinarySearchTree;

BinarySearchTree* createBinarySearchTree() {
    BinarySearchTree* newBinarySearchTree = (BinarySearchTree*) malloc(sizeof(BinarySearchTree));
    if (newBinarySearchTree == NULL) {
        printf("It was not possible to allocate memory\n");
        exit(1);
    }
    newBinarySearchTree->root = NULL;
    return newBinarySearchTree;
}

Leaf* createLeaf(int value) {
    Leaf* newLeaf = (Leaf*) malloc(sizeof(Leaf));
    if (newLeaf == NULL) {
        printf("It was not possible to allocate memory\n");
        exit(1);
    }
    newLeaf->left = NULL;
    newLeaf->right = NULL;
    newLeaf->value = value;
    return newLeaf;
}

void insertRecursively(Leaf** target, Leaf** newLeaf) {
    Leaf* targetPointer = *target;
    Leaf* newLeafPointer = *newLeaf;


    if (targetPointer == NULL) {
        *target = newLeafPointer;
        return;
    }

    int value = newLeafPointer->value;

    if (targetPointer->value > value) {
        insertRecursively(&targetPointer->left, &newLeafPointer);
    } else {
        insertRecursively(&targetPointer->right, &newLeafPointer);
    }

}

void insert(BinarySearchTree** bst, int value) {
    Leaf* newLeaf = createLeaf(value);
    BinarySearchTree* bstPointer = *bst;

    if (bstPointer->root == NULL) {
        bstPointer->root = newLeaf;
        return;
    }

    insertRecursively(&bstPointer->root, &newLeaf);

    return;
}

void printBinaryTreeRecursively(Leaf** leaf, int space) {
    Leaf* leafPointer = *leaf;
    int COUNT = 5;

    if (leafPointer == NULL) {
        return;
    }

    space += COUNT;

    printBinaryTreeRecursively(&leafPointer->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", leafPointer->value);
    printBinaryTreeRecursively(&leafPointer->left, space);
}

void printTree(BinarySearchTree** bst) {
    if((*bst)->root == NULL) {
        return;
    }
    printBinaryTreeRecursively(&(*bst)->root, 0);
}

Leaf* findMin(Leaf* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void removeLeafRecursively(Leaf** leaf, int value) {
    if (*leaf == NULL) return;

    Leaf* leafPointer = *leaf;

    if (value < leafPointer->value) {
        removeLeafRecursively(&(leafPointer->left), value);
    }
    else if (value > leafPointer->value) {
        removeLeafRecursively(&(leafPointer->right), value);
    }
    else {
        if (leafPointer->left == NULL && leafPointer->right == NULL) {
            free(leafPointer);
            *leaf = NULL;
        }
        else if (leafPointer->left == NULL) {
            Leaf* temp = *leaf;
            *leaf = leafPointer->right;
            free(temp);
        }
        else if (leafPointer->right == NULL) {
            Leaf* temp = *leaf;
            *leaf = leafPointer->left;
            free(temp);
        }
        else {
            Leaf* minNode = findMin(leafPointer->right);
            leafPointer->value = minNode->value;
            removeLeafRecursively(&(leafPointer->right), minNode->value);
        }
    }
}

void removeLeaf(BinarySearchTree** bst, int value) {
    if ((*bst)->root == NULL) {
        printf("The BinaryTree is empty! \n");
        return;
    }
    removeLeafRecursively(&(*bst)->root, value);
    return;
}

int main() {
    BinarySearchTree* bst = createBinarySearchTree();
    insert(&bst, 2);
    insert(&bst, 1);
    insert(&bst, 3);
    insert(&bst, 7);
    insert(&bst, 5);
    insert(&bst, 4);

    removeLeaf(&bst, 3);

    printf("Binary tree: \n");
    printTree(&bst);

    printf("right element: %d\n", bst->root->right->value);

    return 0;
}