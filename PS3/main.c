#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "node.h"

typedef struct node {
    int value;
    node *next;
} node;


int main() {
    int initialValues[] = {89, 39, 18, 96, 71, 25, 2, 55, 60, -8, 9, 42, 69, 96, 24};
    int initialValuesLength = sizeof(initialValues) / sizeof(*initialValues);
    node *node = NULL, *search = NULL; //always ground new pointers

//PS3.1 Create list
    int *values = initialValues;
    while (initialValuesLength--) {
        if (node = createNode(*values++)) {
            addNode(node);
        }
    }
    printList();

//PS3.2 Delete largest nodes
    deleteLargestNodes();
    printList();

//PS3.3 Count nodes
    printf("\nList has %d nodes\n", countList());

//PS3.4 Sort the list
    puts("Sorting list");
    sortList();
    printList();

    return 0;
}

