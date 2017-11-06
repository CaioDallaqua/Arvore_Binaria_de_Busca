#define bool int
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
typedef struct{    /*Definição do tipo do elemento*/
    char chave[31];    /*Vetor com uma célula a mais*/
    char info[31];     /*que o limite proposto para armazenar \0*/
}tipoElem;
typedef struct nodo{    /*Definição No*/
    tipoElem elem;
    struct nodo *esq, *dir, *pai;    /*Ponteiros aos filhos esquerdo e direito,*/
}No;                                /* bem como ao pai*/
typedef struct{    /*Definição do tipo da árvore*/
    No *raiz;
    int numNos;    /*Número de nós da árvore*/
}ABB;
ABB *Definir(void);    /*Define a ABB*/
void LiberarNo();    /*Libera memória usada por um nó*/
void Destruir(ABB *A);    /*Libera memótia usada por uma ABB*/
bool ABBvazia(ABB *A);    /*Verifica se a ABB está vazia*/
bool NoExterno(ABB *A, No *N);    /*Retorna 1 se um nó é externo (logo responde se é interno)*/
No *Raiz(ABB *A);    /*Retorna referência à raiz*/
No *Inserir(ABB *A, tipoElem x);    /*Retorna referência ao elemento inserido*/
No *ExpandirExterno(ABB *A, No *N, tipoElem x);    /*Inicializa de modo padrão um nó externo e retorna referência a ele*/
No *InserirABBvazia(ABB *A, tipoElem x);    /*Retorna referência ao elemento inserido*/
tipoElem Remover(ABB *A, char k[]);    /*Retorna elemento removido ou nulo se não há elemento com tal chave na ABB*/
void TrocarNos(ABB *A, No *N, No *M);    /*Troca os elementos de dois nós*/
No *EncontrarSubstituto(ABB *A, No *N);    /*Encontra substituto ao nó que será removido*/
void PercursoIntFix(ABB *A, No *N);    /*Realiza o percurso inter-fixado numa ABB, imprimindo as chaves dos nós em que passa*/
bool SubstituirElem(ABB *A, tipoElem x);    /*Substitui elementos de mesma chave, mas de informações distintas*/
tipoElem Localizar(ABB *A, char k[]);    /*Retorna elemento com a chave procurada*/
No *Buscar(ABB *A, No *N, char k[]);
bool flag = 0;
No *M;
void RemoverCaso1(ABB *A, No *N, No *S);
ABB *Definir(void){    //Definição da ABB
    ABB *A = malloc(sizeof(ABB));   //Alocação de memória à ABB
    if(A == NULL)   //Verifica se alocação foi bem-sucedida
        printf("Alocação sem sucesso\n");//senão imprime isso
    A->raiz = NULL;    //Inicialização
    A->numNos = 0;    //padrão da ABB
    return A;   //Retorna referência à ABB
}
bool ABBvazia(ABB *A){     //Verifica se ABB vazia através de referência a ela
    return (!A->numNos);     //Retorna 1 se vazia, aenão 0
}
bool NoExterno(ABB *A, No *N){     //Verifica N é nó externo
    return ( (N->esq == NULL) && (N->dir == NULL) );     //Retorna 1 se sim, senão 0
}
No *Raiz(ABB *A){   //Retorna referência à raiz da ABB
    return A->raiz;
}
void Destruir(ABB *A){
    if(ABBvazia(A))
        return;
    LiberarNo(A, Raiz(A));
    free(A);
}
void LiberarNo(ABB *A, No *N){
    if(N->esq != NULL)
        LiberarNo(A, N->esq);
    if(N->dir != NULL)
        LiberarNo(A, N->dir);
    free(N);
}
No *Buscar(ABB *A, No *N, char k[]) {     //Busca recursiva na ABB a partir da raiz
    if (N == NULL){     //Verifica se a busca leva para fora da árvore
        //N = malloc(sizeof(No));     //Aloca nó em memória
        //if(N == NULL)     //Verifica se alocação deu certo
         //   printf("Alocação sem sucesso\n");//senão imprime isso
        N->elem.chave[0] = '\0';     //Inicialização padrão do nó
        if (!flag)     //Vê se o nó N é filho direito ou esquerdo
            M->dir = N;
        else
            M->esq = N;
        N->pai = M;     //Ponteiro do novo nó apontado ao pai
        return N;     //Retorna referência ao local na ABB onde a busca levou
    }
    else if (!strcmp(N->elem.chave, k))     //Se encontrar a chave
        return N;                          //retorna referência ao nó onde está
    else if (strcmp(N->elem.chave, k) < 0){     //Vê se N está na sub-árvore
        M = N;                                 //esquerda e leva a recursão
        flag = 1;                             //para lá
        return Buscar(A, N->esq, k);
    }
    else if (strcmp(N->elem.chave, k) > 0){     //Vê se N está na sub-árvore
        M = N;                                 //direita e leva a recursão
        flag = 0;                             //para lá
        return Buscar(A, N->dir, k);
    }
}
No *Inserir(ABB *A, tipoElem x){     //Insere elemento na ABB
    No *N = malloc(sizeof(No));      //Aloca memória ao nó a ser inserido
    if(N == NULL)                    //Vê se alocação deu certo
        printf("Alocação sem sucesso\n");//senão imprime isso
    if(ABBvazia(A))     //Se ABB está vazia
        N = InserirABBvazia(A, x);//Inserção específica
    else{
        N = Buscar(A, Raiz(A), x.chave);     //Busca posição a inserir
        if(!strcmp(N->elem.chave, x.chave))     //Se já há nó com essa chave
            N = NULL;                          //retornará referência a NULL
        else
            N = ExpandirExterno(A, N, x);     //Inserção padrão (em nó folha)
    }
    A->numNos++;     //Atualiza o número de nós da ABB (uso interno, manutenção)
    return N;     //Retorna referência ao elemento inserido ou NULL se já existe
}                //elemento com a mesma chave na ABB
No *ExpandirExterno(ABB *A, No *N, tipoElem x){     //Rotina auxiliar à inserção
    N->dir = NULL;     //Inicialização padrão
    N->esq = NULL;    //de nó
    N->elem = x;
    return N;     //Retorna referência ao nó externo expandido
}
No *InserirABBvazia(ABB *A, tipoElem x){     //Inserção especial
    No *N = malloc(sizeof(No));     //Aloca memória para nó a ser inserido
    if(N == NULL)     //Vê se alocação deu certo
        printf("Alocação sem sucesso\n");//senão imprime isso
    N = ExpandirExterno(A, N, x);     //Expande nó raiz externo
    N->pai=NULL;     //Inicialização padrão
    A->raiz = N;    //para primeiro nó da ABB
    return N;     //Retorna referência ao nó inserido
}
tipoElem Remover(ABB *A, char k[]){     //Remove nó cujo elemento tem chave k[]
    tipoElem x;     //Variável tipoElem auxiliar
    No *N = malloc(sizeof(No));
    if(N == NULL)
        printf("Alocação sem sucesso\n");
    if(!ABBvazia(A))
        N = Buscar(A, Raiz(A), k);     //Busca nó com elemento de chave k[]
    if(ABBvazia(A) || N->elem.chave=='\0'){     //Se ABB vazia ou nó inexistente
         strcpy(x.chave, "\0");     //Inicializa variável auxiliar
         strcpy(x.info, "\0");     //de modo padrão para retorno
    }
    else{
        x = N->elem;     //Variável recebe elemento antes de liberar trocar o nó
        if (!NoExterno(A, N)){     //Se nó a ser removido é interno
            No *S = malloc(sizeof(No));
            if(S == NULL)
                printf("Alocação sem sucesso\n");
            S = EncontrarSubstituto(A, N);     //Encontra substituto
            if(NoExterno(A, S)){     //Se substituto é nó folha
                RemoverCaso1(A, N, S);
                free(S);     //Libera S que agora possui o antigo elemento de N
            }else{     //Se substituto é interno
                if(strcmp(S->elem.chave, N->elem.chave)>0)
                    flag = 1;   //Se o substituto está na sub-árvore esquerda
                else
                    flag = 0;
                if(flag)    //Passo 1
                    if(N->dir != NULL){
                        M = N->dir;
                        M->pai = S;
                    }else
                        S->dir = NULL;
                else
                    if(N->esq != NULL){
                        M = N->esq;
                        M->pai = S;
                    }else
                        S->esq = NULL;
                if(S->pai != N)    //Se o pai de S não for N
                    RemoverCaso2(A, N, S);
                else    //Se o pai de S for N (nó a ser removido)
                    RemoverCaso3(A, N, S);

                free(N);
            }
        }else{
            RemoverCaso4(A, N, k);
            free(N);
        }
        A->numNos--;     //Atualiza o número de nós da ABB
    }
    return x;     //Retorna elemento removido ou nulo se remoção não feita
}
void RemoverCaso1(ABB *A, No *N, No *S){
    TrocarNos(A, N, S);     //Troca N por substituto S
    if(S->pai->esq == S)
        S->pai->esq = NULL;                  //esquerdo
    else                                    //ou
        S->pai->dir = NULL;                //direito
}
void RemoverCaso2(ABB *A, No *N, No *S){
    if(strcmp(S->pai->elem.chave, S->elem.chave)>0){
        S->pai->dir = S->esq;
        S->esq->pai = S->pai;
    }else{
        S->pai->esq = S->dir;
        S->dir->pai = S->pai;
    }
    if(A->raiz == N){
        A->raiz = S;
        S->pai = NULL;
    }
    if(N->esq != NULL)
        S->esq = N->esq;
    else
        S->esq = NULL;
    if(N->dir != NULL)
        S->dir = N->dir;
    else
        S->dir = NULL;
}
void RemoverCaso3(ABB *A, No *N, No *S){
    if(Raiz(A) != N){
        if(strcmp(N->pai->elem.chave, N->elem.chave)>0)
            N->pai->dir = S;
        else
            N->pai->esq = S;
        S->pai = N->pai;
    }else{
        A->raiz = S;
        S->pai = NULL;
        if(flag)
            S->dir = N->dir;
        else
            S->esq = N->esq;
    }
}
void RemoverCaso4(ABB *A, No *N, char k[]){
    if(Raiz(A) == N)     //Se remoção é na raiz e ela é nó externo
        A->raiz = NULL;     //Seta valor padrão à raiz
    else if(strcmp(N->pai->elem.chave, k) < 0)     //Vê se nó é filho esquerdo
        N->pai->esq = NULL;
    else     //Se nó é filho direito
        N->pai->dir = NULL;
}
void TrocarNos(ABB *A, No *N, No *S){     //N-> Nó a ser trocado; S-> Substituto
    No *O = malloc(sizeof(No));     //Nó auxiliar
    if(O == NULL)
        printf("Alocação sem sucesso\n");
    O->elem = N->elem;     //Elemento em N é passado para nó auxiliar
    N->elem = S->elem;     //Elemento em S é passado para N
    S->elem = O->elem;     //Elemento do nó auxiliar é passado para S
    free(O);
}
No *EncontrarSubstituto(ABB *A, No *N){     //N->Nó a ser substituído
    No* S;     //Nó auxiliar
    if(N->dir == NULL){     //Vê se filho direito é nulo
        S = N->esq;
        while(S->dir != NULL)
            S = S->dir;
    }else{      //Se filho direito não for nulo
        S = N->dir;      //N aponta para seu filho direito
        while(S->esq != NULL)      //Enquanto filho esquerdo não for nulo
            S = S->esq;         //N aponta para seu filho esquerdo
    }//printf("%s %s\n", S->elem.chave, S->pai->elem.chave);
    return S;     //Retorna substituto encontrado
}
void PercursoIntFix(ABB *A, No *N){     //Faz percurso inter-fixado recursivamente
    if(ABBvazia(A))     //Se ABB vazia
        return ;       //rotina é terminada
    if(N->esq != NULL)     //Se o filho esquerdo existe
        PercursoIntFix(A, N->esq);//leve a recursão até ele
    puts(N->elem.chave);     //Imprime a chave do elemento atual
    if(N->dir != NULL)     //Se o filho direito existe
        PercursoIntFix(A, N->dir);//leve a recursão até ele
}
bool SubstituirElem(ABB *A, tipoElem x){       //Troca informação do elemento com chave k[]
    No *N = Buscar(A, Raiz(A), x.chave);     //Nó auxiliar recebe retorno de Buscar
    if(!strcmp(N->elem.chave, "\0"))     //Se chave não for encontrada
        return FALSE;                   //retorna falso e a substituição não é feita
    else{                                  //Se chave for encontrada
        strcpy(N->elem.info, x.info);     //informação é substituída no elemento com aquela chave
        return TRUE;                     // e retorna verdadeiro
    }
}

tipoElem Localizar(ABB *A, char k[]){       //Localiza elemento cuja chave é k[]
    tipoElem x;     //Elemento auxiliar
    No *N = Buscar(A, Raiz(A), k);     //Nó auxiliar recebe retorno de Buscar
    if(!strcmp(N->elem.chave, "\0")){     //Se chave não foi encontrada
        x.chave[0] = '\0';     //chave do elemento auxiliar recebe valor padrão
        x.info[0] = '\0';     // e informação do elemento auxiliar recebe valor padrão
    }else{                                   //Se chave foi encontrada
        strcpy(x.chave, N->elem.chave);     //chave do elemento auxiliar recebe valor encontrado
        strcpy(x.info, N->elem.info);      //e informação do elemento auxiliar recebe valor encontrado
    }
    return x;     //Retorna elemento localizado ou nulo
}
char c;
void menu(){
    printf("Escolha a operação ou aperte 0 para sair \n");
    printf("1 - Inserir \n");
    printf("2 - Remover \n");
    printf("3 - Substituir \n");
    printf("4 - Buscar \n");
    printf("5 - Percurso Inter-Fixado \n\n");
    scanf(" %c", &c);
}
void le(char *c){
    int c1 = 0;
    scanf(" %c", &c[c1]);c1++;
    while(scanf("%c", &c[c1]) && c[c1]!='\n'){
        c1++;
    }c[c1] = '\0';
}
int main(){
    tipoElem z;
    char chave[31];
    char info[31];
    ABB *A;
    A = Definir();
    bool a = 0;
    do {
        menu();
        if (c == '1'){
            printf("Insira a chave\n");
            le(chave);
            strcpy(z.chave, chave);
            printf("Insira a informação\n");
            le(info);
            strcpy(z.info, info);
            a = Inserir(A,z);
            if (!a) printf("Elemento não inserido. Chave já existe no Mapa\n\n");
            else printf("Elemento inserido com sucesso\n\n");
        } else if (c == '2'){
            printf("Insira a chave do elemento a ser removido\n");
            le(chave);
            z = Remover(A, chave);
            if(strcmp(z.chave, "\0")){
                printf("O elemento removido foi: \n");
                printf("Chave: %s\n", z.chave);
                printf("Informação: %s\n\n", z.info);
            } else printf("Elemento inexistente no Mapa\n\n");
        }else if (c == '3'){
            printf("Insira o elemento a ser substituído\n");
            printf("Insira a chave\n");
            le(chave);
            strcpy(z.chave, chave);
            printf("Insira a informação\n");
            le(info);
            strcpy(z.info, info);
            a = SubstituirElem(A,z);
            if (a==1) printf("Elemento substituído com sucesso\n\n");
            else printf("Elemento não substituído. Chave não existe no Mapa\n\n");
        } else if(c == '4'){
            printf("Insira a chave a ser buscada\n");
            le(chave);
            printf("\n");
            z = Localizar(A, chave);
            if(strcmp(z.chave, "\0") != 0){
                printf("O elemento encontrado foi: \n");
                printf("%s\n", z.chave);
                printf("%s\n\n", z.info);
            } else printf("Elemento inexistente no Mapa\n\n");
        }else if(c == '5'){
            printf("\n");
            PercursoIntFix(A, Raiz(A));
            printf("\n");
        }else if(c != '0')
            printf("Indisponivel no menu\n");
    }while(c != '0');
return 0;
}
