#include "TAD_MatEsparca.h"
int InicializaColuna(TLista *lista, int j) {
    Apontador aux;
    int next;
    aux = lista->principal;
    for (next = 0; next < j; next++){
    aux->direita = (Apontador) malloc(sizeof(TCelula)); //Direita points to nova celula
    aux = aux->direita;                       //Ultimo points to nova celula
    aux->linha = 0;                                   //Valor da coluna é o mesmo de aux
    aux->coluna = -1;
    aux->direita = lista->principal;            //Direita(NC) points to celula principal
    aux->abaixo = aux;
    }
    return 1;
}
int InicializaLinha(TLista *lista, int i){
    Apontador aux;
    int next;
    aux = lista->principal;
    for (next = 0; next < i; ++next){
        aux->abaixo = (Apontador) malloc(sizeof(TCelula)); //Abaixo points to nova celula
        aux = aux->abaixo;                       //Ultimo points to nova celula
        aux->linha = -1;                                   //Valor da linha é o mesmo de aux
        aux->coluna = 0;
        aux->abaixo = lista->principal;             //Abaixo(NC) points to celula principal
        aux->direita = aux;
    }
    return 1;
}
int InicializaMatriz(TLista *lista){
    //Criação da célula cabeça principal
    lista->principal = (Apontador) malloc(sizeof(TCelula));   //Inicializa célula cabeça Principal
    lista->principal->direita = lista->principal;
    lista->principal->abaixo = lista->principal;
    lista->principal->linha = -1;                          //Define célula principal (linha -1 por convenção)
    lista->principal->coluna = -1;                         //Define célula principal (coluna -1 por convenção)

    return 1;
}

void ImprimeMatrizC(TLista *lista, int j){
    Apontador aux;
    int next;
    aux = lista->principal->direita;
    for(next = 0; next < j; ++next){
        printf("%d\n", aux->linha);
        printf("%d\n", aux->coluna);
        printf("\n");
        aux = aux->direita;
    }
}

void ImprimeMatrizL(TLista *lista, int i){
    Apontador aux;
    int next;
    aux = lista->principal;
    for(next = 0; next < i+1; ++next){
        printf("%d\n", aux->linha);
        printf("%d\n", aux->coluna);
        printf("\n");
        aux = aux->abaixo;
    }
}

void InsereMatriz(TLista *lista, int coluna, int linha,TProdutos *produtos){
    Apontador newcel;
    Apontador aux;
    int next;
    newcel = (Apontador)malloc(sizeof(TCelula));
    newcel->linha = linha;
    newcel->coluna = coluna;
    InicializaProd(&newcel->lisprod);
    Insere(&newcel->lisprod, produtos);

    // percorre coluna
    aux = lista->principal->direita;

    for(next = 1; next < coluna; next++){
        aux = aux->direita;
    }
    while(linha >= aux->abaixo->linha && aux->linha < aux->abaixo->linha && aux->abaixo->coluna != -1){
        if(linha == aux->abaixo->linha && aux->abaixo->coluna == coluna) {
            Insere(&aux->abaixo->lisprod, produtos);
            free(newcel);
            return;
        }
        aux = aux->abaixo;
    }
    newcel->abaixo = aux->abaixo;
    aux->abaixo = newcel;

    //percorre linha
    aux = lista->principal->abaixo;

    for(next = 1; next < linha; next++){
        aux = aux->abaixo;
    }
    while(coluna >= aux->direita->coluna && aux->coluna < aux->direita->coluna && aux->direita->linha != -1){
        if(linha == aux->direita->linha && aux->direita->coluna == coluna) {
            Insere(&aux->abaixo->lisprod, produtos);
            free(newcel);
            return;
        }
        aux = aux->direita;
    }
    newcel->direita = aux->direita;
    aux->direita = newcel;


}

void ImprimeMatriz(TLista *lista){
    Apontador aux;
    aux = lista->principal->abaixo;
    while (aux->coluna != -1){

        aux = aux->direita;
        if(aux->coluna == 1){
            printf("\nCliente: %d\n",aux->linha);
        }

        if(aux->linha == -1){
            printf("\n");
            aux = aux->abaixo;
        }else {
            printf("Produto %d: ",aux->coluna);
            Imprime(&aux->lisprod);
        }

    }
}

int LeMatriz(FILE *ptr_arq, TLista *lista, int qtd_i, int qtd_j) {

    int i, j, qtd;
    char data[11];
    char linha[] = "";
    char ch[] = " ";
    int checkfunctionC, checkfunctionL;

    //Células cabeça criadas a partir da principal de acordo com o número de linhas e colunas
    //Linhas
    checkfunctionC = InicializaColuna(lista, qtd_j);
    //colunas
    checkfunctionL = InicializaLinha(lista, qtd_i);

    if (checkfunctionL == 1 && checkfunctionC == 1) {
        printf("Linha inicializada com sucesso...\n");
        printf("Coluna inicializada com sucesso...\n");
        printf("Matriz incializada com sucesso!\n");
    } else {
        printf("Matriz não inicializada\n");
    }

    while (fgets(linha, 400, ptr_arq) !=
           NULL) { //Lê o arquivo escolhendo o item da matriz e definindo os valores da lista
        char *ptr = strtok(linha, " ");
        while (ptr != NULL) {
            printf("\n%s", ptr);
            ptr = strtok(NULL, " ");
        }
    }
}

int qtdCompraporProduto(TLista *lista, TLisprod *lisprod, int coluna){
    int next, qtdcompra;
    Apontador aux;
    Apontadorp pAux;
    aux = lista->principal->direita;
    qtdcompra = 0;
    for (next = 0; next < coluna; next++) {
        aux = aux->direita;
    }
    while(aux->abaixo->linha != 0 && aux->abaixo->coluna == -1){
        aux = aux->abaixo;
        pAux = lisprod->Primeiro;
        while(pAux != NULL){
            pAux = pAux->prox;
            qtdcompra += pAux->produtos.qtdproduto;
        }
    }

    return qtdcompra;
}
int qtdCompraporCliente(TLista *lista, TLisprod *lisprod, int linha){
    int next, qtdcompra;
    Apontador aux;
    Apontadorp pAux;
    aux = lista->principal->abaixo;
    qtdcompra = 0;
    for (next = 0; next < linha; next++) {
        aux = aux->direita;
    }
    while(aux->abaixo->linha != 0 && aux->abaixo->coluna == -1){
        aux = aux->direita;
        pAux = lisprod->Primeiro;
        while(pAux != NULL){
            pAux = pAux->prox;
            qtdcompra += pAux->produtos.qtdproduto;
        }
    }

    return qtdcompra;
}






