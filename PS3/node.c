//
// Created by Perry Donham on 2/28/21.
//

#include <stdlib.h>
#include <stdio.h>
#include "node.h"

typedef struct node {
    int value;
    char operator;
    node *next;
} node;


node *createNode(int value) {
    node *newNode = (struct node*) malloc(sizeof(node));
    if (newNode) {
        newNode->value = value;
        newNode->next = NULL;
    } else {
        puts("Unable to allocate memory for a node.\n");
        exit(-1);
    }
    return newNode;


}
