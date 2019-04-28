//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"

//Esta funcao olha qual e a maior letra utilizando a tabela ASII
// e a retorna para que ela seja armazenada no interno
int comparar (char entrada, char arvore){
  return (entrada > arvore)?entrada:arvore;
}

//Aqui ele confere letra por letra, para ver se as palavras sao iguais,
//se forem retorna -1, se nao ela retorna a posicao a onde houve diferenca
int igual (char *entrada, char *arvore){
  int i;
  for(i=0; entrada[i] == arvore[i]; i++){
    if(entrada[i] == '\0'){
      return -1;
    }
  }
  return i;
}

int EExterno(tipopatno *p){
  if (p->nt == externo){
    return 1;
  }
  else{
    return 0;
  }
}

tipopatno *CriaNoInt(char caractere, int i, tipopatno **esq, tipopatno **dir){
  tipopatno *aux;
  aux = (tipopatno*) malloc(sizeof(tipopatno));
  aux->nt = interno;
  aux->No.nointerno.esq = *esq;
  aux->No.nointerno.dir = *dir;
  aux->No.nointerno.indice = i;
  aux->No.nointerno.caractere = caractere;
  return aux;
}

tipopatno *CriaNoExt(char *k){
  tipopatno *aux;
  aux = (tipopatno*) malloc(sizeof(tipopatno));
  aux->nt = externo;
  strcpy(aux->No.chave, k);
  inicializa_lista(&aux->repetidos);
  return aux;
}

void InsereEntre(char *entrada, char diferente, tipopatno **arvore, int i, int id){
  tipopatno *aux_interno = NULL, *aux_externo = NULL;
  if ((*arvore)->nt == externo || i < (*arvore)->No.nointerno.indice){
    aux_externo = CriaNoExt(entrada);
    lista_inserir(&aux_externo->repetidos, id);
    if (aux_externo == NULL) {
      return;
    }
    if (entrada[i] < diferente) {
      aux_interno = CriaNoInt(diferente, i, &aux_externo, arvore);
    }
    else{
      aux_interno = CriaNoInt(diferente, i, arvore ,&aux_externo);
    }
    if(aux_interno == NULL){
      return;
    }
    *arvore = aux_interno;
    return;
  }
  else{
    if ((*arvore)->No.nointerno.caractere > entrada[(*arvore)->No.nointerno.indice]){
      return InsereEntre(entrada, diferente ,&(*arvore)->No.nointerno.esq, i, id);
    }
    else{
      return InsereEntre(entrada, diferente ,&(*arvore)->No.nointerno.dir, i, id);
    }
  }
}

//para decidir o caminho que a palavra fara pela arvore ate um ponteiro NULL ou uma repeticao
//o algoritmo pergunta em cada no interno se a quantidade de letras da entrada e maior ou igual ao indice
//e se a letra na posicao do indice e igual ou maior que a letra armazenada no no
//se essas duas condicoes forem verdadeiras ele ira seguir para o lado direiro dquele NO
//se nao ele seguira para o lado esquerdo
void Insere (char *entrada, tipopatno **arvore, int id){
  tipopatno *aux;
  int i=0;

  if(*arvore == NULL){
    *arvore = CriaNoExt(entrada);
    lista_inserir(&(*arvore)->repetidos, id);
    return;
  }
  else{
    aux = *arvore;
    while (aux->nt == interno) {
      if(strlen(entrada) >= aux->No.nointerno.indice && entrada[aux->No.nointerno.indice] >= aux->No.nointerno.caractere){
        aux = aux->No.nointerno.dir;
      }
      else{
        aux = aux->No.nointerno.esq;
      }
    }
    i = igual(entrada, aux->No.chave);
    if (i == -1) {
      lista_inserir(&aux->repetidos, id);
    }
    else{
      return (InsereEntre(entrada, comparar(entrada[i], aux->No.chave[i]), arvore, i, id));
    }
  }
}

void pesquisa(char *palavra, tipopatno *arvore){
  if(arvore == NULL){
    printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
               "|                                                 |\n"
               "|               BIBLIOTECA VAZIA                  |\n"
               "|                                                 |\n"
               "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    return;
  }
  if(EExterno(arvore) == 1){
    if(strcmp(palavra, arvore->No.chave) == 0){
      printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                 "|                                                 |\n"
                 "|             PALAVRA ENCONTRADA                  |\n"
                 "|                   %s                               \n", arvore->No.chave);
      lista_imprimi(arvore->repetidos);
      printf(    "|                                                 |\n"
                 "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    }
    else{
      printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                 "|                                                 |\n"
                 "|      ESTA PALAVRA NAO EXISTE NA BIBLIOTECA      |\n"
                 "|                                                 |\n"
                 "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    }
  }
  else{
    if (strlen(palavra) >= arvore->No.nointerno.indice && arvore->No.nointerno.caractere > palavra[arvore->No.nointerno.indice]){
      pesquisa(palavra, arvore->No.nointerno.esq);
    }
    else{
        pesquisa(palavra, arvore->No.nointerno.dir);
      }
  }
}

void imprimir(tipopatno *arvore){
  if (arvore == NULL){
    return;
  }
  if (EExterno(arvore) == 0){
    imprimir(arvore->No.nointerno.esq);
    imprimir(arvore->No.nointerno.dir);
  }
  else{
    printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
               "|                                                 |\n"
               "|                  CHAVE: %s                       \n", arvore->No.chave);
    lista_imprimi(arvore->repetidos);
    printf(    "|                                                 |\n"
               "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
  }
}

//esta funcao procura a palavra e retorna a lista de ocorrencias dela
//se a palavra nao existir na arvore ele renorna NULL
void retorna_lista(char *palavra, tipopatno *arvore, lista **retorno){
    if(arvore == NULL){
        (*retorno) = NULL;
        return;
    }
    if(EExterno(arvore) == 1){
        if(strcmp(palavra, arvore->No.chave) == 0){
          (*retorno) = &(arvore->repetidos);
        }
        else{
          (*retorno) = NULL;
        }
    }
    else{
        if (strlen(palavra) >= arvore->No.nointerno.indice && arvore->No.nointerno.caractere > palavra[arvore->No.nointerno.indice]){
            retorna_lista(palavra, arvore->No.nointerno.esq, retorno);
        }
        else{
            retorna_lista(palavra, arvore->No.nointerno.dir, retorno);
        }
  }
}
