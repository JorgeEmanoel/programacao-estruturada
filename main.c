#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/string.h"
#include "utils/common.h"

#include "models/Funcionario.h"
#include "models/Produto.h"
#include "models/Venda.h"

void moduloVendas();
void moduloProdutos();
void moduloFuncionarios();
void moduloRelatorios();

int main() {

    int op = 0, tmpInt;

    do {
        breadcrumb("Painel de Controle");
        printf("Bem-vindo(a)\n\n");
        printf("Escolha um módulo:\n");
        printf("1 - Produtos\n");
        printf("2 - Funcionários\n");
        printf("3 - Vendas\n");
        printf("4 - Relatórios\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                moduloProdutos();
            break;
            case 2:
                moduloFuncionarios();
            break;
            case 3:
                moduloVendas();
            break;
            case 4:
                moduloRelatorios();
            break;
            default:
                printf("\nOpção inválida!\n");
            break;
        }

    } while(op != 0);


    return 0;
}

void moduloProdutos() {
    int op = 0, tmpInt;
    Produto tmpProduto;

    do {
        breadcrumb("Painel de Controle / Módulo de Produtos");
        printf("Escolha uma opção:");
        printf("\n1 - Cadastrar produto");
        printf("\n2 - Listar produtos (%d)", contarProdutos());
        printf("\n3 - Buscar produto");
        printf("\n4 - Remover produto");
        printf("\n5 - Editar produto");
        printf("\n0 - Voltar");

        printf("\nOpção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                breadcrumb("Painel de Controle / Módulo de Produtos/ Cadastrar");
                getchar();

                if (!contarFuncionarios()) {
                    printf("Nenhum funcionário cadastrado. Impossível criar um produto.\n");
                    break;
                }

                Produto produto = lerProduto();

                if (!confirm("Deseja realmente salvar o produto?")) {
                    printf("Ação cancelada pelo usuário.\n");
                    break;
                }

                salvarProduto(produto);
                printf("Produto salvo com sucesso.");
            break;
            case 2:
                breadcrumb("Painel de Controle / Módulo de Produtos / Listar");
                if (!contarProdutos()) {
                    printf("Nenhum produto cadastrado.\n");
                } else {
                    listarProdutos();
                }
            break;
            case 3:
                breadcrumb("Painel de Controle / Módulo de Produtos/ Buscar");
                printf("Código do produto: ");
                scanf("%d", &tmpInt);

                if (!existeProduto(tmpInt)) {
                    printf("Produto não encontrado com o código especificado.\n");
                    break;
                }

                tmpProduto = buscarProduto(tmpInt);

                printf("Descrição: %s\n", tmpProduto.descricao);
                printf("Data de Entrada: %s\n", tmpProduto.data_entrada);
                printf("Unidade de medida: %s\n", tmpProduto.unidade_medida);
                printf("Quantidade: %d\n", tmpProduto.quantidade);
                printf("Quantidade mínima: %d\n\n", tmpProduto.quantidade_minima);
            break;
            case 4:
                breadcrumb("Painel de Controle / Módulo de Produtos/ Remover produto");
                printf("Código do produto: ");
                scanf("%d", &tmpInt);

                if (!existeProduto(tmpInt)) {
                    printf("Produto não encontrado com o código especificado.\n");
                    break;
                }

                if (contarVendasProduto(tmpInt)) {
                    printf("Não é possível excluir este produto pois ele possui vendas registradas.\n");
                    break;
                }

                if (!confirm("Deseja realmente remover o produto selecionado?")) {
                    printf("Ação cancelada pelo usuário.\n");
                    break;
                }

                Produto removido = removerProduto(tmpInt);
                printf("Produto \"%s\" removido com sucesso!\n\n", removido.descricao);
            break;
            case 5:
                breadcrumb("Painel de Controle / Módulo de Produtos/ Editar produto");
                printf("Código do produto: ");
                scanf("%d", &tmpInt);

                if (!existeProduto(tmpInt)) {
                    printf("Produto não encontrado com o código especificado.\n");
                    break;
                }

                tmpProduto = buscarProduto(tmpInt);

                printf("Data de Entrada: %s\n", tmpProduto.data_entrada);
                printf("Descrição: %s\n", tmpProduto.descricao);
                printf("Unidade de medida: %s\n", tmpProduto.unidade_medida);
                printf("Quantidade: %d\n", tmpProduto.quantidade);
                printf("Quantidade mínima: %d\n\n", tmpProduto.quantidade_minima);

                printf("\nPreencha os novos dados do produto.\n");

                tmpInt = tmpProduto.codigo;
                getchar();
                tmpProduto = lerProduto();

                if (!confirm("Deseja realmente salvar as alterações?")) {
                    printf("Ação cancelada pelo usuário.\n");
                    break;
                }

                tmpProduto.codigo = tmpInt;
                salvarProduto(tmpProduto);
                printf("Dados do produto atualizados com sucesso.\n");
            break;
            case 0:
            break;
            default:
                printf("Operação inválida.");
        }

        if (op != 0)
            wait();

    } while(op != 0);
}

void moduloFuncionarios() {
    int op = 0, tmpInt;
    Funcionario tmpFuncionario;

    do {
        breadcrumb("Painel de Controle / Módulo de Funcionários");
        printf("Escolha uma opção:");
        printf("\n1 - Cadastrar funcionario");
        printf("\n2 - Listar funcionarios (%d)", contarFuncionarios());
        printf("\n3 - Buscar funcionario");
        printf("\n4 - Remover funcionario");
        printf("\n5 - Editar funcionario");
        printf("\n0 - Voltar");

        printf("\nOpção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                breadcrumb("Painel de Controle / Módulo de Funcionários / Cadastrar");
                printf("Cadastro de funcionario:\n");
                getchar();

                Funcionario funcionario = lerFuncionario();
                getchar();

                if (!confirm("Deseja salvar o funcionário?")) {
                    printf("Ação cancelada pelo usuário.\n");
                    break;
                }

                salvarFuncionario(funcionario);
                printf("Funcionario salvo com sucesso.\n");
            break;
            case 2:
                breadcrumb("Painel de Controle / Módulo de Funcionários / Listar");
                if (!contarFuncionarios()) {
                    printf("\nNenhum funcionario cadastrado.\n");
                } else {
                    listarFuncionarios();
                }
            break;
            case 3:
                breadcrumb("Painel de Controle / Módulo de Funcionários / Buscar");
                printf("Código do funcionario: ");
                scanf("%d", &tmpInt);

                if (!existeFuncionario(tmpInt)) {
                    printf("Funcionario não encontrado com o código especificado.\n");
                    break;
                }

                tmpFuncionario = buscarFuncionario(tmpInt);

                printf("Nome: %s\n", tmpFuncionario.nome);
                printf("Cargo: %s\n", tmpFuncionario.cargo);
                printf("Data de Nascimento: %s\n", tmpFuncionario.data_nascimento);
                printf("Telefone: %s\n", tmpFuncionario.telefone);
                printf("Produtos: %d\n", contarProdutosFuncionario(tmpFuncionario.codigo));
                printf("Vendas: %d\n\n", contarVendasFuncionario(tmpFuncionario.codigo));
            break;
            case 4:
                breadcrumb("Painel de Controle / Módulo de Funcionários / Remover");
                printf("Código do funcionario: ");
                scanf("%d", &tmpInt);

                if (!existeFuncionario(tmpInt)) {
                    printf("Funcionario não encontrado com o código especificado.\n");
                    break;
                }

                if (contarProdutosFuncionario(tmpInt) || contarVendasFuncionario(tmpInt)) {
                    printf("Não é possível excluir este funcionário, pois já possui vendas ou produtos no sistema.\n");
                    break;
                }

                if (!confirm("Deseja realmente remover o funcionário selecionado?")) {
                    printf("Ação cancelada pelo usuário.\n");
                    break;
                }

                Funcionario removido = removerFuncionario(tmpInt);
                printf("Funcionario \"%s\" removido com sucesso!\n\n", removido.nome);
            break;
            case 5:
                breadcrumb("Painel de Controle / Módulo de Funcionários / Editar");
                printf("Código do funcionario: ");
                scanf("%d", &tmpInt);

                if (!existeFuncionario(tmpInt)) {
                    printf("Funcionario não encontrado com o código especificado.\n");
                    break;
                }

                tmpFuncionario = buscarFuncionario(tmpInt);

                printf("Nome: %s\n", tmpFuncionario.nome);
                printf("Cargo: %s\n", tmpFuncionario.cargo);
                printf("Data de Nascimento: %s\n", tmpFuncionario.data_nascimento);
                printf("Telefone: %s\n\n", tmpFuncionario.telefone);

                printf("\nPreencha os novos dados do funcionario.\n");
                getchar();

                tmpInt = tmpFuncionario.codigo;
                tmpFuncionario = lerFuncionario();

                if (!confirm("Deseja salvar as alterações feitas no funcionário?")) {
                    printf("Ação cancelada pelo usuário.\n");
                    break;
                }

                tmpFuncionario.codigo = tmpInt;
                salvarFuncionario(tmpFuncionario);
                printf("Dados do funcionario atualizados com sucesso.\n\n");
            break;
        }

        if (op != 0)
            wait();

    } while(op != 0);
}

void moduloVendas() {
    int op = 0, tmpInt;
    Venda tmpVenda;
    Produto tmpProduto;

    do {
        breadcrumb("Painel de Controle / Módulo de Vendas");
        printf("Escolha uma opção:");
        printf("\n1 - Cadastrar venda");
        printf("\n2 - Listar vendas (%d)", contarVendas());
        printf("\n3 - Buscar venda");
        printf("\n0 - Voltar");

        printf("\nOpção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                breadcrumb("Painel de Controle / Módulo de Vendas / Cadastrar");

                if (!contarProdutos() || !contarFuncionarios()) {
                    printf("Pelo menos um produto e um funcionario devem estar cadastrados no sistema.\n");
                    break;
                }

                printf("Cadastro de venda:\n");
                getchar();

                Venda venda = lerVenda();
                fflush(stdin);

                if (!confirm("Salvar dados da venda?")) {
                    printf("Ação cancelada pelo usuário.\n");
                    break;
                }

                tmpProduto = buscarProduto(venda.produto_codigo);
                tmpProduto.quantidade -= venda.quantidade;

                if (tmpProduto.quantidade < 0) {
                    printf("\nNão existe esta quantidade disponível em estoque.\n");
                    printf("\nQuantidade disponível para o produto: %d\n", tmpProduto.quantidade);
                    salvarVendaNegativa(venda);
                    break;
                }

                if (tmpProduto.quantidade < tmpProduto.quantidade_minima) {
                    printf("O produto está com a quantidade menor qua a quantidade mínima definida.\n");
                    printf("Estoque: %d\nQuantidade mínima: %d\n", tmpProduto.quantidade, tmpProduto.quantidade_minima);
                    printf("Não é possível finalizar a venda.\n");
                    salvarVendaSemEstoque(venda);
                    break;
                }

                salvarVenda(venda);
                salvarProduto(tmpProduto);
                printf("Venda registrada com sucesso.\n");

            break;
            case 2:
                breadcrumb("Painel de Controle / Módulo de Vendas / Listar");

                if (!contarVendas()) {
                    printf("Nenhuma venda cadastrada.\n");
                    break;
                }

                listarVendas();
            break;
            case 3:
                breadcrumb("Painel de Controle / Módulo de Vendas / Buscar");
                printf("Código da venda: ");
                scanf("%d", &tmpInt);

                if (!existeVenda(tmpInt)) {
                    printf("Venda não encontrada com o código especificado.\n");
                    break;
                }

                tmpVenda = buscarVenda(tmpInt);

                Funcionario funcionario = buscarFuncionario(tmpVenda.funcionario_codigo);
                tmpProduto = buscarProduto(tmpVenda.produto_codigo);
                printf("Código: %d\n", tmpVenda.codigo);
                printf("Data: %s\n", tmpVenda.data);
                printf("Produto: %s", tmpProduto.descricao);
                printf("Valor unitário: %.2f\n", tmpVenda.preco);
                printf("Quantidade: %d\n", tmpVenda.quantidade);
                printf("Valor total: %.2f\n", tmpVenda.quantidade * tmpVenda.preco);
                printf("Funcionário: %s (ID: %d)\n\n", funcionario.nome, tmpVenda.funcionario_codigo);
            break;
            case 0:
            break;
            default:
                printf("Opção inválida.\n");
        }

        if (op != 0)
            wait();

    } while(op != 0);
}

void moduloRelatorios() {
    int op = 0, tmpInt;
    Produto tmpProduto;
    Funcionario tmpFuncionario;
    Venda tmpVenda;
    char data[10];
    int dataInicio, dataFim;

    do {
        breadcrumb("Painel de Controle / Módulo de Relatórios");
        printf("Escolha uma opção:");
        printf("\n1 - Vendas realizadas");
        printf("\n2 - Produto mais vendido");
        printf("\n3 - Funcinário mais lucrativo");
        printf("\nOpção: ");
        scanf("%d", &op);
        getchar();

        printf("Data de início (dd/mm/aaaa): ");
        stread(data, 11);
        while (!datevalid(data)) {
            breadcrumb("Painel de Controle / Módulo de Relatórios");
            printf("Data inválida (%s). Utilize o formato: dd/mm/aaaa\n", data);
            printf("Data de início: ");
            stread(data, 11);
        };

        getchar();
        dataInicio = formatdate(data);

        printf("Data final (dd/mm/aaaa): ");
        stread(data, 11);
        while (!datevalid(data)) {
            breadcrumb("Painel de Controle / Módulo de Relatórios");
            printf("Data inválida (%s). Utilize o formato: dd/mm/aaaa\n", data);
            printf("Data final: ");
            stread(data, 11);
        };

        dataFim = formatdate(data);

        switch (op) {
            case 1:
                if (!contarVendas()) {
                    printf("Nenhuma venda realizada.\n");
                    break;
                }

                int entrada;

                FILE *f = fopen("database/vendas.bin", "rb");
                while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
                    entrada = formatdate(tmpVenda.data);
                    if (entrada >= dataInicio && entrada <= dataFim) {
                        tmpFuncionario = buscarFuncionario(tmpVenda.funcionario_codigo);
                        tmpProduto = buscarProduto(tmpVenda.produto_codigo);
                        printf("Código: %d\n", tmpVenda.codigo);
                        printf("Data: %s\n", tmpVenda.data);
                        printf("Produto: %s", tmpProduto.descricao);
                        printf("Valor unitário: %.2f\n", tmpVenda.preco);
                        printf("Quantidade: %d\n", tmpVenda.quantidade);
                        printf("Valor total: %.2f\n", tmpVenda.quantidade * tmpVenda.preco);
                        printf("Funcionário: %s (ID: %d)\n\n", tmpFuncionario.nome, tmpVenda.funcionario_codigo);
                    }
                }
                fclose(f);
            break;
            case 2:
                int id;
                float maior = 0;
                
            break;
            case 0:
            break;
            default:
                printf("Opção inválida.\n");
        }

        wait();

    } while (op != 0);
}
