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

/**
* Breve coment�rio: temos aqui uma arvore bin�ria. Funciona e seu tempo de busca � em teoria O(log n)
* acontece que a arvore binaria � sens�vel � ordem de inser��o dos dados nela, podendo se desconfigurar
* e com isso perder as vantagens de arvore logo precisamos de uma fun��o que de tempos em tempos fa�a
* o rebalanceamento da mesma, isso poderia ser evitado se tivessemos fun��es que balanceassem a arvore a
* cada inser��o, mantendo-a sempre nivelada.
* Da� temos a arvore binaria de busca AVL que possui opera��es para tal objetivo.
* */

/**
 *          Arvore binaria AVL
 *         � um tipo de arvore bin�ria munida de opera��es que a mant�m balanceada na inser��o e na
 *      remo��o,portanto ela sobrescreve esses metodos.
 *         Para fazer isso ela utiliza 2 fun��es a mais que s�o rota��oDireita e rota��oEsquerda, al�m de outras
 *      2 fun��es que s�o composi��es dessas 2 rota��oDuplaDireita e rota��oDuplaEsquerda, al�m de
 *      possuir um campo a mais em seus n�s que � chamado fator de balan�o (FB<|1|).
 *         Essa pratica visa evitar o rebalanceamento que � deveras custoso,para fazer isso
 *      os elementos(Folhas) possuem um tipo adicional de dado chamado fator de balan�o
 *      que � a diferen�a de altura do lado esquerdo pro direito e deve ser mantido sempre
 *      entre -1 e +1 no m�ximo, preferencialmente em 0 (n�s com mesma altura).*/


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
