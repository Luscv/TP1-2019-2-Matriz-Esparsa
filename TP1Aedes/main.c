#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_MatEsparca.c"
#include "TAD_Produto.c"

int main() {
    int linha, coluna, qtdcompra;
    int checkfunctionL, checkfunctionC, checkfunctionM;
    TCelula *celula;
    TLisprod lisprod;
    TProdutos produtos;
    TLista lista;
    int cod_op;
    char nome_arq[100];
    int qtd_i, qtd_j;

    //Entrada por Arquivo
    FILE *arq;


    printf("Insira o nome do arquivo:\n");
    scanf("%s", nome_arq);
    //printf("%s", nomearq);

    arq = fopen(nome_arq, "r");
    if (arq == NULL) {
        printf("Erro na abertura!\n");
        perror((arq));
        exit(1);
    }

        //Inicializa lista
        InicializaProd(&lisprod);
        //Inicializa Matriz
        InicializaMatriz(&lista);


    do{
        printf("Entre com a operacao desejada:\n");
        printf("*****************************************\n");
        printf("| Codigos de operacao:                  |\n");
        printf("| 1 - Insere dados de compra            |\n");
        printf("| 2 - Imprime Matriz                    |\n");
        printf("| 3 - Imprime cabecas                   |\n");
        printf("| 4 - Inserir Compra                    |\n");
        printf("| 5 - Imprime lista de compra           |\n");
        printf("| 6 - Qtd compra por cliente            |\n");
        printf("| 7 - Qtd compra por produto            |\n");
        printf("| 0 - Encerra                           |\n");
        printf("*****************************************\n");
        fflush(stdin);
        scanf("%d", &cod_op);
        if(cod_op == 1){
            printf("Insira os dados da celula (cliente, produto, data de compra e qtd)\n");

            scanf("%d %d %s %d", &linha, &coluna, produtos.datacompra, &produtos.qtdproduto);

            InsereMatriz(&lista, coluna, linha, &produtos);
        }
        else if(cod_op == 2){
            ImprimeMatriz(&lista);
        }
        else if(cod_op == 3){
            ImprimeMatrizL(&lista, qtd_i);
            ImprimeMatrizC(&lista, qtd_j);
        }
        else if(cod_op == 4){
            scanf("%d %s", &produtos.qtdproduto, produtos.datacompra);
            Insere(&lisprod, &produtos);
        }
        else if(cod_op == 5){
            Imprime(&lisprod);
        }
        else if(cod_op == 6){
            scanf("%d", &linha);
            qtdcompra = qtdCompraporCliente(&lista, &lisprod, linha);
            printf("%d\n", qtdcompra);
        }
        else if(cod_op == 7){
            scanf("%d", &coluna);
            qtdcompra = qtdCompraporProduto(&lista, &lisprod, coluna);
            printf("%d\n", qtdcompra);
        }

    }while(cod_op != 0);
    return 0;
}