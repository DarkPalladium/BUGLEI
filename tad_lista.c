//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_lista.h"

void inicializa_lista (lista *lista){

  lista->primeiro = (apontador) malloc(sizeof(celula));
  lista->ultimo = lista->primeiro;
  lista->primeiro->prox = NULL;
}

void lista_inserir (lista *lista, int id){
  celula *novo, *atual, *prox;

  atual = lista->primeiro;
  prox = lista->primeiro->prox;

  while (prox != NULL) {
    if (prox->tex.id == id) {
      prox->tex.quant += 1;
      return;
    }
    atual = prox;
    prox = prox->prox;
  }
  novo = (apontador) malloc(sizeof(celula));
  novo->tex.id = id;
  novo->tex.quant = 1;
  novo->prox = prox;
  atual->prox = novo;
  if (lista->ultimo->prox != NULL){
      lista->ultimo = lista->ultimo->prox;
      lista->ultimo->prox = NULL;
  }
}

void lista_imprimi (lista lista){
  celula *atual;
  atual = lista.primeiro->prox;

  while (atual != NULL){
    printf("|           Aparereceu: %d no Texto %d              \n", atual->tex.quant, atual->tex.id);
    atual = atual->prox;
  }
}
