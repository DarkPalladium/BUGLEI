//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include <string.h>
#include "tst.h"

void TSTInit(TNode **root)
{
    *root = NULL;
}

void TSTInsert(TNode **current,char *key)
{
    if (*current == NULL) {
        MALLOC(*current,TNode);
        (*current)->c = *key;
        (*current)->flag = 0;
        (*current)->pLess = NULL;
        (*current)->pEqual = NULL;
        (*current)->pGreater = NULL;
    }

    if (*key < (*current)->c)
        TSTInsert(&((*current)->pLess),key);
    else if (*key > (*current)->c)
        TSTInsert(&((*current)->pGreater),key);
    else
        if (*(key+1))
            TSTInsert(&((*current)->pEqual),key+1);
        else
            (*current)->flag = 1;
}

int auto_complite(TNode *corrent, char *key, char *imprimir, int *i){
  if (corrent == NULL)
      return 0;
  else if (*key < corrent->c)
    return auto_complite(corrent->pLess, key, imprimir, i);
  else if (*key > corrent->c)
    return auto_complite(corrent->pGreater, key, imprimir, i);
  else
  {
      if (*(key+1)){
        imprimir[*i] = corrent->c;
        *i += 1;
        if (corrent->flag == -1){
          int j;
          for(j=0;j<*i;j++){
            printf("%c", imprimir[j]);
          }
          printf("\n");
        }
        auto_complite(corrent->pEqual, key+1, imprimir, i);
        return 1;
      }
      else{
        imprimir[*i] = corrent->c;
        *i += 1;
        if (corrent->flag == -1){
          int j;
          for(j=0;j<*i;j++){
            printf("%c", imprimir[j]);
          }
          printf("\n");
        }
        impressao(corrent->pEqual, imprimir, i);
        return 1;
      }
  }
}
void impressao (TNode *corrent, char *palavra, int *i){
  if(corrent == NULL){
    return;
  }
  if(corrent->flag == -1){
    int j=0;
    palavra[*i] = corrent->c;
    *i += 1;
    for(j=0;j<*i;j++){
      printf("%c", palavra[j]);
    }
    printf("\n");
    palavra[*i] = palavra[*i+1];
    *i -= 1;
  }
  if (corrent->pLess != NULL){
    impressao(corrent->pLess, palavra, i);
  }
  if (corrent->pGreater != NULL){
    impressao(corrent->pGreater, palavra, i);
  }
  if (corrent->pEqual != NULL){
    palavra[*i] = corrent->c;
    *i += 1;
    impressao(corrent->pEqual, palavra, i);
    palavra[*i] = palavra[*i + 1];
    *i -= 1;
  }

}
