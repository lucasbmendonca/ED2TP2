#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED

typedef struct ator
{
    char id[16];
    char nome[128];
    char genero[1];
}TAtor;

typedef struct vizinho
{
    TAtor atorVizinho;
    struct vizinho *prox;
} TVizinho;

typedef struct grafo
{
    TAtor atorVertice;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *inicializa();
void imprime(TGrafo *g);
void imprime_recursivo(TGrafo *g);
void libera(TGrafo *g);
void libera_vizinhos(TVizinho *v);
void libera_recursivo(TGrafo *g);
void libera_vizinho_recursivo(TVizinho *v);
TGrafo *busca_vertice(TGrafo *g, char v[]);
TVizinho *busca_aresta(TGrafo *g, char v1[], char v2[]);
TGrafo *insere_vertice(TGrafo *g, TAtor x);
void insere_um_sentido(TGrafo *g, char v1[], char v2[]);
void insere_aresta(TGrafo *g, char v1[], char v2[]);
void retira_um_sentido(TGrafo *g, TAtor v1, TAtor v2);
void retira_aresta(TGrafo *g, TAtor v1, TAtor v2);
TGrafo *retira_vertice(TGrafo *g, TAtor v);
void copyToken(char* destination, char* source, size_t maxLen, char const* delimiter);

#endif