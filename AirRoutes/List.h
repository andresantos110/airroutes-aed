#ifndef ListHeader
#define ListHeader

#include"AirRoutes.h"
#include<stdio.h>

LinkedList* initLinkedList(void);

LinkedList* insertUnsortedLinkedList(LinkedList * next, Item this);

LinkedList** PreencheLista (LinkedList**, FILE*, int, int);

void FreeList(LinkedList *first, void (*FreeItem)(Item));

void FreeItem(Item);

int CompareItem (Item, Item);

LinkedList* insertSortedLinkedList(LinkedList *first, Item item, int (* compareItems) (Item it1, Item it2));

int removeAdj(LinkedList** arestas, int argumento1, int argumento2);

#endif
