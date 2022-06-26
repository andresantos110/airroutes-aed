#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED
#include"AirRoutes.h"

int checkExtension(char*);

char* exitFileExtension(char *filename, int fileinsize);

void writeToFile(FILE *fileout, int V, int E, char* func, int argumento1, int argumento2, double res);

void printA1 (Lin* veclin, int V, int E, char *func, int narestas, double total, FILE *fout);

void printE1 (Lin* veclin, Lin* alternatives, int V, int E, char *func, int narestas, double total, FILE *fout);

#endif // FILEIO_H_INCLUDED
