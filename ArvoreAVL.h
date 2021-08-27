/**
 *          autor: Pedro Henrique Carneiro de Ara�jo   Matricula: 22108287
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

typedef struct FolhaAVL{
    int dado;
    int FatorBalanco;
    struct FolhaAVL *Esq;
    struct FolhaAVL *Dir;
}FolhaAVL;

FolhaAVL* rotacao_Direita(FolhaAVL *no);
void rotacao_Esquerda(FolhaAVL **no);
FolhaAVL* rotacao_Esq_Dir(FolhaAVL *no);
void rotacao_Dir_Esq(FolhaAVL **no);
int alturaDir(FolhaAVL *no);
int alturaEsq(FolhaAVL *no);
void calculaFatorBalanco(FolhaAVL *no);
FolhaAVL criaRegistro(int info);
FolhaAVL* inserir(FolhaAVL **pPonteiroParaRaiz,int numero,int *cresceu);
void insereAux(int info,FolhaAVL **pontRaiz);
void percorreCalculandoFB(FolhaAVL *pNo);
void visita(FolhaAVL *no);
void emOrdem(FolhaAVL *pNo);
void preOrdem(FolhaAVL *pNo);
void posOrdem(FolhaAVL *pNo);
