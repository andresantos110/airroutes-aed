#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

extern Item* fila;
extern int current;
extern int hsize;

Item* PQinit(int V);

void PQinsert(int v, double prio);

void FixUp(Item *fila, int index);

void FixDown(Item *fila, int index);

int compareLess (Item el1, Item el2);

int compareMore (Item el1, Item el2);

void PQdec(int index, double newval);

void freeHeap(Item *fila);

int PQempty();

int PQdelmin();

#endif // HEAP_H_INCLUDED
