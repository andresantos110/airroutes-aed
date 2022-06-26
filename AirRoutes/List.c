#include<stdio.h>
#include<stdlib.h>
#include <float.h>

#include"List.h"
#include"AirRoutes.h"
#include"modes.h"

LinkedList * initLinkedList(void)
{
    return NULL;
}

/***************************************************************
 * ()
 *
 * Argumentos: next - apontador para a cabeça da lista
               this - item a inserir na lista
 *
 * Retorna: new - apontador para a nova cabeça da lista

 * Descrição: a função recebe um apontador para uma das listas
    adjacências de um vertice e um item a adicionar. O item é
    colocado na cabeça da lista e é retornado um apontador.
    Função retirada do ficheiro LinkedList.c dado como parte do
    4º lab.
 *
 ***************************************************************/

LinkedList *insertUnsortedLinkedList(LinkedList *next, Item this) /*Função do LAB4*/
{
    LinkedList *new;

    /* Memory allocation */
    new = (LinkedList *) malloc(sizeof(LinkedList));

    /* Check memory allocation errors */
    if(new == NULL)
        return NULL;


    /* Initialize new node */
    new->this = this;
    new->next = next;

    return new;
}

void FreeItem(Item this)
{
    free(this);
}

/***************************************************************
 * FreeList()
 *
 * Argumentos: first - apontador para a cabeça da lista
               FreeItem - apontador para funçao que liberta
               memória alocada para um item
 *
 * Retorna: void

 * Descrição: A função recebe um apontador para a cabeça de uma
    lista e um apontador para a função que permite libertar
    a memória alocada para cada um dos seus elementos. Liberta
    tudo e retorna.
 *
 ***************************************************************/

void FreeList(LinkedList *first, void (*FreeItem)(Item))
{
    LinkedList *aux, *temp;
    aux = first;
    while(aux!=NULL)
    {
        temp=aux;
        aux=aux->next;
        FreeItem(temp->this);
        free(temp);
    }
    return;
}
/***************************************************************
 * PreencheLista()
 *
 * Argumentos: arestas - apontador para a lista de adjacências
               f - apontador para ficheiro de entrada
               E - número de arestas
               V - número de vértices
 *
 * Retorna: arestas - apontador para lista de adjacências

 * Descrição: a função lê os valores presentes no ficheiro e
    cria uma lista de adjacências ordenada.
 *
 ***************************************************************/

LinkedList** PreencheLista (LinkedList** arestas, FILE *f, int E, int V)
{
    Aval *auxstr1;
    Aval *auxstr2;
    int Atual, Aresta, i;
    double Valor;

    for(i=0;i<E;i++)
    {
        if(fscanf(f,"%d",&Atual) != 1) exit(0);
        if(fscanf(f,"%d",&Aresta) != 1) exit(0);
        if(fscanf(f,"%lf",&Valor) != 1) exit(0);

        Atual = Atual - 1;
        Aresta = Aresta - 1;

        auxstr1=(Aval*) malloc (sizeof(Aval));
        if(auxstr1 == NULL) exit(0);

        auxstr2=(Aval*) malloc (sizeof(Aval));
        if(auxstr2 == NULL) exit(0);

        auxstr1->Adj = Aresta;
        auxstr1->Val = Valor;

        arestas[Atual]=insertSortedLinkedList(arestas[Atual], (Item) auxstr1, CompareItem);

        if(arestas[Atual] == NULL) exit(0);

        auxstr2->Adj=Atual;
        auxstr2->Val=Valor;

        arestas[Aresta]=insertSortedLinkedList(arestas[Aresta], (Item) auxstr2, CompareItem);

        if(arestas[Atual] == NULL) exit(0);
    }

return arestas;

}
/***************************************************************
 * CompareItem()
 *
 * Argumentos: item1
               item2
 *
 * Retorna: 0 - valores iguais
            1 - valor de item 1 > valor de item 2
            2 - erro na comparação
            -1 - valor de item 2 > valor de item 1

 * Descrição: compara os valores de dois itens dados como
    argumento.
 *
 ***************************************************************/

int CompareItem (Item item1, Item item2)
{
    Aval *aux1, *aux2;
    aux1 = (Aval*) item1;
    aux2 = (Aval*) item2;
    if(aux1->Val == aux2->Val) return 0;
    if(aux1->Val > aux2->Val) return 1;
    if(aux1->Val < aux2->Val) return -1;
    return 2;
}

/***************************************************************
 * insertSortedLinkedList()
 *
 * Argumentos: first - apontador para a cabeça da lista
               item - item a inserir na lista
               compareItems - função para comparar o novo item
                com os presentes na lista
 *
 * Retorna: apontador para a cabeça da lista

 * Descrição: insere um novo elemento na lista de forma ordenada
    de acordo com a sua prioridade.
    Função retirada do ficheiro LinkedList.c dado como parte do
    4º lab.
 *
 ***************************************************************/

LinkedList * insertSortedLinkedList(LinkedList *first, /*Funcao do lab4*/
                Item item,
                int (* compareItems) (Item it1, Item it2))
{
    LinkedList  *new, *aux;

    /* alloc and check */
    new = (LinkedList *) malloc(sizeof(LinkedList));
    if(new == NULL)
        return NULL;

    new->this = item;           /* Initialize new node  */
    new->next = NULL;

    if (first == NULL)          /* first item in list */
    {
        return new;
    }
    /* list not empty, insertion sort */
    /* insert at head */
    if ((compareItems(item, first->this) <= 0) )
    {
        new->next = first;
        return new;
    }
    /* second etc */
    aux = first;
    while(aux != NULL)
    {
        if (aux->next != NULL)
        {
            if ( compareItems(item, aux->next->this) <= 0 )
            {
                new->next = aux->next;
                aux->next = new;
                return first;
            }
        }
        else        /* none left, insert in tail */
        {
            aux->next = new;
            return first;
        }
        aux = aux->next;
    }
    return NULL;
}

/***************************************************************
 * removeAdj()
 *
 * Argumentos: arestas
               argumento1
               argumento2
 *
 * Retorna: 0 se nao conseguir remover adjacências
            1 se remover apenas uma das adjacências
            2 se remover ambas as adjacencias

 * Descrição: recebe um apontador para a lista de adjacencias e
    os vértices a remover. Remove adjacência da lista de ambos.
 *
 ***************************************************************/

int removeAdj(LinkedList** arestas, int argumento1, int argumento2)
{
    LinkedList *aux1, *aux2;
    int success=0;
    Aval* auxaval;

    aux1 = arestas[argumento1];
    auxaval = aux1->this;
    if(auxaval->Adj == argumento2)
    {
        arestas[argumento1] = aux1->next;
        free(auxaval);
        free(aux1);
        success++;
    }

    while(aux1 != NULL && success == 0)
    {
        aux2 = aux1->next;
        auxaval = aux2->this;
        if(auxaval->Adj == argumento2)
        {
            aux1->next = aux2->next;
            free(auxaval);
            free(aux2);
            success++;
        }
        aux1 = aux1->next;
    }

    aux1 = arestas[argumento2];
    auxaval = aux1->this;
    if(auxaval->Adj == argumento1)
    {
        arestas[argumento2] = aux1->next;
        free(auxaval);
        free(aux1);
        success++;
    }

    while(aux1 != NULL && success == 1)
    {
        aux2 = aux1->next;
        auxaval = aux2->this;
        if(auxaval->Adj == argumento1)
        {
            aux1->next = aux2->next;
            free(auxaval);
            free(aux2);
            success++;
        }
        aux1 = aux1->next;
    }



    return success;

}

