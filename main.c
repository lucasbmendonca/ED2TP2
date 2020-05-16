#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "movies.h"
#include "movies.c"

#define LINE_SIZE 200

int main()
{
    char line[LINE_SIZE];
    char nome[128];
    char id[16];
    char genero[1];
    TAtor ator;
    TGrafo *grafo;
    int lv_result;
    bool isEndOfFile = false;

    /*Tratamento do arquivo - Vertices*/
    FILE *arq;
    arq = fopen("small/actors.txt", "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!\n");
    }
    else
    {
        grafo = inicializa();
        do
        {
            if (fgets(line, sizeof(line), arq))
            {
                copyToken(ator.id, line, sizeof(ator.id), "\t");
                copyToken(ator.nome, NULL, sizeof(ator.nome), "\t");
                copyToken(ator.genero, NULL, sizeof(ator.genero), "\n");
                grafo = insere_vertice(grafo, ator);
            }
            else
            {
                isEndOfFile = true;
            }
        } while (!isEndOfFile);
    }

    fclose(arq);

    char id1[16], id2[16];
    /*Tratamento do arquivo - Vizinhos*/
    arq = fopen("small/co-actors.txt", "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!\n");
    }
    else
    {
        while (fgets(line, sizeof(line), arq))
        {
            copyToken(id1, line, sizeof(id1), "\t");
            copyToken(id2, NULL, sizeof(id2), "\n");

            insere_aresta(grafo, id1, id2);
        }
    }

    imprime(grafo);
    libera(grafo);
}