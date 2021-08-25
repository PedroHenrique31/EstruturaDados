#include <stdio.h>
#include <stdlib.h>
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


 /* Tipo estruturado FolhaAVL � uma folha que armazena um inteiro e o fator de balan�o
 */
typedef struct FolhaAVL{
    int dado;
    int FatorBalanco;
    struct FolhaAVL *Esq;
    struct FolhaAVL *Dir;
}FolhaAVL;

/*
 * Par funcionar a arvore AVL faz uso de 4 funcoes basicas que a mant�m balanceada s�o elas:
 *      1- rota��o a direita;
 *      2-rota��o a esquerda;
 *      3-rota��o dupla a direita;(opera��o composta de 2 e 1);
 *      4-rota��o dupla a esquerda;(opera��o composta de 1 e 2).
*/
void rotacao_Direita(FolhaAVL *no){
    FolhaAVL *q,*temporario;
    q=no->Esq;
    temporario=no->Dir;
    q->Dir=no;
    no->Esq=temporario;
    no=q;
}
void rotacao_Esquerda(FolhaAVL *no){
    FolhaAVL *q,*temporario;
    q=no->Dir;
    temporario=q->Esq;
    q->Esq=no;
    no->Dir=temporario;
    no=q;
}
void rotacao_Esq_Dir(FolhaAVL *no){
    rotacao_Esquerda(no->Esq);
    rotacao_Direita(no);
}
void rotacao_Dir_Esq(FolhaAVL *no){
    rotacao_Direita(no->Dir);
    rotacao_Esquerda(no);
}
/* Outra funcionalidade extra � a de calcular a altura de um n� para mais tarde calcular o Fator de balanco*/

int alturaDir(FolhaAVL *no){
    return (no==NULL)? 0:1+alturaDir(no->Dir);
}
int alturaEsq(FolhaAVL *no){
    return (no==NULL)? 0:1+alturaEsq(no->Esq);
}
void calculaFatorBalanco(FolhaAVL *no){
    int altDir,altEsq;
    altDir=alturaDir(no);
    altEsq=alturaEsq(no);
    no->FatorBalanco=altDir-altEsq;
}
/* No mais uma arvore AVL � uma arvore binaria e realiza as mesmas opera��es
 */

FolhaAVL criaRegistro(int info){
    FolhaAVL novo;
    novo.dado=info;
    novo.FatorBalanco=0;
    novo.Dir=NULL;
    novo.Esq=NULL;
    return novo;
}

int main()
{
    int valorAleatorio;
    FolhaAVL registro;
    for(int i=0;i<10;i++){
        valorAleatorio=rand()%100;
        registro=criaRegistro(valorAleatorio);
        printf("random=%d registro.dado=%d reg.FB=%d\n",valorAleatorio,registro.dado,registro.FatorBalanco);
    }
    return 0;
}
