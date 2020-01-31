#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/string.h"
#include "models/Produto.h"

int main() {
    int op = 0, tmp_int;
    Produto tmpProduto;

    do {
        // system("clear");
        printf("Escolha uma opção:");
        printf("\n0 - Sair");
        printf("\n1 - Cadastrar produto");
        printf("\n2 - Listar produtos");
        printf("\n3 - Buscar produto");
        printf("\n4 - Remover produto");
        printf("\n5 - Editar produto");

        printf("\nOpção: ");
        scanf("%d", &op);

        system("clear");

        switch (op) {
            case 1:
                cadastrarProduto();
            break;
            case 2:
                listarProdutos();
            break;
            case 3:
                system("clear");
                printf("====================== Ver produto  ==================\n\n");
                printf("Código do produto: ");
                scanf("%d", &tmp_int);
                getchar();

                if (!existeProduto(tmp_int)) {
                    printf("Produto não encontrado com o código especificado.\n");
                    break;
                }

                tmpProduto = buscarProduto(tmp_int);

                printf("\nCódigo: %d\nDescrição: %s\n", tmpProduto.codigo, tmpProduto.descricao);
                printf("Unidade de medida: %s\nQuantidade: %d\n", tmpProduto.unidade_medida, tmpProduto.quantidade);
                printf("Quantidade mínima: %d\n\n", tmpProduto.quantidade_minima);
            break;
            case 4:
                system("clear");
                printf("====================== Remover produto  ==================\n\n");
                printf("Código do produto: ");
                scanf("%d", &tmp_int);
                getchar();

                if (!existeProduto(tmp_int)) {
                    printf("Produto não encontrado com o código especificado.\n");
                    break;
                }

                Produto removido = removerProduto(tmp_int);
                printf("Produto \"%s\" removido com sucesso!\n\n", removido.descricao);
            break;
            case 5:
                system("clear");
                printf("====================== Editar produto  ==================\n\n");
                printf("Código do produto: ");
                scanf("%d", &tmp_int);
                getchar();

                if (!existeProduto(tmp_int)) {
                    printf("Produto não encontrado com o código especificado.\n");
                    break;
                }

                tmpProduto = buscarProduto(tmp_int);

                printf("\nCódigo: %d\nDescrição: %s\n", tmpProduto.codigo, tmpProduto.descricao);
                printf("Unidade de medida: %s\nQuantidade: %d\n", tmpProduto.unidade_medida, tmpProduto.quantidade);
                printf("Quantidade mínima: %d\n\n", tmpProduto.quantidade_minima);

                printf("\nPreencha os novos dados do produto.\n");

                tmp_int = tmpProduto.codigo;
                tmpProduto = lerProduto();
                tmpProduto.codigo = tmp_int;
                salvarProduto(tmpProduto);
                printf("Dados do produto atualizados com sucesso.\n\n");
            break;
        }

    } while(op != 0);
}
