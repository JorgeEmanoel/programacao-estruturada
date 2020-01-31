#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/string.h"
#include "models/Venda.h"

int main() {
    int op = 0, tmp_int;
    Venda tmpVenda;

    do {
        // system("clear");
        printf("Escolha uma opção:");
        printf("\n0 - Sair");
        printf("\n1 - Cadastrar venda");
        printf("\n2 - Listar vendas");
        printf("\n3 - Buscar venda");

        printf("\nOpção: ");
        scanf("%d", &op);

        system("clear");

        switch (op) {
            case 1:
                cadastrarVenda();
            break;
            case 2:
                listarVendas();
            break;
            case 3:
                system("clear");
                printf("====================== Buscar venda  ==================\n\n");
                printf("Código da venda: ");
                scanf("%d", &tmp_int);
                getchar();

                if (!existeVenda(tmp_int)) {
                    printf("Venda não encontrada com o código especificado.\n");
                    break;
                }

                tmpVenda = buscarVenda(tmp_int);

                printf("Código: %d\n", tmpVenda.codigo);
                printf("Data: %s\n", tmpVenda.data);
                printf("Preço: %.2f\n", tmpVenda.preco);
                printf("Quantidade: %d\n", tmpVenda.quantidade);
                printf("Valor total: %.2f\n", tmpVenda.quantidade * tmpVenda.quantidade);
            break;
        }

    } while(op != 0);
}
