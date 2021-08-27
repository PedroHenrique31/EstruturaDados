#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include "ArvoreAVL.h"
#define TRUE 1
#define FALSE 0

//#include "CUnit/Basic.h"

/**
 *        autor: Pedro Henrique Carneiro de Ara�jo   Matricula: 22108287
 *
 *     Uma arvore binaria � uma estrutura de dados caracterizada de forma recursiva, definida como sendo um conjunto
 *  de n�s que possuem 3 informa��es:
 *      1- O dado armazenado que neste caso ser� um inteiro;
 *      2-Um ponteiro para uma arvore a esquerda (conjunto de numeros menores que o dado)
 *      3-Um ponteiro para um arvore a direita (conjunto de numeros maiores que o dado)
 *  Na arvore binaria s�o feitas basicamente 3 opera��es emergentes (ou seja surgem
 *      do conjunto de Folhas e n�o delas individualmente) s�o elas:inser��o,remo��o e busca definidas por:
 *      1-inser��o:Fun��o complexa, ela avalia se o n� raiz esta vazio se -sim insere nele-, se -- n�o ela deve avaliar
 *      se o dado � maior ou menor que o dado raiz e chamar a fun��o respectiva desse dado--;
 *      2-busca: opera��o de percorrer a arvore para averiguar se elemento existe, tamb�m � rescursiva e
 *      pode ser feito de varias maneiras: em ordem sim�trica, pr�-ordem (quando visita o n� antes de ir para
 *      o proximo),p�s-ordem(visita os n�s antes de visitar esse) e em n�vel;
 *      3-remo��o: depende da busca para encontrar elemento e ent�o destruir a folha.
 *
*/



int main()
{
    setlocale(LC_ALL,"ptb");//Traduz os caracteres para portugues.

    int valorAleatorio,total=199;
    FolhaAVL *RaizArvore,**ponteiroParaRaiz;
    RaizArvore=NULL;
    ponteiroParaRaiz=&RaizArvore;
    int aumentou=0;



    for(int i=0;i<total;i++){
        printf("intera��o:%d\n",i);
        valorAleatorio=rand()%100;
        insereAux(valorAleatorio,ponteiroParaRaiz);
        printf("\n=============================================\n");
    }
    printf("\t\t\t\t<<<Percorre em ordem>>>\n");
    emOrdem(RaizArvore);
    printf("\t\t\t\t<<<Percorre em p�s-Ordem>>>\n");
    posOrdem(RaizArvore);
    printf("\t\t\t\t<<<Percorre em pr�-Ordem>>>\n");
    preOrdem(RaizArvore);


    return 0;
}
