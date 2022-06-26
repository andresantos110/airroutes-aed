#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include"modes.h"
#include"List.h"
#include"AirRoutes.h"
#include"Fileio.h"

Item* fila;
int current;
int hsize;

int main(int argc,char *argv[])
{
    FILE *f = NULL, *fout = NULL;
    int V, E, fileinsize, argumento1, argumento2, i, j;
    char func[3], *filename, *exitFileName;
    struct LinkedListStruct **arestas;
    double res;

    int *st1, *st2, *visitados;
    double *val1, *val2;

    if(argc != 2) exit(0);

    fileinsize = strlen(argv[1]);
    filename = (char*) malloc (sizeof(char)*(fileinsize + 1));

    if(filename == NULL) exit(0);

    strcpy (filename, argv[1]);

    if(checkExtension(filename) != 0)
    {
        free(filename);
        exit(0);
    }

    f=fopen(filename,"r");
    if(f==NULL)
    {
        free(filename);
        exit(0);
    }

    exitFileName = exitFileExtension(filename, fileinsize);

    fout=fopen(exitFileName,"w");
    if(fout==NULL)
    {
        free(filename);
        exit(0);
    }



    while(fscanf(f, "%d", &V) == 1)
    {

        if(fscanf(f, "%d", &E) != 1) exit(0);
        if(fscanf(f, "%s", func) != 1) exit(0);
        if(V < 0 || E < 0)
        {
            remove(exitFileName);
            fclose(f);
            fclose(fout);
            free(filename);
            free(exitFileName);
            exit(0);
        }


     /*   if((strcmp(func, "A0") != 0) && (strcmp(func, "B0") != 0) && (strcmp(func, "C0") != 0) && (strcmp(func, "D0") != 0))
        {
            remove(exitFileName);
            fclose(f);
            fclose(fout);
            free(filename);
            free(exitFileName);
            exit(0);
        }*/

        arestas = (LinkedList**) malloc (V * sizeof(LinkedList*));

        if(arestas == NULL) exit(0);

        for(i=0;i<V;i++) arestas[i] = (void*) initLinkedList();

        if(strcmp(func, "A0") == 0)
        {
            if(fscanf(f, "%d", &argumento1) != 1) exit(0);
            arestas = PreencheLista(arestas, f, E, V);
            if(argumento1 > V || argumento1 < 0) res = -1;
            else res = modeA0 (arestas[(argumento1-1)]);
            writeToFile(fout, V, E, func, argumento1, argumento2, res);
        }

        if(strcmp(func, "B0") == 0)
        {
            if(fscanf(f, "%d", &argumento1) != 1) exit(0);
            if(fscanf(f, "%d", &argumento2) != 1) exit(0);
            arestas = PreencheLista(arestas, f, E, V);
            if(argumento1 > V || argumento1 < 0 || argumento2 > V || argumento2 < 0) res = -1;
            else res = modeB0(arestas, (argumento1-1), (argumento2-1));
            writeToFile(fout, V, E, func, argumento1, argumento2, res);
        }

        if(strcmp(func, "C0") == 0)
        {
            if(fscanf(f, "%d", &argumento1) != 1) exit(0);
            arestas = PreencheLista(arestas, f, E, V);
            if(argumento1 > V || argumento1 < 0) res = -1;
            else res = modeCD0(arestas, (argumento1-1), func, V);
            writeToFile(fout, V, E, func, argumento1, argumento2, res);
        }

        if(strcmp(func, "D0") == 0)
        {
            if(fscanf(f, "%d", &argumento1) != 1) exit(0);
            arestas = PreencheLista(arestas, f, E, V);
            if(argumento1 > V || argumento1 < 0) res = -1;
            else res = modeCD0(arestas, (argumento1-1), func, V);
            writeToFile(fout, V, E, func, argumento1, argumento2, res);
        }

        if(strcmp(func, "A1") == 0)
        {
            int narestas=0;
            double total=0.0;

            st1 = (int*) malloc (V*sizeof(int));
            val1 = (double*) malloc (V*sizeof(double));
            visitados = (int*) malloc (V*sizeof(int));

            if(st1 == NULL) exit(0);
            if(val1 == NULL) exit(0);
            if(visitados == NULL) exit(0);

            for(i=0;i<V;i++) visitados[i] = 0;
            arestas = PreencheLista(arestas, f, E, V);

            for(i=0;i<V;i++)
            {
                if(visitados[i] == 0) modeA1(arestas, i, st1, val1, V, visitados);
            }

            for(i=0;i<V;i++)
            {
                if(st1[i] != -1) narestas++;
            }
            for(i=0;i<V;i++) total = total + val1[i];

            Lin *backbone = createBackbone(st1, val1, V);
            printA1(backbone, V, E, func, narestas, total, fout);

            free(backbone);
            free(st1);
            free(val1);
            free(visitados);
        }

        if(strcmp(func, "B1") == 0)
        {
            int narestas=0, swaparg = 0, posSub = 0, res = 0;
            double total=0.0;
            Lin *backbone, *backbone2;

            st1 = (int*) malloc (V*sizeof(int));
            val1 = (double*) malloc (V*sizeof(double));
            st2 = (int*) malloc (V*sizeof(int));
            val2 = (double*) malloc (V*sizeof(double));
            visitados = (int*) malloc (V*sizeof(int));

            if(st1 == NULL) exit(0);
            if(val1 == NULL) exit(0);
            if(st2 == NULL) exit(0);
            if(val2 == NULL) exit(0);
            if(visitados == NULL) exit(0);

            for(i=0;i<V;i++) visitados[i] = 0;
            if(fscanf(f, "%d", &argumento1) != 1) exit(0);
            if(fscanf(f, "%d", &argumento2) != 1) exit(0);

            arestas = PreencheLista(arestas, f, E, V);

            if(argumento1 > 0 && argumento1 < V+1 && argumento2 > 0 && argumento1 < V+1)
            {
                if(modeB0(arestas, argumento1-1, argumento2-1) == -1) res = -1;
            }

            if(argumento1 < 1 || argumento1 > V || argumento2 < 1 || argumento1 > V) res = -1;

            for(i=0;i<V;i++)
            {
                if(visitados[i] == 0) modeA1(arestas, i, st1, val1, V, visitados);
            }

            for(i=0;i<V;i++)
            {
                if(st1[i] != -1) narestas++;
            }
            for(i=0;i<V;i++) total = total + val1[i];

            backbone = createBackbone(st1, val1, V);
            if(argumento1 > 0 && argumento1 < V+1 && argumento2 > 0 && argumento1 < V+1)
            {
                if(res != -1)
                {
                    if(argumento2 < argumento1)
                    {
                        i = argumento2;
                        argumento2 = argumento1;
                        argumento1 = i;
                        swaparg = 1;
                    }

                    for(i=0;i<V;i++) visitados[i] = 0;

                    for(i=0;i<V;i++)
                    {
                        if(backbone[i].a == argumento1 && backbone[i].b == argumento2)
                        {
                            if (removeAdj(arestas, argumento1-1, argumento2-1)!=2) exit(0);
                            for(j=0;j<V;j++)
                            {
                                if(visitados[j] == 0) modeA1(arestas, j, st2, val2, V, visitados);
                                res = 1;
                            }
                        }
                    }
                    if(res != 0)
                    {
                        backbone2 = createBackbone(st2, val2, V);

                        if(posSub == 0)
                        {
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
                                        res = 1;
                                        posSub = i;
                                    }
                                }
                                if (posSub != 0) break;
                                if(i==V-1) res = -1;
                            }
                        }
                        if(swaparg == 1)
                        {
                            i = argumento2;
                            argumento2 = argumento1;
                            argumento1 = i;
                            swaparg = 0;
                        }

                        if(res != -1)
                        {
                            fprintf(fout, "%d %d %s %d %d %d %.2lf %d\n", V, E, func, argumento1, argumento2, narestas, total, res);
                            for(i=0;i<V;i++)
                            {
                                if(backbone[i].val != 0) fprintf(fout, "%d %d %.2lf\n", backbone[i].a ,backbone[i].b, backbone[i].val);
                            }
                            fprintf(fout, "%d %d %.2lf\n", backbone2[posSub].a, backbone2[posSub].b, backbone2[posSub].val);
                        }

                        free(backbone2);
                    }
                }
            }

            if(swaparg == 1)
            {
                i = argumento2;
                argumento2 = argumento1;
                argumento1 = i;
                swaparg = 0;
            }
            if(res != 1)
            {
                fprintf(fout, "%d %d %s %d %d %d %.2lf %d\n", V, E, func, argumento1, argumento2, narestas, total, res);

                for(i=0;i<V;i++){
                    if(backbone[i].val != 0) fprintf(fout, "%d %d %.2lf\n", backbone[i].a ,backbone[i].b, backbone[i].val);
                }
            }
            fprintf(fout, "\r\n");

            free(backbone);
            free(st1);
            free(val1);
            free(st2);
            free(val2);
            free(visitados);



        }

        if(strcmp(func, "C1") == 0)
        {
            int swaparg = 0;
            int narestas=0, arestaC;
            double total=0.0, res = 0.0;
            Lin *backbone, *backbone2;

            st1 = (int*) malloc (V*sizeof(int));
            val1 = (double*) malloc (V*sizeof(double));
            st2 = (int*) malloc (V*sizeof(int));
            val2 = (double*) malloc (V*sizeof(double));
            visitados = (int*) malloc (V*sizeof(int));

            if(st1 == NULL) exit(0);
            if(val1 == NULL) exit(0);
            if(st2 == NULL) exit(0);
            if(val2 == NULL) exit(0);
            if(visitados == NULL) exit(0);

            for(i=0;i<V;i++) visitados[i] = 0;
            if(fscanf(f, "%d", &argumento1) != 1) exit(0);
            if(fscanf(f, "%d", &argumento2) != 1) exit(0);

            arestas = PreencheLista(arestas, f, E, V);

            for(i=0;i<V;i++)
            {
                if(visitados[i] == 0) modeA1(arestas, i, st1, val1, V, visitados);
            }

            for(i=0;i<V;i++)
            {
                if(st1[i] != -1) narestas++;
            }

            for(i=0;i<V;i++) total = total + val1[i];

            for(i=0;i<V;i++) visitados[i] = 0;

            arestaC = narestas;
            res = -1;
            backbone = createBackbone(st1, val1, V);

            if(argumento1 > 0 && argumento1 < V+1 && argumento2 > 0 && argumento1 < V+1)
            {
                if(modeA0(arestas[argumento1-1]) != 0)
                {
                    if(argumento2 < argumento1)
                    {
                        i = argumento2;
                        argumento2 = argumento1;
                        argumento1 = i;
                        swaparg = 1;
                    }


                    for(i=0;i<V;i++)
                    {
                        if(backbone[i].a == argumento1 && backbone[i].b == argumento2)
                        {
                            for(j=0;j<V;j++)
                            {
                                if(visitados[j] == 0) PrimIgnore(arestas, j, st2, val2, V, visitados, argumento1-1, argumento2-1);
                            }
                        }
                    }
                }
            }

                if(visitados[0] == 1)
                {
                    arestaC = 0;
                    res = 0;
                    for(i=0;i<V;i++)
                    {
                        if(st2[i] != -1) arestaC++;
                    }

                    for(i=0;i<V;i++) res = res + val2[i];
                    backbone2 = createBackbone(st2, val2, V);
                    if(swaparg == 1)
                    {
                        i = argumento2;
                        argumento2 = argumento1;
                        argumento1 = i;
                        swaparg = 0;
                    }
                    fprintf(fout, "%d %d %s %d %d %d %.2lf %d %.2lf\n", V, E, func, argumento1, argumento2, narestas, total, arestaC, res);
                    for(i=0;i<V;i++)
                    {
                        if(backbone[i].val != 0) fprintf(fout, "%d %d %.2lf\n", backbone[i].a ,backbone[i].b,backbone[i].val);
                    }
                    for(i=0;i<V;i++)
                    {
                        if(backbone2[i].val != 0 && res != -1) fprintf(fout, "%d %d %.2lf\n", backbone2[i].a ,backbone2[i].b, backbone2[i].val);
                    }

                free(backbone2);

            }

            if(swaparg == 1)
            {
                i = argumento2;
                argumento2 = argumento1;
                argumento1 = i;
                swaparg = 0;
            }

            if(res == -1)
            {
                fprintf(fout, "%d %d %s %d %d %d %.2lf %.0lf\n", V, E, func, argumento1, argumento2, narestas, total, res);
                for(i=0;i<V;i++){
                    if(backbone[i].val != 0) fprintf(fout, "%d %d %.2lf\n", backbone[i].a ,backbone[i].b,backbone[i].val);
                }
            }
           fprintf(fout, "\r\n");

            free(backbone);
            free(st1);
            free(val1);
            free(st2);
            free(val2);
            free(visitados);
        }

        if(strcmp(func, "D1") == 0)
        {
            int narestas=0, nrotas=0, *vperdidosaux, *vperdidos, routesLeft=0;
            double total=0.0;
            Lin *alternativas, aux;

            st1 = (int*) malloc (V*sizeof(int));
            val1 = (double*) malloc (V*sizeof(double));
            visitados = (int*) malloc (V*sizeof(int));

            vperdidosaux = (int*) malloc (sizeof(int));

            if(st1 == NULL) exit(0);
            if(val1 == NULL) exit(0);
            if(visitados == NULL) exit(0);

            if(fscanf(f, "%d", &argumento1) != 1) exit(0);

            if(argumento1 > V || argumento1 < 1) routesLeft = -1;

            for(i=0;i<V;i++) visitados[i] = 0;
            arestas = PreencheLista(arestas, f, E, V);

            for(i=0;i<V;i++)
            {
                if(visitados[i] == 0) modeA1(arestas, i, st1, val1, V, visitados);
            }

            for(i=0;i<V;i++)
            {
                if(st1[i] != -1) narestas++;
            }
            for(i=0;i<V;i++) total = total + val1[i];

            Lin *backbone = createBackbone(st1, val1, V);          

            if(routesLeft != -1)
            {

                for(i=0;i<V;i++)
                {
                    if(backbone[i].a == argumento1)
                    {
                        nrotas++;
                        vperdidosaux = (int*) realloc (vperdidosaux, nrotas*sizeof(int));
                        vperdidosaux[nrotas-1] = backbone[i].b;
                    }
                    if(backbone[i].b == argumento1)
                    {
                        nrotas++;
                        vperdidosaux = (int*) realloc (vperdidosaux, nrotas*sizeof(int));
                        vperdidosaux[nrotas-1] = backbone[i].a;
                    }
                }

                for(i=0;i<nrotas;i++)
                {
                    if(vperdidosaux[i] != 0) routesLeft++;
                }

                vperdidos = (int*) malloc (routesLeft*sizeof(int));
                j=0;
                for(i=0;i<nrotas;i++)
                {
                    if(vperdidosaux[i] != 0)
                    {
                        vperdidos[j] = vperdidosaux[i];
                        j++;
                    }
                }

                nrotas = routesLeft;

                alternativas = (Lin*) malloc (routesLeft*sizeof(Lin));

                for(i=0;i<V;i++)
                {
                    for(j=0;j<routesLeft;j++)
                    {
                        if((backbone[i].a == argumento1 && backbone[i].b == vperdidos[j]) || (backbone[i].b == argumento1 && backbone[i].a == vperdidos[j]))
                        {

                            aux = modeE1(backbone, i, arestas, V);
                            alternativas[j] = aux;
                        }
                    }
                }

                for(i=0;i<nrotas;i++)
                {
                    if(alternativas[i].val == 0) routesLeft--;
                    if(alternativas[i].a == argumento1 || alternativas[i].b == argumento1)
                    {
                        alternativas[i].a = 0;
                        alternativas[i].b = 0;
                        alternativas[i].val = 0;
                        routesLeft--;
                    }
                }

                for(i=0;i<nrotas;i++)
                {
                    for(j=i+1;j<nrotas;j++)
                    {
                        if(alternativas[i].a == alternativas[j].a && alternativas[i].b == alternativas[j].b)
                        {
                            alternativas[j].a = 0;
                            alternativas[j].b = 0;
                            alternativas[j].val = 0;
                            routesLeft--;
                        }
                    }
                }

                if(routesLeft == -1) routesLeft = 0;

                InsertionSort(alternativas, nrotas);            

                fprintf(fout, "%d %d %s %d %d %.2lf %d\n", V, E, func, argumento1, narestas, total, routesLeft);
                for(i=0;i<V;i++) if(backbone[i].val != 0) fprintf(fout, "%d %d %.2lf\n", backbone[i].a, backbone[i].b, backbone[i].val);
                for(i=0;i<nrotas;i++) if(alternativas[i].val != 0) fprintf(fout, "%d %d %.2lf\n", alternativas[i].a, alternativas[i].b, alternativas[i].val);

                free(alternativas);
                free(vperdidos);
            }
            else
            {
                fprintf(fout, "%d %d %s %d %d %.2lf %d\n", V, E, func, argumento1, narestas, total, routesLeft);
                for(i=0;i<V;i++) if(backbone[i].val != 0) fprintf(fout, "%d %d %.2lf\n", backbone[i].a, backbone[i].b, backbone[i].val);
            }
            fprintf(fout, "\r\n");


            free(backbone);
            free(st1);
            free(val1);
            free(visitados);
            free(vperdidosaux);
        }

        if(strcmp(func, "E1") == 0)
        {
            int narestas=0;
            double total=0.0;
            Lin aux, *alternatives;

            st1 = (int*) malloc (V*sizeof(int));
            val1 = (double*) malloc (V*sizeof(double));
            visitados = (int*) malloc (V*sizeof(int));

            if(st1 == NULL) exit(0);
            if(val1 == NULL) exit(0);
            if(visitados == NULL) exit(0);

            for(i=0;i<V;i++) visitados[i] = 0;
            arestas = PreencheLista(arestas, f, E, V);

            for(i=0;i<V;i++)
            {
                if(visitados[i] == 0) modeA1(arestas, i, st1, val1, V, visitados);
            }

            for(i=0;i<V;i++)
            {
                if(st1[i] != -1) narestas++;
            }
            for(i=0;i<V;i++) total = total + val1[i];

            Lin *backbone = createBackbone(st1, val1, V);
            alternatives = (Lin*) malloc(V*sizeof(Lin));

            for(i=0;i<V;i++)
            {
                aux = modeE1(backbone, i, arestas, V);
                alternatives[i] = aux;
            }

            printE1(backbone, alternatives, V, E, func, narestas, total, fout);
            free(st1);
            free(val1);
            free(visitados);
            free(backbone);
            free(alternatives);

        }


        for(i=0;i<V;i++)
        {
            FreeList(arestas[i],FreeItem);
        }
        free(arestas);

    }

    fclose(f);
    fclose(fout);
    free(filename);
    free(exitFileName);
    return 0;

}

