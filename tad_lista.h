//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id, quant;
} texto;

typedef  struct tcelula *apontador;
typedef struct tcelula {
  texto tex;
  struct tcelula *prox;
} celula;

typedef struct {
    celula *primeiro;
    celula *ultimo;
} lista;

void inicializa_lista (lista *lista);
void lista_inserir (lista *lista, int id);
void lista_imprimi (lista lista);
