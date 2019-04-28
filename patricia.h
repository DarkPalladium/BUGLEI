//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_lista.h"
#define T 50 //essa faviavel e utilizada para padronizar os tamanhos dos vetores de carcteres

typedef enum {
  interno, externo
} tipono;

typedef struct tipopatno {
  tipono nt;
  lista repetidos;
  union {
    struct {
      char caractere;
      int indice;
      struct tipopatno *esq, *dir;
    } nointerno;
    char chave[T];
  }No;
}tipopatno;

int comparar (char entrada, char arvore);
int igual (char *entrada, char *arvore);
int EExterno(tipopatno *p);
tipopatno *CriaNoInt(char caractere, int i, tipopatno **esq, tipopatno **dir);
tipopatno *CriaNoExt(char *k);
void InsereEntre(char *entrada, char diferente, tipopatno **arvore, int i, int id);
void Insere (char *entrada, tipopatno **arvore, int id);
void imprimir(tipopatno *arvore);
void pesquisa(char *palavra, tipopatno *arvore);
void retorna_lista(char *palavra, tipopatno *arvore, lista **retorno);
