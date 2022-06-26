#ifndef MODES_INCLUDED
#define MODES_INCLUDED
#include"AirRoutes.h"

int modeA0 (LinkedList* listaHeader);

double modeB0 (LinkedList** arestas,int argumento1,int argumento2);

int modeCD0 (LinkedList** arestas, int argumento1, char* func, int V);

void modeA1 (LinkedList** arestas, int in, int st[], double val[], int V, int visitados[]);

Lin modeE1(Lin* backbone, int posicao, LinkedList** arestas, int V);

void PrimIgnore (LinkedList** arestas, int in, int st[], double val[], int V, int visitados[], int ignore1, int ignore2);

Lin* createBackbone(int *st, double *val, int V);

Lin searchCheapest(LinkedList** arestas, int lista, int argumento1);

void InsertionSort (Lin* veclin, int tamanho);

#endif // MODES_INCLUDED
