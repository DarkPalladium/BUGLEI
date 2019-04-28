//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

#include "tad_documento.h"

void inicializa_lista_doc(lista_doc *lista){
    lista->primeiro = (celula_doc*)malloc(sizeof(celula_doc));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}
void insere_lista_doc(lista_doc *lista, int id){
    celula_doc *percorre;
    percorre = lista->primeiro->prox;
    while(percorre != NULL){ //documento ja pode estar na lista_doc
        if(percorre->id == id){
            return;
        }
        percorre = percorre->prox;
    }
    lista->ultimo->prox = (celula_doc*)malloc(sizeof(celula_doc));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->id = id;
    lista->ultimo->relevancia = 0;
    lista->ultimo->prox = NULL;
}
void palavras_distintas (tipopatno *arvore, int id, int *resultado){
  if (arvore == NULL){
    return;
  }
  if (EExterno(arvore) == 0){
    palavras_distintas(arvore->No.nointerno.esq, id, resultado);
    palavras_distintas(arvore->No.nointerno.dir, id, resultado);
  }
  else{
    celula *atual;
    atual = arvore->repetidos.primeiro->prox;

    while (atual != NULL){
      if (atual->tex.id == id){
        *resultado += 1;
        break;
      }
      atual = atual->prox;
    }
  }
}
void faz_relevancia(char *termo, tipopatno *arvore, lista_doc *lista_de_doc, float N){
    lista *lista1; lista lista_aux; int dj = 0; int Fij; int ni = 0; float relevancia_relativa = 0;
    celula_doc *percorre_doc; celula *percorre;

    retorna_lista(termo, arvore, &lista1); //lista da palavra "termo";
    if (lista1 == NULL){
        printf("\n\nTERMO %s NAO ENCONTRADO\n", termo);
    }
    else{
        lista_aux = *lista1; // SEGURAN�A
        ///preenchimento da lista_doc, SE necessario (logica no insere_lista_doc)
        percorre = lista_aux.primeiro->prox;
        while(percorre != NULL){
            insere_lista_doc(lista_de_doc, percorre->tex.id);
            dj++;
            percorre = percorre->prox;
        }

        ///agora foca em cada documento, AKA frequencia relativas;
        percorre_doc = lista_de_doc->primeiro->prox;
        percorre = lista_aux.primeiro->prox; //primeira celula do termo atual
        while(percorre_doc != NULL){
            ///CALCULAR AS RELEVANCIAS PARCIAIS DOS ARQUIVOS QUE O TERMO APARECE
            while(percorre != NULL){
                if (percorre->tex.id == percorre_doc->id){
                    ni = 0;
                    palavras_distintas(arvore, percorre_doc->id, &ni);

                    relevancia_relativa = percorre->tex.quant; // f
                    relevancia_relativa = relevancia_relativa*log2(N)/dj; //logN/dj
                    relevancia_relativa = relevancia_relativa/ni; //divide por ni
                    percorre_doc->relevancia += relevancia_relativa;
                }
                percorre = percorre->prox;
            }
            percorre_doc = percorre_doc->prox;
            percorre =lista_aux.primeiro->prox;
        }
    }
}

void retorna_lista_doc_ordenada(lista_doc *lista){
    celula_doc *anterior; celula_doc *proximo; celula_doc *maior; celula_doc *anterior_maior;

    anterior = lista->primeiro;
    proximo = anterior->prox;
    maior = anterior->prox;
    while(proximo != NULL){
        while(proximo != NULL){
            if(proximo->relevancia >= maior->relevancia){
                anterior_maior = anterior;
                maior = proximo;
            }

            anterior = proximo;
            proximo = proximo->prox;
        }
        printf("|                 Texto %d = %.2f                              |\n", maior->id, maior->relevancia);
        anterior_maior->prox = maior->prox;
        free(maior);
        anterior = lista->primeiro;
        maior = anterior->prox;
        proximo = anterior->prox;
    }
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
}
