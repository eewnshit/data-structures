#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Group {
    char* label;
    int value;
} Group;

typedef struct UnionFind {
    size_t capacity;
    size_t size;
    Group** groups;
} UnionFind;

Group* createGroup(char* label, int value) {
    Group* newGroup = (Group*) malloc(sizeof(Group));
    if (newGroup == NULL) {
        printf("It was not possible to allocate memory\n");
        exit(1);
    }
    newGroup->label = label;
    newGroup->value = value;
    return newGroup;
}

UnionFind* createUnionFind(size_t initialCapacity) {
    UnionFind* newUnionFind = (UnionFind*) malloc(sizeof(UnionFind));
    if (newUnionFind == NULL) {
        printf("It was not possible to allocate memory\n");
        exit(1);
    }

    newUnionFind->groups = (Group**) malloc(initialCapacity * sizeof(Group*));
    newUnionFind->capacity = initialCapacity;
    newUnionFind->size = 0;
    return newUnionFind;
}

void resizeUnionFind(UnionFind** unionFind, size_t newCapacity) {
    Group** newGroups = (Group**) malloc(newCapacity * (sizeof(Group*)));

    if (newGroups == NULL) {
        printf("It was not possible to allocate memory\n");
        exit(1);
    }

    UnionFind* unionFindPointer = *unionFind;

    memcpy(newGroups, unionFindPointer->groups, newCapacity * sizeof(Group*));
    free(unionFindPointer->groups);

    unionFindPointer->groups = newGroups;
    unionFindPointer->capacity = newCapacity;
}

void addGroupToUnionFind(UnionFind** unionFind, Group** group) {

    UnionFind* ufPointer = *unionFind;

    if(ufPointer->size >= ufPointer->capacity) {
        resizeUnionFind(&ufPointer, ufPointer->capacity * 2);
        printf("Old Capacity: %zu - New Capacity: %zu\n", ufPointer->capacity/2, ufPointer->capacity);
    }

    Group* groupPointer = *group;

    if(ufPointer == NULL || groupPointer == NULL) {
        printf("Some given value is NULL\n");
        return;
    }

    ufPointer->groups[ufPointer->size++] = groupPointer;
}

void unionGroups(UnionFind** uf, size_t g1, size_t g2) {
    UnionFind* ufPointer = *uf;
    
    if(ufPointer->size <= 1) {
        printf("The UnionFind don't have enough elements\n");
        return;
    }
    
    Group* g1Pointer = ufPointer->groups[g1];
    Group* g2Pointer = ufPointer->groups[g2];

    if(g1Pointer == NULL || g2Pointer == NULL) {
        printf("Some group don't exist!\n");
        return;
    }

    g2Pointer->label = g1Pointer->label;
}

Group* find(UnionFind** uf, size_t gIndex) {
    UnionFind* ufPointer = *uf;
    
    if(ufPointer->groups[gIndex] == NULL) {
        printf("Don't exist a group at index %zu\n", gIndex);
        return NULL;
    }

    return ufPointer->groups[gIndex];
}

void printUnionFind(UnionFind* uf) {
    printf("UnionFind with %zu elements: \n", uf->size);
    for(size_t i = 0; i < uf->size; i++) {
        printf("Group %zu - [%s]: %d\n", i, uf->groups[i]->label, uf->groups[i]->value);
    }
}

int main() {
    UnionFind* uf = createUnionFind(1);
    Group* group = createGroup("blue", 5);
    Group* group2 = createGroup("red", 2);

    addGroupToUnionFind(&uf, &group);
    addGroupToUnionFind(&uf, &group2);
    unionGroups(&uf, 0, 1);
    
    Group* secondGroup = find(&uf, 1);

    if(secondGroup != NULL) {
        printf("Label of second group: %s\n", secondGroup->label);
    } 


    printUnionFind(uf);
}