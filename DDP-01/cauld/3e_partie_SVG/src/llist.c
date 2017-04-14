#include "llist.h"

#include <stdlib.h>
#include <string.h>

struct Node
{
    char *data;
    Node *next;
};


Node *initList(void)
{
    return NULL;
}

int pushBack(Node **list, char *data)
{
    Node *newNode = malloc(sizeof(Node));

    if(!newNode)
    {
        setError(MALLOC_ERROR);
        return ERROR;
    }


    newNode->next = NULL;
    newNode->data = strdup(data);

    if(!newNode->data)
    {
        free(newNode);
        setError(STRDUP_ERROR);
        return ERROR;
    }


    while(*list)
        list = &(*list)->next;

    *list = newNode;

    return SUCCESS;
}

void freeList(Node *list)
{
    while(list)
    {
        Node *next = list->next;
        free(list->data);
        free(list);
        list = next;
    }
}

void printList(Node *list, FILE *fd)
{
    while(list)
    {
        fprintf(fd, "%s\n", list->data);
        list = list->next;
    }
}

void copyListToBuffer(Node *list, char *buffer)
{
    if(list)
    {
        sprintf(buffer, "%s", list->data);
        list = list->next;

        while(list)
        {
            strcat(buffer, list->data);
            list = list->next;
        }
    }
    else
        buffer[0] = '\0';

}
