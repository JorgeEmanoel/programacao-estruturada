int produto_autoincremento = 0;

typedef struct {
    int codigo;
    char descricao[30];
    char unidade_medida[10];
    char data_entrada[10];
    float preco;
    int quantidade;
    int quantidade_minima;
    int funcionario_codigo;
} Produto;


void cadastrarProduto();
void salvarProduto(Produto produto);
void listarProdutos();
void copiarProdutos();
int existeProduto(int codigo);
int contarProdutos();
int contarProdutosFuncionario(int codigo);
Produto lerProduto();
Produto buscarProduto();
Produto removerProduto();

int existeProduto(int codigo) {
    FILE *f;
    Produto tmpProduto;
    f = fopen("database/produtos.bin", "rb");
    while (fread(&tmpProduto, sizeof(Produto), 1, f)) {
        if (codigo == tmpProduto.codigo) {
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int contarProdutos() {
    FILE *f;
    Produto tmpProduto;
    f = fopen("database/produtos.bin", "rb");
    int qtd = 0;
    if (!f) {
        return 0;
    }
    while (fread(&tmpProduto, sizeof(Produto), 1, f)) {
        qtd++;
    }
    fclose(f);
    return qtd;
}

int contarProdutosFuncionario(int codigo) {
    FILE *f;
    Produto tmpProduto;
    f = fopen("database/produtos.bin", "rb");
    int qtd = 0;
    if (!f) {
        return 0;
    }
    while (fread(&tmpProduto, sizeof(Produto), 1, f)) {
        if (tmpProduto.funcionario_codigo == codigo)
            qtd++;
    }
    fclose(f);
    return qtd;
}

void copiarProdutos() {
    FILE *tf, *f;
    Produto tmpProduto;
    f = fopen("database/produtos.bin", "rb");
    tf = fopen("database/produtos.tmp.bin", "wb");
    while (fread(&tmpProduto, sizeof(Produto), 1, f))
        fwrite(&tmpProduto, sizeof(Produto), 1, tf);

    fclose(f);
    fclose(tf);
}

void salvarProduto(Produto produto) {
    FILE *f, *tf;
    Produto tmpProduto;

    if (produto.codigo == 0) {
        produto.codigo = ++produto_autoincremento;
        f = fopen("database/produtos.bin", "ab");
        fwrite(&produto, sizeof(Produto), 1, f);
    } else {
        copiarProdutos();
        f = fopen("database/produtos.bin", "wb");
        tf = fopen("database/produtos.tmp.bin", "rb");
        while(fread(&tmpProduto, sizeof(Produto), 1, tf)) {
            if (tmpProduto.codigo == produto.codigo) {
                fwrite(&produto, sizeof(Produto), 1, f);
            } else {
                fwrite(&tmpProduto, sizeof(Produto), 1, f);
            }
        }
        remove("database/produtos.tmp.bin");
        fclose(tf);
    }

    fclose(f);
}

void listarProdutos() {
    FILE *f;
    f = fopen("database/produtos.bin", "rb");
    char tmp;
    Produto tmpProduto;
    Funcionario tmpFuncionario;
    while (fread(&tmpProduto, sizeof(Produto), 1, f)) {
        tmpFuncionario = buscarFuncionario(tmpProduto.funcionario_codigo);
        printf("Código: %d\nDescrição: %s\n", tmpProduto.codigo, tmpProduto.descricao);
        printf("Unidade de medida: %s\nQuantidade: %d\n", tmpProduto.unidade_medida, tmpProduto.quantidade);
        printf("Quantidade mínima: %d\n", tmpProduto.quantidade_minima);
        printf("Funcionário: %s (ID: %d)\n\n", tmpFuncionario.nome, tmpProduto.funcionario_codigo);
    }
    fclose(f);
}

Produto lerProduto() {
    Produto novoProduto;
    novoProduto.codigo = 0;

    printf("Descrição: ");
    stread(novoProduto.descricao, 41);

    printf("Preço: ");
    scanf("%f", &novoProduto.preco);
    getchar();

    printf("Unidade de Medida: ");
    stread(novoProduto.unidade_medida, 11);

    printf("Data de Entrada: ");
    stread(novoProduto.data_entrada, 11);
    while (!datevalid(novoProduto.data_entrada)) {
        printf("Data inválida (%s). Utilize o formato: dd/mm/aaaa\n", novoProduto.data_entrada);
        printf("Data de Entrada: ");
        stread(novoProduto.data_entrada, 11);
    }

    printf("Quantidade: ");
    scanf("%d", &novoProduto.quantidade);

    printf("Quantidade mínima no estoque: ");
    scanf("%d", &novoProduto.quantidade_minima);

    int i;
    printf("Id do funcionário: ");
    scanf("%d", &i);

    while (!existeFuncionario(i)) {
        printf("Funcionário não encontrado. Insira um código válido:\n");
        printf("Código: ");
        scanf("%d", &i);
    }

    Funcionario funcionario = buscarFuncionario(i);
    int c = 0;
    while (!c) {
        while (!existeFuncionario(i)) {
            printf("Funcionário não encontrado. Insira um código válido:\n");
            printf("Código: ");
            scanf("%d", &i);
        }
        funcionario = buscarFuncionario(i);
        printf("Funcionário: %s\n", funcionario.nome);
        c = confirm("Funcionário correto?");
        i = 0;
    }

    novoProduto.funcionario_codigo = funcionario.codigo;

    return novoProduto;
}

Produto buscarProduto(int codigo) {
    FILE *f;
    f = fopen("database/produtos.bin", "rb");
    Produto tmpProduto;
    while (fread(&tmpProduto, sizeof(Produto), 1, f)) {
        if (tmpProduto.codigo == codigo){
            return tmpProduto;
        }
    }
    fclose(f);
}

Produto removerProduto(int codigo) {
    FILE *tf, *f;
    Produto tmpProduto;
    Produto removido;
    copiarProdutos();
    f = fopen("database/produtos.bin", "wb");
    tf = fopen("database/produtos.tmp.bin", "rb");
    while (fread(&tmpProduto, sizeof(Produto), 1, tf)) {
        if (tmpProduto.codigo != codigo)
            fwrite(&tmpProduto, sizeof(Produto), 1, f);
        else
            removido = tmpProduto;
    }

    remove("database/produtos.tmp.bin");
    fclose(f);
    fclose(tf);

    return removido;
}
