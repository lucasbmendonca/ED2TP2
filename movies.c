#include <stdio.h>
#include <string.h>
#include "movies.h"

//INICIALIZAÇÃO DA ESTRUTURA
TGrafo *inicializa()
{
    return NULL;
}

//IMPRESSÃO DO GRAFO
void imprime(TGrafo *g)
{
    while (g != NULL)
    {
        printf("Vertice %s\n", g->atorVertice.id);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;
        while (v != NULL)
        {
            printf("%s ", v->atorVizinho.id);
            v = v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}

//IMPRESSÃO DO GRAFO (IMPLEMENTAÇÃO RECURSIVA)
void imprime_recursivo(TGrafo *g)
{
    if (g != NULL)
    {
        printf("Vértice: %s:\n", g->atorVertice.id);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;
        while (v)
        {
            printf("%s ", v->atorVizinho.id);
            v = v->prox;
        }
        printf("\n\n");
        imprime_recursivo(g->prox);
    }
}

//LIBERAÇÃO DA ESTRUTURA
void libera(TGrafo *g)
{
    while (g != NULL)
    {
        libera_vizinhos(g->prim_vizinho);
        TGrafo *temp = g;
        g = g->prox;
        free(temp);
    }
}
void libera_vizinhos(TVizinho *v)
{
    while (v != NULL)
    {
        TVizinho *temp = v;
        v = v->prox;
        free(temp);
    }
}

//LIBERAÇÃO DA ESTRUTURA(IMPLEMENTAÇÃO RECURSIVA)
void libera_recursivo(TGrafo *g)
{
    if (g != NULL)
    {
        libera_vizinho_recursivo(g->prim_vizinho);
        libera_recursivo(g->prox);
        free(g);
    }
}
void libera_vizinho_recursivo(TVizinho *v)
{
    if (v != NULL)
    {
        libera_vizinho_recursivo(v->prox);
        free(v);
    }
}

//BUSCA POR VÉRTICE X
TGrafo *busca_vertice(TGrafo *g, char v[])
{
    while ((g != NULL) && (strcmp(g->atorVertice.id, v) != 0))
    {
        g = g->prox;
    }
    return g;
}

//BUSCA POR ARESTA (V1, V2) OU {V1, V2}
TVizinho *busca_aresta(TGrafo *g, char v1[], char v2[])
{
    TGrafo *pv1 = busca_vertice(g, v1);
    TGrafo *pv2 = busca_vertice(g, v2);
    TVizinho *resp = NULL;
    //checa se ambos os vértices existem
    if ((pv1 != NULL) && (pv2 != NULL))
    {
        //percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_vizinho;
        while ((resp != NULL) && (strcmp(resp->atorVizinho.id, v2) != 0))
        {
            resp = resp->prox;
        }
    }
    return resp;
}

//INSERÇÃO DE VÉRTICE
TGrafo *insere_vertice(TGrafo *g, TAtor x)
{
    TGrafo *p = busca_vertice(g, x.id);
    if (p == NULL)
    {
        p = (TGrafo *)malloc(sizeof(TGrafo));
        p->atorVertice = x;
        p->prox = g;
        p->prim_vizinho = NULL;
        g = p;
    }
    return g;
}

//INSERÇÃO DE ARESTA EM GRAFO NÃO ORIENTADO
void insere_um_sentido(TGrafo *g, char v1[], char v2[])
{
    TGrafo *p = busca_vertice(g, v1);
    TGrafo *p2 = busca_vertice(g, v2);
    TVizinho *nova = (TVizinho *)malloc(sizeof(TVizinho));
    nova->atorVizinho = p2->atorVertice;
    nova->prox = p->prim_vizinho;
    p->prim_vizinho = nova;
}

//Usar essa função para grafico nao orientado
void insere_aresta(TGrafo *g, char v1[], char v2[])
{
    TVizinho *v = busca_aresta(g, v1, v2);
    if (v == NULL)
    {
        insere_um_sentido(g, v1, v2);
        insere_um_sentido(g, v2, v1);
    }
}

//EXCLUSÃO DE ARESTA EM GRAFO NÃO ORIENTADO
void retira_um_sentido(TGrafo *g, TAtor v1, TAtor v2)
{
    TGrafo *p = busca_vertice(g, v1.id);
    if (p != NULL)
    {
        TVizinho *ant = NULL;
        TVizinho *atual = p->prim_vizinho;
        while ((atual) && (strcmp(atual->atorVizinho.id, v2.id) != 0))
        {
            ant = atual;
            atual = atual->prox;
        }
        if (ant == NULL) //v2 era o primeiro nó da lista
            p->prim_vizinho = atual->prox;
        else
            ant->prox = atual->prox;
        free(atual);
    }
}

//Usar esta para grafos nao orientados
void retira_aresta(TGrafo *g, TAtor v1, TAtor v2)
{
    TVizinho *v = busca_aresta(g, v1.id, v2.id);
    if (v != NULL)
    {
        retira_um_sentido(g, v1, v2);
        retira_um_sentido(g, v2, v1);
    }
}

//EXCLUSÃO DE VÉRTICE EM GRAFO NÃO ORIENTADO
TGrafo *retira_vertice(TGrafo *g, TAtor v)
{
    TGrafo *p = g;
    TGrafo *ant = NULL;
    while ((p != NULL) && (strcmp(p->atorVertice.id, v.id) != 0))
    {
        ant = p;
        p = p->prox;
    }
    if (p != NULL)
    {
        while (p->prim_vizinho != NULL)
            retira_aresta(g, v, p->prim_vizinho->atorVizinho);
        if (ant == NULL)
            g = g->prox;
        else
            ant->prox = p->prox;
        free(p);
    }
    return g;
}

void copyToken(char *destination,
               char *source,
               size_t maxLen,
               char const *delimiter)
{
    char *token = strtok(source, delimiter);
    if (token != NULL)
    {
        destination[0] = '\0';
        strncat(destination, token, maxLen - 1);
    }
}