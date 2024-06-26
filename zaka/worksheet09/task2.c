#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int value;
    struct Item *next;
} Item;

Item *statetab[31];

int hash(int value) {
    return value % 31;
}

void initHashTable() {
    for (int i = 0; i < 31; i++) {
        statetab[i] = NULL;
    }
}

int insert(int value) {
    int index = hash(value);
    Item *newItem = (Item *)malloc(sizeof(Item));
    if (!newItem) return -1; // memory allocation failed
    newItem->value = value;
    newItem->next = NULL;

    Item *current = statetab[index];
    while (current != NULL) {
        if (current->value == value) {
            free(newItem);
            return -1; // value already exists
        }
        current = current->next;
    }

    newItem->next = statetab[index];
    statetab[index] = newItem;
    return 0;
}

int search(int value) {
    int index = hash(value);
    Item *current = statetab[index];
    while (current != NULL) {
        if (current->value == value) {
            return 0; // value found
        }
        current = current->next;
    }
    return -1; // value not found
}

int delete(int value) {
    int index = hash(value);
    Item *current = statetab[index];
    Item *prev = NULL;

    while (current != NULL) {
        if (current->value == value) {
            if (prev == NULL) {
                statetab[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return 0; // value deleted
        }
        prev = current;
        current = current->next;
    }
    return -1; // value not found
}

void printCollisions() {
    for (int i = 0; i < 31; i++) {
        int count = 0;
        Item *current = statetab[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
        if (count > 1) {
            printf("Collision at index %d: %d items\n", i, count);
        }
    }
}

int main() {
    initHashTable();

    // Insert numbers from 0 to 99
    for (int i = 0; i < 100; i++) {
        insert(i);
    }

    // Search for each number from 0 to 99
    for (int i = 0; i < 100; i++) {
        if (search(i) == 0) {
            printf("Value %d found in hash table.\n", i);
        } else {
            printf("Value %d not found in hash table.\n", i);
        }
    }

    // Print collisions
    printCollisions();

    return 0;
}
