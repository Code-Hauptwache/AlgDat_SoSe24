#include <stdio.h>
#include <stdlib.h>

void initHashTable();
int insert(int value);
int search(int value);
int delete(int value);

typedef struct Item
{
    int value;
    struct Item *next;
} Item;

Item *statetab[31];

int main()
{
    initHashTable();

    // Example usage
    insert(10);
    insert(41); // This will hash to the same index as 10
    printf("Search 10: %d\n", search(10)); // Should print 0 (found)
    printf("Search 41: %d\n", search(41)); // Should print 0 (found)
    printf("Delete 10: %d\n", delete(10)); // Should print 0 (deleted)
    printf("Search 10: %d\n", search(10)); // Should print -1 (not found)
    printf("Search 41: %d\n", search(41)); // Should print 0 (found)
    printf("Delete 41: %d\n", delete(41)); // Should print 0 (deleted)
    printf("Search 41: %d\n", search(41)); // Should print -1 (not found)

    return 0;
}

int hash(int value)
{
    return value % 31;
}

void initHashTable()
{
    for (int i = 0; i < 31; i++)
    {
        statetab[i] = NULL;
    }
}

int insert(int value)
{
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

int search(int value)
{
    int index = hash(value);
    Item *current = statetab[index];
    while (current != NULL)
    {
        if (current->value == value)
        {
            return 0; // value found
        }
        current = current->next;
    }
    return -1; // value not found
}

int delete(int value)
{
    int index = hash(value);
    Item *current = statetab[index];
    Item *prev = NULL;

    while (current != NULL) {
        if (current->value == value)
        {
            if (prev == NULL)
                statetab[index] = current->next;
            else
                prev->next = current->next;
            free(current);
            return 0; // value deleted
        }
        prev = current;
        current = current->next;
    }
    return -1; // value not found
}