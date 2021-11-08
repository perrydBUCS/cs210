//
// Created by Perry Donham on 2/28/21.
//

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "list.h"
#include "node.h"

typedef struct node {
    int value;
    node *next;
} node;

//Making these global since they are used in several functions
//
node *HEAD = NULL;  //top of the list
node *walker = NULL;
node *upstream = NULL;

//Add a pre-constructed node to the list. Start at HEAD and look for
//a node with next->NULL. That's the end of the list. Add the new one there.
//
void addNode(node *node) {
    if (!HEAD) {
        HEAD = node;  //this is the first entry in the list
    } else {
        walker = HEAD; //start at the top
        while (walker->next) {
            walker = walker->next; //inspect the next node
        }
        walker->next = node; //end of the list, place new node here
    }
}

//Given a value, find the first node holding that value and return it
//
node *findNode(int value) {
    if (!HEAD) {
        puts("List is empty, unable to locate node");
        return NULL;
    } else {
        walker = HEAD; //start at the top
        while (walker) {
            if (walker->value == value) {
                return walker;      //Found it! Return the pointer.
            } else {
                walker = walker->next;
            }
        }
        //at this point we've walked the entire list and haven't found the item
        //so return a NULL
        return NULL;
    }
}

bool deleteNode(int value) {
    if (!HEAD) {
        return false; //Case 0, the list is empty, node not deleted
    }
    walker = upstream = HEAD;  //start at the top
    if (walker->value == value) {  //Case 1, node is at the top
        HEAD = walker->next;
        free(walker);
        walker = NULL;
        return true;
    }

    //Move the pointers up one, since we know the value is not the first
    //this splits walker and upstream (which still points to HEAD)
    //
    walker = walker->next;

    while (walker) { //walker, upstream still points to HEAD on first iteration
        if (walker->value == value) {
            upstream->next = walker->next; //splices out found node
            free(walker);
            walker = NULL;
            return true;
        }
        upstream = walker;          //move both pointers up in tandem
        walker = walker->next;
    }
    return false; //if we reach this point, the node was not found
}

void printList(void) {
    if (!HEAD) {
        puts("List is empty");
    } else {
        //Using a for loop here to show that we can manage
        //walking the list with just a few lines of code
        //
        for (walker = HEAD; walker; walker = walker->next) {
            printf("%d ", walker->value);
        }
        printf("\n");
    }
}

void deleteLargestNodes(void) {
    //Find the largest value
    if (!HEAD) {
        puts("List is empty");
    } else {
        int largest = HEAD->value;
        walker = HEAD;                  //start at the top
        while (walker) {
            largest = (walker->value > largest) ? walker->value : largest;
            walker = walker->next;      //Check the next node
        }
        //Now delete them
        node *deleteMe = NULL;

        //Here we'll just call findNode until it returns a null,
        //deleting any nodes that are found
        //
        while ((deleteMe = (findNode(largest)))) {
            deleteNode(deleteMe->value);
            printf("Deleted node with %d\n", largest);
        }
    }
}

int countList(void) {
    int listCount = 0;
    //Start at the top
    if (HEAD) {
        walker = HEAD;
        //Again, the for loop is the quickest way to write the function
        //
        for (walker = HEAD; walker; walker = walker->next) {
            listCount++;
        }
    }
    return listCount;
}

int doSwaps(void) {
    node *temp = NULL;
    node *upstream = NULL;
    int counter = 0;
    if (!HEAD) {
        puts("List is empty, not sorting");
        return 0;
    }
    //Start at the top - we'll go all the way through the
    //list once and report the number of swaps. When the
    //count is zero, we're sorted
    //
    walker = HEAD;
    upstream = HEAD;

    while (walker->next) { //Case 1: Swap HEAD
        //check walker->next->val to see if a swap is needed
        if (walker->value > walker->next->value) {
            temp = walker->next;            //swap nodes
            walker->next = temp->next;      //   |
            temp->next = walker;            //   |
            if (walker == HEAD) {           //HEAD doesn't have an upstream node
                HEAD = temp;                //  so we don't need to link it, just
                upstream = temp;            //  adjust HEAD
            } else {
                upstream->next = temp;      //This is the non-HEAD swap, link
                upstream = temp;            //  the upstream node in and move up one
            }
            counter++;
        } else {
            upstream = walker;              //If there was no swap, just move the
            walker = walker->next;          //pointers up by one
        }
    }
    printList();
    return counter;
}

//To sort the list, call doSwaps until it reports no swaps
//
void sortList(void) {
    int count = 0;
    do {
        count = doSwaps();
    } while (count != 0);
}