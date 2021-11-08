//
// Created by Perry Donham on 2/28/21.
//

#ifndef PS3_LIST_H
#define PS3_LIST_H
#include "node.h"

void addNode(node *node);
node *findNode(int value);
bool deleteNode (int value);
void printList(void);
void deleteLargestNodes(void);
int countList(void);
void sortList(void);
int doSwaps(void);
#endif //PS3_LIST_H
