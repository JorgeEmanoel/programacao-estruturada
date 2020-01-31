int produto_autoincremento = 0;

typedef struct {
    int codigo;
    char descricao[30];
    char unidade_medida[10];
    int quantidade;
    int quantidade_minima;
    char data_entrada[10];
    int funcionario_codigo;
} Produto;


void cadastrarProduto();
void salvarProduto(Produto produto);
void listarProdutos();
void copiarProdutos();
int existeProduto(int codigo);
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

void cadastrarProduto() {
    printf("Cadastro de produto:\n");
    getchar();

    Produto produto = lerProduto();
    salvarProduto(produto);
    printf("Produto salvo com sucesso.");

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
    printf("=================== Lista de produtos cadastrados ==================\n\n");
    FILE *f;
    f = fopen("database/produtos.bin", "rb");
    char tmp;
    Produto tmpProduto;
    while (fread(&tmpProduto, sizeof(Produto), 1, f)) {
        printf("Código: %d\nDescrição: %s\n", tmpProduto.codigo, tmpProduto.descricao);
        printf("Unidade de medida: %s\nQuantidade: %d\n", tmpProduto.unidade_medida, tmpProduto.quantidade);
        printf("Quantidade mínima: %d\n\n", tmpProduto.quantidade_minima);
    }
    printf("====================================================================\n\n");
    fclose(f);
}

Produto lerProduto() {
    Produto novoProduto;
    novoProduto.codigo = 0;

    printf("Descrição: ");
    stread(novoProduto.descricao, 40);

    printf("Unidade de Medida: ");
    stread(novoProduto.unidade_medida, 10);

    printf("Data de Entrada: ");
    stread(novoProduto.data_entrada, 10);

    printf("Quantidade: ");
    scanf("%d", &novoProduto.quantidade);

    printf("Quantidade mínima no estoque: ");
    scanf("%d", &novoProduto.quantidade_minima);

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
