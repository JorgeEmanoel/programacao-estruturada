#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/string.h"
#include "models/Funcionario.h"

int main() {
    int op = 0, tmp_int;
    Funcionario tmpFuncionario;

    do {
        // system("clear");
        printf("Escolha uma opção:");
        printf("\n0 - Sair");
        printf("\n1 - Cadastrar funcionario");
        printf("\n2 - Listar funcionarios");
        printf("\n3 - Buscar funcionario");
        printf("\n4 - Remover funcionario");
        printf("\n5 - Editar funcionario");

        printf("\nOpção: ");
        scanf("%d", &op);

        system("clear");

        switch (op) {
            case 1:
                cadastrarFuncionario();
            break;
            case 2:
                // printf("Funcionarios: %d", contarFuncionarios());
                if (!contarFuncionarios()) {
                    printf("\nNenhum funcionario cadastrado.\n");
                } else {
                    listarFuncionarios();
                }
            break;
            case 3:
                system("clear");
                printf("====================== Ver funcionario  ==================\n\n");
                printf("Código do funcionario: ");
                scanf("%d", &tmp_int);
                getchar();

                if (!existeFuncionario(tmp_int)) {
                    printf("Funcionario não encontrado com o código especificado.\n");
                    break;
                }

                tmpFuncionario = buscarFuncionario(tmp_int);

                printf("Nome: %s\n", tmpFuncionario.nome);
                printf("Cargo: %s\n", tmpFuncionario.cargo);
                printf("Data de Nascimento: %s\n", tmpFuncionario.data_nascimento);
                printf("Telefone: %s\n\n", tmpFuncionario.telefone);
            break;
            case 4:
                system("clear");
                printf("====================== Remover funcionario  ==================\n\n");
                printf("Código do funcionario: ");
                scanf("%d", &tmp_int);
                getchar();

                if (!existeFuncionario(tmp_int)) {
                    printf("Funcionario não encontrado com o código especificado.\n");
                    break;
                }

                Funcionario removido = removerFuncionario(tmp_int);
                printf("Funcionario \"%s\" removido com sucesso!\n\n", removido.nome);
            break;
            case 5:
                system("clear");
                printf("====================== Editar funcionario  ==================\n\n");
                printf("Código do funcionario: ");
                scanf("%d", &tmp_int);
                getchar();

                if (!existeFuncionario(tmp_int)) {
                    printf("Funcionario não encontrado com o código especificado.\n");
                    break;
                }

                tmpFuncionario = buscarFuncionario(tmp_int);

                printf("Nome: %s\n", tmpFuncionario.nome);
                printf("Cargo: %s\n", tmpFuncionario.cargo);
                printf("Data de Nascimento: %s\n", tmpFuncionario.data_nascimento);
                printf("Telefone: %s\n\n", tmpFuncionario.telefone);

                printf("\nPreencha os novos dados do funcionario.\n");

                tmp_int = tmpFuncionario.codigo;
                tmpFuncionario = lerFuncionario();
                tmpFuncionario.codigo = tmp_int;
                salvarFuncionario(tmpFuncionario);
                printf("Dados do funcionario atualizados com sucesso.\n\n");
            break;
        }

    } while(op != 0);
}
