//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(A,B) (A) = (B *)malloc(sizeof(B)); if ((A) == NULL) return

typedef struct node {
    char c;
    int flag: 1;
    struct node *pLess;
    struct node *pEqual;
    struct node *pGreater;
} TNode;

void TSTInit(TNode **root);
void TSTInsert(TNode **current,char *key);
int auto_complite(TNode *corrent, char *key, char *imprimir, int *i);
void impressao (TNode *corrent, char *palavra, int *i);
