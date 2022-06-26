#ifndef MainHeader
#define MainHeader
#include<stdio.h>

typedef void *Item;

typedef struct Aval
    {
        int Adj;
        double Val;
    }Aval;

typedef struct LinkedListStruct LinkedList;

typedef struct Lin
    {
        int a;
        int b;
        double val;
    }Lin;

struct LinkedListStruct
{
    Item this;
    LinkedList *next;
};

#endif
