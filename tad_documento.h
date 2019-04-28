//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include <math.h>
#include "patricia.h"

typedef struct celula_doc *apontador_doc;
typedef struct celula_doc{
    int id;
    float relevancia;
    apontador_doc prox;
}celula_doc;

typedef struct lista_doc{
    apontador_doc primeiro;
    apontador_doc ultimo;
}lista_doc;

void inicializa_lista_doc(lista_doc *lista);
void insere_lista_doc(lista_doc *lista, int id);
void palavras_distintas (tipopatno *arvore, int id, int *resultado);
void faz_relevancia(char *termo, tipopatno *arvore, lista_doc *lista_de_doc, float N);
void retorna_lista_doc_ordenada(lista_doc *lista);
