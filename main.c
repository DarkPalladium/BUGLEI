//Autores:
// Pablo Miranda Batista          3482
//Lucas Ranieri Oliveira Martins  3479
//João Victor Magalhães Souza     3483

//gcc -o tp1 main.c patricia.c patricia.h tad_documento.c tad_documento.h tad_lista.c tad_lista.h tst.h tst.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_documento.h"
#include "tst.h"

int main()
{
    char palavra[T], saida[T];
    int controle, id=0, i=0, quant;
    tipopatno *arvore = NULL;
    lista_doc lista_de_documentos;
    TNode *raiz;
    inicializa_lista_doc(&lista_de_documentos);
    TSTInit(&raiz);


    printf("\n\n-------------------- BEM VINDO AO BUGLEI ---------------------\n\n"
               "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
               "|                                                             |\n"
               "| ESCOLHA UMA DAS OPCOES:                                     |\n"
               "|                                                             |\n"
               "| INSERIR UM TEXTO A BIBLIOTECA = 1                           |\n"
               "| IMPRIMIR TODAS AS PALAVRAS DA BIBLIOTECA = 2                |\n"
               "| PESQUISAR SE UMA PALAVRA EXISTE NA BIBLIOTECA = 3           |\n"
               "| BUSCAR PELA RELEVANCIA DE N TERMOS = 4                      |\n"
               "| AUTO COMPLETE = 5                                           |\n"
               "| SAIR = 0                                                    |\n"
               "|                                                             |\n"
               "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    printf("DIGITE A OPERACAO DESEJADA: ");
    scanf("%d", &controle);

    while (controle != 0) {

      if (controle == 1) {
        FILE *ptr_arq;
        char arquivo[20];

        printf("\n\nESCREVA O NOME DO ARQUIVO(COM A EXTENCAO): ");
        scanf("%s", arquivo);

        ptr_arq = fopen(arquivo, "r");

        if ((ptr_arq = fopen(arquivo,"r"))==NULL)
            printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                   "|                                                 |\n"
                   "|           ERRO NA ABERTURA DO ARQUIVO           |\n"
                   "|                                                 |\n"
                   "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");

        else
        printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                   "|                                                 |\n"
                   "|         ARQUIVO ABERTO COM SUCESSO!             |\n"
                   "|             ID do arquivo e %d                   |\n"
                   "|                                                 |\n"
                   "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n", id+1);

        id += 1;
        while ((fscanf(ptr_arq,"%s",palavra))!= EOF){
            strlwr(palavra);
            Insere(palavra, &arvore, id);
            TSTInsert(&raiz, palavra);
        }
        fclose(ptr_arq);
      }
      if (controle == 2) {
        imprimir(arvore);
      }
      if (controle == 3) {
        printf("\n\nDIGITE A PALAVRA QUE DESEJA PESQUISAR: ");
        scanf("%s", palavra);
        strlwr(palavra);
        pesquisa(palavra, arvore);
      }
      if (controle == 4){
          printf("\n\nDIGITE A QUANTIDADE DE PALAVRAS QUE DESEJA BUSCAR: ");
          scanf("%d", &quant);
          printf("\n");
          for(i=0;i<quant;i++){
            printf("\nDIGITE 0 %d TERMO DA PESQUISA: ", i+1);
            scanf("%s", palavra);
            strlwr(palavra);
            faz_relevancia(palavra, arvore, &lista_de_documentos, id);
          }
          printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                     "|                                                             |\n");

          retorna_lista_doc_ordenada(&lista_de_documentos);

          printf(    "|                                                             |\n"
                     "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");

      }
      if (controle == 5){
        printf("DIGITE O PREFIXO DESEJADO: ");
        scanf("%s", palavra);
        strlwr(palavra);
        printf("\n\nLISTA DE PALAVRAS:\n");
        if (auto_complite(raiz, palavra, saida, &i) == 0){
          printf("NAO EXISTE PALAVRAS COM ESSA PREFIXACAO NA BIBLIOTECA\n");
        }
        i = 0;
      }

      printf("\n\n-------------------- BEM VINDO AO BUGLEI ---------------------\n\n"
                 "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
                 "|                                                             |\n"
                 "| ESCOLHA UMA DAS OPCOES:                                     |\n"
                 "|                                                             |\n"
                 "| INSERIR UM TEXTO A BIBLIOTECA = 1                           |\n"
                 "| IMPRIMIR TODAS AS PALAVRAS DA BIBLIOTECA = 2                |\n"
                 "| PESQUISAR SE UMA PALAVRA EXISTE NA BIBLIOTECA = 3           |\n"
                 "| BUSCAR PELA RELEVANCIA DE N TERMOS = 4                      |\n"
                 "| AUTO COMPLETE = 5                                           |\n"
                 "| SAIR = 0                                                    |\n"
                 "|                                                             |\n"
                 "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
      printf("DIGITE A OPERACAO DESEJADA: ");
      scanf("%d", &controle);
  }

}
