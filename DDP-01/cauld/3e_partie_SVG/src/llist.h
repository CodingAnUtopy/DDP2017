#ifndef LLIST_H
#define LLIST_H

#include <stdio.h>

#include "error.h"

typedef struct Node Node;

Node *initList(void);
int pushBack(Node **list, char *data);
void freeList(Node *list);
void printList(Node *list, FILE *fd);
void copyListToBuffer(Node *list, char *buffer);

#endif // LLIST_H
