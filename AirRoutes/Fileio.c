#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include"modes.h"
#include"List.h"
#include"AirRoutes.h"
/***************************************************************
 * checkExtension()
 *
 * Argumentos: filename
 *
 * Retorna: -1 se não tem a extensão correta
 *           0 caso contrário

 * Descrição: verifica se tem a extensão ".routes"
 *
 ***************************************************************/

int checkExtension(char* filename)
{
    char *dot = strrchr(filename, '.');
    if(strcmp(dot, ".routes") != 0) return -1;
    else return 0;

}

/***************************************************************
 * exitFileExtension()
 *
 * Argumentos: filename
               fileinsize
 *
 * Retorna:  exitFileName - nome do ficheiro de saída com a
    extensão correta

 * Descrição: recebe o nome do ficheiro de entrada, remove a
    extensão de entrada e coloca a de saída, retorna.
 *
 ***************************************************************/
char* exitFileExtension(char *filename, int fileinsize)
{
    int filenamesize;
    char* exitFileName;
    filenamesize = fileinsize - 7;

    exitFileName = (char*) malloc ((filenamesize+8) * sizeof(char));

    if(exitFileName == NULL) exit(0);

    strncpy(exitFileName, filename, filenamesize);
    exitFileName[filenamesize] = '\0';
    strcat(exitFileName, ".bbones");

    return exitFileName;
}
/***************************************************************
 * writeToFile()
 *
 * Argumentos: fileout - apontador para o ficheiro de saída
               V - número de vértices
               E - número de arestas
               func - modo de funcionamento
               argumento1 - primeiro argumento
               argumento2 - segundo argumento
               res - resolução caso exista
 *
 * Retorna: void
 *
 * Descrição: imprime os resultados da primeira fase de submissões
    (modos A0, B0, C0, D0)
 *
 ***************************************************************/
void writeToFile(FILE *fileout, int V, int E, char* func, int argumento1, int argumento2, double res)
{
    if(strcmp(func, "B0") == 0)
    {
        if(res == -1) fprintf(fileout, "%d %d %s %d %d %.0lf \r\n", V, E, func, argumento1, argumento2, res);

        else fprintf(fileout, "%d %d %s %d %d %.2lf \r\n", V, E, func, argumento1, argumento2, res);

        fprintf(fileout, "\r\n");
    }
    if(strcmp(func, "A0") || strcmp(func, "C0") || strcmp(func, "D0"))
    {
        fprintf(fileout, "%d %d %s %d %.0lf \r\n", V, E, func, argumento1, res);

        fprintf(fileout, "\r\n");
    }
    return;

}

/***************************************************************
 * printA1()
 *
 * Argumentos: veclin - representação em lista do backbone
               V - número de vértices
               E - número de arestas
               func - modo de funcionamento
               narestas - numero de arestas do backbone
               total - valor do backbone
               fout - apontador para o ficheiro de saída
 *
 * Retorna: void
 *

 * Descrição: imprime o backbone de acordo com o pedido para
    a variante A1.
 *
 ***************************************************************/

void printA1 (Lin* veclin, int V, int E, char *func, int narestas, double total, FILE *fout)
{
    int i;
    fprintf(fout, "%d %d %s %d %.2lf\n", V, E, func, narestas, total);
    for(i=0;i<V;i++){
        if(veclin[i].val != 0) fprintf(fout, "%d %d %.2lf\n", veclin[i].a ,veclin[i].b,veclin[i].val);
    }
    fprintf(fout, "\r\n");
}

/***************************************************************
 * printE1()
 *
 * Argumentos: veclin - representação em lista do backbone
               alternatives - vetor das arestas alternativas
               V - número de vértices
               E - número de arestas
               func - modo de funcionamento
               narestas - numero de arestas do backbone
               total - valor do backbone
               fout - apontador para o ficheiro de saída
 *
 * Retorna: void
 *

 * Descrição: imprime o backbone original e as rotas alternativas
    para cada uma das arestas do backbone original.
 *
 ***************************************************************/
void printE1 (Lin* veclin, Lin* alternatives, int V, int E, char *func, int narestas, double total, FILE *fout)
{
    int i;
    fprintf(fout, "%d %d %s %d %.2lf\n", V, E, func, narestas, total);

    for(i=0;i<V;i++){
        if(veclin[i].val != 0 && alternatives[i].val != 0) fprintf(fout, "%d %d %.2lf %d %d %.2lf\n", veclin[i].a, veclin[i].b, veclin[i].val, alternatives[i].a, alternatives[i].b, alternatives[i].val);
        if(veclin[i].val != 0 && alternatives[i].val == 0) fprintf(fout, "%d %d %.2lf -1\n", veclin[i].a, veclin[i].b, veclin[i].val);
    }
    fprintf(fout, "\r\n");
}
