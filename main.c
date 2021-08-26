#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
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
FolhaAVL* rotacao_Direita(FolhaAVL *no){
    printf("\t\tROTACAO DIREITA\n\tno->dado:%d no->esq->dado:%d no->dir:%x",no->dado,no->Esq->dado,no->Dir);
    FolhaAVL *q,*temporario;
    temporario=no;//copia o valor de no para mexer nele
    q=no->Esq;//q aponta para esquerda de n�
    temporario->Esq=q->Dir;// esquerda de n� aponta para direita de q (pois o valor no>q.DIR>q)
    q->Dir=temporario;//direita de q aponta para no (pois valor no>q)
    q->FatorBalanco=0;//zera o FB de q
    temporario->FatorBalanco=0;//zera o fb de no
    no=q;//troca no de lugar para q
    //printf("\t fim rotacao direita\tno->dado:%d no->esq:%d no->dir:%d\n",no->dado,no->Esq->dado,no->Dir->dado);
    return no;
}
void rotacao_Esquerda(FolhaAVL **no){
    FolhaAVL *a,*b;
    a=*no;//salva o valor de no
    b=a->Dir;//b aponta para direita de no (logo valor b>no)
    a->Dir=b->Esq;//no aponta para esquerda de b (pois valor b->esq<b>no)
    b->Esq=a;//esquerda de b aponta no (pois b->esq<b>no)
    a->FatorBalanco=0;
    b->FatorBalanco=0;
    *no=b;//troca no de lugar para b
}
FolhaAVL* rotacao_Esq_Dir(FolhaAVL *no){
    printf("\t\t\t\t <<<< ROTACAO ESQUERDA-DIREITA >>>>\n");
    int FatorBalancoNo=no->FatorBalanco;
    rotacao_Esquerda(&no->Esq);
    no=rotacao_Direita(no);

    FolhaAVL *a=no->Esq,*b=no->Dir;
    switch(FatorBalancoNo){
        case -1:
            a->FatorBalanco=0;b->FatorBalanco=1;break;
        case 0:
            a->FatorBalanco=0;b->FatorBalanco=0;break;
        case 1:
            a->FatorBalanco=-1;b->FatorBalanco=0;break;
    }
    //no->FatorBalanco=0;//ja foi iterado
    printf("no->FB antes:%d depois:%d\n\tno.esq.dado:%d no.esq.fatorbalan�o:%d\n",no->FatorBalanco,FatorBalancoNo,no->Esq->dado,no->Esq->FatorBalanco);
    return no;
}
void rotacao_Dir_Esq(FolhaAVL **no){//essa fun��o retorna void por isso devo passar um **no para trabalhar mas como nao foi chamada...
    printf("\t\t\t\t <<<< Rota��o Direita Esquerda >>>>\n");
    FolhaAVL *noAtual=*no;printf("passou a linha 110 noAtual:%d *no:%x *no->dado: tem que ser 53\n",noAtual->dado,*no);
    int FatorBalancoNo=noAtual->FatorBalanco;printf("passou a linha 111 noAtual->fb:%d\n",noAtual->FatorBalanco);
    noAtual->Dir=rotacao_Direita(noAtual->Dir);printf("passou a linha 112\n");
    rotacao_Esquerda(&noAtual);printf("passou a linha 113\n");

    FolhaAVL *a=noAtual->Esq,*b=noAtual->Dir;
    switch(FatorBalancoNo){
        case -1:
            a->FatorBalanco=0;b->FatorBalanco=1;break;
        case 0:
            a->FatorBalanco=0;b->FatorBalanco=0;break;
        case 1:
            a->FatorBalanco=-1;b->FatorBalanco=0;break;
    }
    //no->FatorBalanco=0;//ja iterado
    *no=noAtual;
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
 * por�m com algumas modifica��es.
 */

 //criaRegistro: cria e armazena um tipo FolhaAVL a partir de um valor inteiro.
FolhaAVL criaRegistro(int info){
    FolhaAVL novo;
    novo.dado=info;
    novo.FatorBalanco=0;
    novo.Dir=NULL;
    novo.Esq=NULL;

    return novo;
}
//insere: busca uma posi��o e insere uma nova FolhaAVL a uma subarvore.
//inserir: Cria um novo registro e o insere na arvore.
FolhaAVL* inserir(FolhaAVL **pPonteiroParaRaiz,int numero,int *cresceu){
    FolhaAVL *pRaiz=*pPonteiroParaRaiz;
    printf("come�ou \nnumero a inserir:%d \npRaiz=%x\n",numero,pRaiz);
    if(pRaiz==NULL)
    {
        pRaiz=(FolhaAVL *)malloc(sizeof(FolhaAVL));printf("pRaiz==NULL\n");
        if(pRaiz==NULL)
            return 0;// erro de insercao, n�o tem mem�ria.
        else
        {
            (pRaiz)->dado=numero;//printf("inserido numero:%d em pRaiz:%x que esta em %x\n",(pRaiz)->dado,pRaiz,&pRaiz);
            (pRaiz)->Dir=NULL;
            (pRaiz)->Esq=NULL;
            (pRaiz)->FatorBalanco=0;
            *pPonteiroParaRaiz=pRaiz;
            *cresceu=TRUE;
            return pRaiz;//sucesso inser��o
        }
    }else if(numero<=(pRaiz)->dado){
        printf("%d comparado a raiz %d\n",numero,pRaiz->dado);
        //printf("numero menor \n");
        if(pRaiz->Esq=inserir(&(pRaiz)->Esq,numero,cresceu)){printf("chamada:%d esquerda:%d conseguiu inserir %d cresceu:%d\n",pRaiz->dado,
                                                         pRaiz->Esq->dado,numero,*cresceu);
            if(*cresceu){//caso tenha conseguido inserir a esquerda.
                    printf("AVALIA BALANCO ESQUERDA,no->dado:%d\n",pRaiz->dado);
                switch((*pRaiz).FatorBalanco){
                    case -1://desbalanceado a esquerda
                        printf("case -1\n");
                        if((pRaiz)->Esq->FatorBalanco==-1){
                            printf("ROTACAO DIREITA\n");pRaiz=rotacao_Direita(pRaiz);
                        }else{ printf("ROTACAO ESQ DIREITA pRaiz:%d\n",pRaiz->dado);pRaiz=rotacao_Esq_Dir(pRaiz);
                        printf("AO FINAL DA ROT_ESQ_DIR pRaiz:%d\n",pRaiz->dado);}//Sinais trocados
                        *cresceu=FALSE;
                        break;
                    case 0:
                        printf("case 0 FB=-1\n");
                        (pRaiz)->FatorBalanco=-1;
                        *cresceu=TRUE;printf("FATOR BALANCO:0 apenas colocou -1 em Raiz\n");
                        break;
                    case 1://direita maior
                        printf("CASE 1\n");
                        (pRaiz)->FatorBalanco=0;printf("(pRaiz)->info:%d FatorBalanco:%d\n",(pRaiz)->dado,(pRaiz)->FatorBalanco);
                        *cresceu=FALSE;
                        break;
                }//Fimswitch
            }//FimIF(cresceu)
            return pRaiz;
        }
        else return FALSE;
    }else{
        FolhaAVL *Direita=pRaiz->Dir;
        printf("%d comparado a raiz %d\n",numero,pRaiz->dado);
        if(pRaiz->Dir=inserir(&(pRaiz)->Dir,numero,cresceu)){printf("chamada:%d direita:%d conseguiu inserir %d cresceu:%d\n",pRaiz->dado
                                                         ,pRaiz->Dir->dado,numero,*cresceu);
            //if(Direita!=pRaiz->Dir){*cresceu=TRUE;}
            if(*cresceu){//inseriu a direita, agora verifica balanco
                    printf("AVALIA BALANCO DIREITA,pRaiz->dado:%d\n",pRaiz->dado);
                switch ((pRaiz)->FatorBalanco){
                    case -1:
                        (pRaiz)->FatorBalanco=0;
                        *cresceu=FALSE;
                        printf("case -1 fb=0\n");
                        break;
                    case 0:
                        (pRaiz)->FatorBalanco=1;*cresceu=TRUE;printf("case 0: acrescenta 1\n");
                        break;
                    case 1:
                        if((pRaiz)->Dir->FatorBalanco==1){printf("case 1: vai rotacionar a esquerda");
                            rotacao_Esquerda(&pRaiz);*cresceu=TRUE;printf("\nrodou Esquerda pRaiz.dado:%d pRaiz.FB:%d pRaiz.esq:%d pRaiz.dir:%d cresceu=%d\n"
                                                                          ,pRaiz->dado,pRaiz->FatorBalanco,pRaiz->Esq->dado,pRaiz->Dir->dado,*cresceu);
                        }else rotacao_Dir_Esq(&pRaiz);*cresceu=FALSE;
                        break;
                }//FIMSWITCH
            }
            return pRaiz;
        }//FIMIF(insereDireita)
        else return FALSE;// nao conseguiu inserir
    }
}//FimInsere
/*
 * Existem tamb�m as famosas fun��es recursivas para percorrimento da arvore em diversas ordens
*/
void visita(FolhaAVL *no){
    printf("No: %d\n",no->dado);
}
void emOrdem(FolhaAVL *pNo) {
     if(pNo != NULL) {
         emOrdem(pNo->Esq);
         visita(pNo);
         emOrdem(pNo->Dir);
     }
 }
 void preOrdem(FolhaAVL *pNo){
     if(pNo != NULL){
         visita(pNo);
         preOrdem(pNo->Esq);
         preOrdem(pNo->Dir);
     }
 }
 void posOrdem(FolhaAVL *pNo){
     if(pNo != NULL){
         posOrdem(pNo->Esq);
         posOrdem(pNo->Dir);
         visita(pNo);
     }
 }
int main()
{
    setlocale(LC_ALL,"ptb");//Traduz os caracteres para portugues.

    int valorAleatorio,total=60;
    FolhaAVL *RaizArvore,**ponteiroParaRaiz;
    RaizArvore=NULL;
    ponteiroParaRaiz=&RaizArvore;
    int aumentou=0;
    printf("RaizArvore:%x &RaizArvore:%x ponteiroParaRaiz:%x\n",RaizArvore,&RaizArvore,ponteiroParaRaiz);


    //if(RaizArvore==NULL){printf("comparou (RaizArvore==NULL)\n");}
    for(int i=0;i<total;i++){
        printf("intera��o:%d\n",i);
        valorAleatorio=rand()%100;
        //printf("inseriu valor: %d\n",valorAleatorio);
        inserir(ponteiroParaRaiz,valorAleatorio,&aumentou);
        printf("\nponteiroParaRaiz:%x RaizArvore:%x RaizArvore->FB:%d\n",ponteiroParaRaiz,RaizArvore,RaizArvore->FatorBalanco);
        printf("\n=============================================\n");
    }
    emOrdem(RaizArvore);

    return 0;
}
