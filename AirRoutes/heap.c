#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include"modes.h"
#include"List.h"
#include"AirRoutes.h"
#include"Fileio.h"
#include"heap.h"


/******************************************************************************
 * PQinit()
 *
 * Argumentos: V
 *
 * Retorna: apontador para a fila
 *
 * Descrição: aloca memória para um acervo de tamanho V representado através
    de uma fila

 *
 *****************************************************************************/
Item* PQinit(int V)
{
    Item* fila;
    hsize = V;
    fila = (Item *)malloc((hsize+1)*sizeof(Item));
    current = 0;
    return fila;
}
/******************************************************************************
 * PQinsert()
 *
 * Argumentos: v - vértice
 *             prio - custo da aresta para chegar a v
 *
 * Retorna: void
 *
 * Descrição: insere/modifica o vertíce V no acervo com prioridade "prio"
    e coloca este na posição correta através de um FixUp.
 *
 *****************************************************************************/
void PQinsert(int v, double prio)
{
    Aval* auxaval;
    auxaval = (Aval*) malloc (sizeof(Aval));
    auxaval->Adj = v;
    auxaval->Val = prio;

    if(current < hsize)
    {
        fila[current] = (Item*) auxaval;
        FixUp(fila, current);
        current++;
    }
}

/******************************************************************************
 * FixUp()
 *
 * Argumentos: fila - apontador para a estrutura Item
 *             index - índice do elemento a ordenar
 * Retorna: void
 *
 * Descrição: Realiza o FixUp do elemento presente em index, comparando-o
    sucessivamente com o elemento acima até estar na posição correta.
 *
 *****************************************************************************/
void FixUp(Item *fila, int index)
{
    Item* aux;

    while(index > 0 && compareLess(fila[(index-1)/2], fila[index]))
    {
        aux = fila[index];
        fila[index] = fila[(index-1)/2];
        fila[(index-1)/2] = aux;
        index = (index-1)/2;
    }
}

/******************************************************************************
 * FixDown()
 *
 * Argumentos: fila - apontador para a estrutura Item
 *             index - índice do elemento a ordenar
 * Retorna: void
 *
 * Descrição: Realiza o FixDown do elemento presente em index, comparando-o
    sucessivamente com os elementos seus filhos até estar na posição correta.
 *
 *****************************************************************************/
void FixDown(Item *fila, int index)
{
    Item aux;
    int child;

    while(2*index < current-1)
    {
        child = 2*index+1;
        if(child < (current-1) && compareLess(fila[child],fila[child+1])) child++;
        if(!compareLess(fila[index],fila[child])) break;

        aux = fila[index];
        fila[index] = fila[child];
        fila[child] = aux;
        index = child;

    }

}
/******************************************************************************
 * compareLess()
 *
 * Argumentos: el1 - Item 1 cuja prioridade vai ser comparada.
               el2 - Item 2 cuja prioridade vai ser comparada.
 * Retorna: 1 se prioridade de el1 > prioridade el2
            0 se prioridade de el2 >= prioridade el1
 *
 * Descrição: compara a prioridade de 2 elementos para fins de ordenação.
 *
 *****************************************************************************/

int compareLess (Item el1, Item el2)
{
    Aval *auxel1 = (Aval*) el1;
    Aval *auxel2 = (Aval*) el2;
    double aa, bb;
    aa = auxel1->Val;
    bb = auxel2->Val;

    return(aa > bb);
}
/******************************************************************************
 * compareLess()
 *
 * Argumentos: el1 - Item 1 cuja prioridade vai ser comparada.
               el2 - Item 2 cuja prioridade vai ser comparada.
 * Retorna: 1 se prioridade de el1 < prioridade el2
            0 se prioridade de el2 <= prioridade el1
 *
 * Descrição: compara a prioridade de 2 elementos para fins de ordenação.
 *
 *****************************************************************************/

int compareMore (Item el1, Item el2)
{
    Aval *auxel1 = (Aval*) el1;
    Aval *auxel2 = (Aval*) el2;
    double aa, bb;
    aa = auxel1->Val;
    bb = auxel2->Val;

    return(aa < bb);
}
/******************************************************************************
 * PQdec()
 *
 * Argumentos: index - vertice cujo valor será modificado
               newval - novo valor de prioridade de index
 * Retorna: void
 *
 * Descrição: procura o vértice index, altera a sua prioridade e reordena
    o acervo através das funções FixUp e FixDown.
 *
 *****************************************************************************/

void PQdec(int index, double newval)
{
    int i;
    for(i=0;i<current;i++)
    {
        Aval* auxaval = (Aval*) fila[i];
        if(auxaval->Adj == index)
        {
            auxaval->Val = newval;
            fila[i] = (Item*) auxaval;
            FixUp(fila, i);
            FixDown(fila, i);
            break;
        }
    }
}
/******************************************************************************
 * freeHeap()
 *
 * Argumentos: fila

 * Retorna: void

 * Descrição: liberta a memória alocada para os itens da lista e de seguida
    a da própria lista.
 *
 *****************************************************************************/
void freeHeap(Item *fila)
{
    int i;
    for(i=0;i<current;i++)
    {
        free(fila[i]);
    }
    free(fila);
}
/******************************************************************************
 * PQempty()
 *
 * Argumentos:
 * Retorna: 1 - a fila está vazia
            0 - a fila não está vazia
 *
 * Descrição: verifica se a fila ainda tem elementos.
 *
 *****************************************************************************/

int PQempty()
{
    if (fila==NULL || current==0) return 1;
    else return 0;
}

/******************************************************************************
 * PQdel()
 *
 * Argumentos:
 * Retorna: index - indíce do valor eliminado
 *
 * Descrição: Elimina o vértice no topo do acervo (menor custo, maior prioridade)
    e retorna o seu índice.
 *
 *****************************************************************************/
int PQdelmin()
{
    Aval* auxaval = (Aval*) fila[0];
    int index = auxaval->Adj;
    fila[0] = fila[current-1];
    fila[current-1] = (Item*) auxaval;
    free(fila[current-1]);
    current--;
    FixDown(fila, 0);
    return index;
}
