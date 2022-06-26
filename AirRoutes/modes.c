#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include"modes.h"
#include"List.h"
#include"AirRoutes.h"
#include"heap.h"

/***************************************************************
 * modeA0()
 *
 * Argumentos: listaHeader - apontador para primeiro elemento
                de uma lista com adjacências
 *
 * Retorna: número de elementos da lista

 * Descrição: percorre a lista até NULL, somando o número de
    elementos.
 *
 ***************************************************************/
int modeA0 (LinkedList* listaHeader)//conta numero de adjacencias de determinado nodo
{
    int count = 0;
    LinkedList* aux;
    aux = listaHeader;

    while(aux != NULL)
    {
        count++;
        aux = aux->next;
    }
    if(count==0) return -1;
    else return count;
}

/***************************************************************
 * modeB0()
 *
 * Argumentos: arestas - apontador para o grafo (lista de
                                                adjacências)
                argumento1, argumento2 - vertices dos quais
                se pretende verificar a adjacência
 *
 * Retorna: -1 - vértices não são adjacentes
            val - custo da aresta caso sejam adjacentes;

 * Descrição: percorre a lista de um dos elementos até encontrar
    o outro e retorna o custo da aresta.
 *
 ***************************************************************/
double modeB0 (LinkedList** arestas,int argumento1,int argumento2) //verifica adjacencia de dois vertices (procura argumento2 na lista de argumento1)
{
    LinkedList* aux;
    aux = arestas[argumento1];
    Aval* auxStruct;

    while(aux != NULL)
    {
        auxStruct = aux->this;
        if(auxStruct->Adj == argumento2) return auxStruct->Val;
        aux = aux->next;
    }
    return -1;
}

/***************************************************************
 * modeC0()
 *
 * Argumentos: arestas - apontador para o grafo (lista de
                                                adjacências)
                argumento1 - vértice que se pretende verificar
                a inclusão num clique de 3 vértices
                func - modo de funcionamento pretendido (C0 ou D0)
                V - número de vértices do grafo
 *
 * Retorna: -1 - vértice não pertence ao grafo
            0 - vértice não está em nenhuma clique
            1 - modo C0 - vértice pertence a pelo menos uma clique
            ncliques - modo D0 - número de cliques a que o vértice
                pertence.

 * Descrição: verifica as adjacências do vértice dado como
    argumento e as suas respetivas adjacências. caso uma destas
    retorne ao argumento, então forma-se uma clique.
 *
 ***************************************************************/

int modeCD0 (LinkedList** arestas, int argumento1, char* func, int V)
{
    int *adjacencias, nadj=0, i, j=1, ncliques=0;
    LinkedList* aux;
    Aval* auxStruct;
    adjacencias = (int*) malloc(sizeof(int)*nadj);
    if(adjacencias == NULL) exit(0);

    if(arestas[argumento1] == NULL) return -1;

    aux = arestas[argumento1];

    while(aux != NULL) //percorre lista do nodo pretendido e guarda as suas adjacencias num vetor
    {
        nadj++;
        auxStruct = aux->this;
        adjacencias = (int*) realloc (adjacencias, (sizeof(int)*nadj));
        if(adjacencias == NULL) exit(0);
        adjacencias[nadj-1] = auxStruct->Adj;
        aux = aux->next;
    }

    if(nadj == 0) return -1;

    for(i=0;i<nadj-1;i++)
    {
        aux = arestas[adjacencias[i]];
        while(aux != NULL)
        {
            auxStruct = aux->this;
            for(j=i+1;j<nadj;j++)
            {
                if((auxStruct->Adj) == (adjacencias[j]))
                {
                    if(strcmp(func, "C0") == 0)
                    {
                        ncliques=1;
                    }
                    if(strcmp(func, "D0") == 0)
                    {
                        ncliques++;
                    }
                }
            }
            aux = aux->next;
        }
    }

    free(adjacencias);
    return ncliques;


}

/***************************************************************
 * modeA1()
 *
 * Argumentos: arestas - apontador para o grafo (lista de
                                                adjacências)
                in - vértice inicial
                st - arestas do backbone
                val - valores das arestas do backbone
                V - número de vértices
                visitados - vetor dos vértices visitados
 *
 * Retorna: void

 * Descrição: Realiza o algoritmo de Prim utilizando um acervo
    para representar a franja. Coloca os resultados em st e val.
 ***************************************************************/
void modeA1 (LinkedList** arestas, int in, int st[], double val[], int V, int visitados[])
{
    int i,j;
    LinkedList* auxlink;
    Aval* auxstr;

    fila = PQinit(V);
    if (fila == NULL) exit(0);

    for(i=0;i<hsize;i++)
    {
        if(visitados[i] == 0)
        {
            st[i] = -1;
            val[i] = DBL_MAX;
            PQinsert(i, val[i]);
        }
    }
    val[in] = 0;
    PQdec(in, val[in]);

    while(!PQempty(fila))
    {
        i = PQdelmin(fila, hsize);
        if(val[i] != DBL_MAX)
        {
            visitados[i] = 1;
            for(auxlink = arestas[i]; auxlink != NULL; auxlink = auxlink->next)
            {
                auxstr = (Aval*) auxlink->this;
                if(val[j=auxstr->Adj] > auxstr->Val && visitados[j] != 1)
                {
                    val[j] = auxstr->Val;
                    PQdec(j, val[j]);
                    st[j] = i;
                }
            }
        }
    }
    free(fila);
}

/***************************************************************
 * modeE1()
 *
 * Argumentos: backbone - arestas do backbone representadas num vetor
                posicao - posicão do vetor em que está a aresta a
                    remover
                arestas - grafo (lista de adjacências)
                V - número de vértices do grafo
 *
 * Retorna: alternativa - aresta que substitui a presente em
    backbone[posicao] caso esta seja removida

 * Descrição: calcula o backbone na ausência da aresta a ignorar
    e verifica qual a que substitui, colocando-a em "alternativa"
    Caso não exista todos os valores de "alternativa" são
    colocados a 0.
 *
 ***************************************************************/

Lin modeE1(Lin* backbone, int posicao, LinkedList** arestas, int V)
{
    int i, j, aAtual, bAtual, *sttemp, *visitadostemp, posSub=0;
    double *valtemp;
    Lin *backbone2, alternativa;

    if(backbone[posicao].val == 0)
    {
        alternativa.a = 0;
        alternativa.b = 0;
        alternativa.val = 0;
        return alternativa;
    }

    sttemp = (int*) malloc(V*sizeof(int));
    if(sttemp == NULL) exit(0);
    visitadostemp = (int*) malloc(V*sizeof(int));
    if(visitadostemp == NULL) exit(0);
    valtemp = (double*) malloc(V*sizeof(double));
    if(valtemp == NULL) exit(0);


    for(i=0;i<V;i++) visitadostemp[i] = 0;

    aAtual = backbone[posicao].a;
    bAtual = backbone[posicao].b;

    for(i=0;i<V;i++)
    {
        if(visitadostemp[i] == 0) PrimIgnore(arestas, i, sttemp, valtemp, V, visitadostemp, aAtual-1, bAtual-1);
    }

    backbone2 = createBackbone(sttemp, valtemp, V);

    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            if(backbone2[i].a == backbone[j].a && backbone2[i].b == backbone[j].b)
            {
                break;
            }
            if(j==V-1)
            {
                posSub = i;
            }
        }
        if (posSub != 0) break;
    }
    if(posSub != 0)
    {
        alternativa.a = backbone2[posSub].a;
        alternativa.b = backbone2[posSub].b;
        alternativa.val = backbone2[posSub].val;
    }
    else
    {
        alternativa.a = 0;
        alternativa.b = 0;
        alternativa.val = 0;
    }

    free(sttemp);
    free(valtemp);
    free(visitadostemp);
    free(backbone2);

    return alternativa;

}

/***************************************************************
 * PrimIgnore()
 *
 * Argumentos: arestas - apontador para o grafo (lista de
                                                adjacências)
                in - vértice inicial
                st - arestas do backbone
                val - valores das arestas do backbone
                V - número de vértices
                visitados - vetor dos vértices visitados
                ignore1, ignore2- vértice a ignorar na determinação
                    do backbone
 *
 * Retorna: void

 * Descrição: Realiza o algoritmo de Prim utilizando um acervo
    para representar a franja. Ignora a aresta entre ignore1 e
    ignore2.
 ***************************************************************/
void PrimIgnore (LinkedList** arestas, int in, int st[], double val[], int V, int visitados[], int ignore1, int ignore2)
{
    int i,j;
    LinkedList* auxlink;
    Aval* auxstr;

    fila = PQinit(V);
    if (fila == NULL) exit(0);

    for(i=0;i<hsize;i++)
    {
        if(visitados[i] == 0)
        {
            st[i] = -1;
            val[i] = DBL_MAX;
            PQinsert(i, val[i]);
        }
    }
    val[in] = 0;
    PQdec(in, val[in]);

    while(!PQempty(fila))
    {
        i = PQdelmin(fila, hsize);
        if(val[i] != DBL_MAX)
        {
            visitados[i] = 1;
            for(auxlink = arestas[i]; auxlink != NULL; auxlink = auxlink->next)
            {
                auxstr = (Aval*) auxlink->this;
                if(val[j=auxstr->Adj] > auxstr->Val && visitados[j] != 1)
                {
                    if((i == ignore1 && j == ignore2) || (i == ignore2 && j == ignore1));
                    else
                    {
                        val[j] = auxstr->Val;
                        PQdec(j, val[j]);
                        st[j] = i;
                    }
                }
            }
        }
    }
    free(fila);
}

Lin searchCheapest(LinkedList** arestas, int lista, int argumento1)
{
    int tempA=0, tempB=0, i;
    double tempval = DBL_MAX;
    LinkedList* auxptr;
    Aval *auxstr;
    Lin auxlin;

    auxptr = arestas[lista];

    while(auxptr != NULL)
    {
        auxstr = auxptr->this;
        if(auxstr->Val < tempval && auxstr->Adj != argumento1)
        {
            tempval = auxstr->Val;
            tempA = lista+1;
            tempB = auxstr->Adj+1;
        }
        auxptr = auxptr->next;
    }

    if(tempA != 0)
    {
        if(tempB < tempA)
        {
            i = tempB;
            tempB = tempA;
            tempA = i;
        }
        auxlin.a = tempA;
        auxlin.b = tempB;
        auxlin.val = tempval;
    }
    else
    {
        auxlin.a = 0;
        auxlin.b = 0;
        auxlin.val = 0;
    }

    return auxlin;
}

/***************************************************************
 * createBackbone()
 *
 * Argumentos: st - apontador
               val - apontador
               V - vértice
 *
 * Retorna: veclin

 * Descrição: cria um vetor de estruturas em que cada elemento
    representa uma aresta do backbone
 *
 ***************************************************************/

Lin* createBackbone(int *st, double *val, int V)
{
    int i, j;


    Lin *veclin = (Lin*) malloc (V*sizeof(Lin));
    if(veclin == NULL) exit(0);

    for(i=0;i<V;i++)
    {
        veclin[i].a = 0;
        veclin[i].b = 0;
        veclin[i].val = 0;
    }

    for(i=0;i<V;i++)
    {
        if (st[i] != -1)
        {
            int aa, bb;

            if ((i+1) < (st[i]+1))
            {
                aa= i+1;
                bb= (st[i]+1);
            }
            else
            {
                aa = (st[i]+1);
                bb = i+1;
            }

            veclin[i].a= aa;
            veclin[i].b= bb;
            veclin[i].val = val[i];
        }
    }

    Lin aux;

    for(i=0;i<V;i++)  /*Insertion Sort*/
    {
        for(j=i;j>0;j--)
        {
            if(veclin[j-1].a > veclin[j].a)
            {
                aux = veclin[j];
                veclin[j] = veclin[j-1];
                veclin[j-1] = aux;
            }
            if(veclin[j-1].a == veclin[j].a)
            {
                if(veclin[j-1].b > veclin[j].b)
                {
                    aux = veclin[j];
                    veclin[j] = veclin[j-1];
                    veclin[j-1] = aux;
                }
            }
        }
    }

    return veclin;
}

void InsertionSort (Lin* veclin, int tamanho)
{
    int i, j;
    Lin aux;

    for(i=0;i<tamanho;i++)  /*Insertion Sort*/
    {
        for(j=i;j>0;j--)
        {
            if(veclin[j-1].a > veclin[j].a)
            {
                aux = veclin[j];
                veclin[j] = veclin[j-1];
                veclin[j-1] = aux;
            }
            if(veclin[j-1].a == veclin[j].a)
            {
                if(veclin[j-1].b > veclin[j].b)
                {
                    aux = veclin[j];
                    veclin[j] = veclin[j-1];
                    veclin[j-1] = aux;
                }
            }
        }
    }
}



