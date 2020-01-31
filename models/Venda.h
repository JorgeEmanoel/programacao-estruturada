int venda_autoincremento = 0;

typedef struct {
    int codigo;
    int quantidade;
    char data[10];
    float preco;
    int funcionario_codigo;
    int produto_codigo;
    char motivo[200];
} Venda;


void salvarVenda(Venda venda);
void listarVendas();
void copiarVendas();
int existeVenda(int codigo);
int contarVendas();
int contarVendasFuncionario(int codigo);
int contarVendasProduto(int codigo);
Venda lerVenda();
Venda buscarVenda();
Venda removerVenda();

int contarVendas() {
    FILE *f;
    Venda tmpVenda;
    f = fopen("database/vendas.bin", "rb");
    int qtd = 0;
    if (!f) {
        return 0;
    }
    while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
        qtd++;
    }
    fclose(f);
    return qtd;
}

int contarVendasFuncionario(int codigo) {
    FILE *f;
    Venda tmpVenda;
    f = fopen("database/vendas.bin", "rb");
    int qtd = 0;
    if (!f) {
        return 0;
    }
    while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
        if (tmpVenda.funcionario_codigo == codigo)
            qtd++;
    }
    fclose(f);
    return qtd;
}

int contarVendasProduto(int codigo) {
    FILE *f;
    Venda tmpVenda;
    f = fopen("database/vendas.bin", "rb");
    int qtd = 0;
    if (!f) {
        return 0;
    }
    while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
        if (tmpVenda.produto_codigo == codigo)
            qtd++;
    }
    fclose(f);
    return qtd;
}

int existeVenda(int codigo) {

    if (!contarVendas()) {
        return 0;
    }

    FILE *f;
    Venda tmpVenda;
    f = fopen("database/vendas.bin", "rb");
    while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
        if (codigo == tmpVenda.codigo) {
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void copiarVendas() {
    FILE *tf, *f;
    Venda tmpVenda;
    f = fopen("database/vendas.bin", "rb");
    tf = fopen("database/vendas.tmp.bin", "wb");
    while (fread(&tmpVenda, sizeof(Venda), 1, f))
        fwrite(&tmpVenda, sizeof(Venda), 1, tf);

    fclose(f);
    fclose(tf);
}

void salvarVenda(Venda venda) {
    FILE *f, *tf;
    Venda tmpVenda;

    if (venda.codigo == 0) {
        venda.codigo = ++venda_autoincremento;
        f = fopen("database/vendas.bin", "ab");
        fwrite(&venda, sizeof(Venda), 1, f);
    } else {
        copiarVendas();
        f = fopen("database/vendas.bin", "wb");
        tf = fopen("database/vendas.tmp.bin", "rb");
        while(fread(&tmpVenda, sizeof(Venda), 1, tf)) {
            if (tmpVenda.codigo == venda.codigo) {
                fwrite(&venda, sizeof(Venda), 1, f);
            } else {
                fwrite(&tmpVenda, sizeof(Venda), 1, f);
            }
        }
        remove("database/vendas.tmp.bin");
        fclose(tf);
    }

    fclose(f);
}

void listarVendas() {
    FILE *f;
    f = fopen("database/vendas.bin", "rb");
    char tmp;
    Venda tmpVenda;
    while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
        Funcionario funcionario = buscarFuncionario(tmpVenda.funcionario_codigo);
        printf("Código: %d\n", tmpVenda.codigo);
        printf("Data: %s\n", tmpVenda.data);
        printf("Preço: %.2f\n", tmpVenda.preco);
        printf("Quantidade: %d\n", tmpVenda.quantidade);
        printf("Valor total: %.2f\n", tmpVenda.quantidade * tmpVenda.preco);
        printf("Funcionário: %s (ID: %d)\n\n", funcionario.nome, tmpVenda.funcionario_codigo);
    }
    fclose(f);
}

void salvarVendaNegativa(Venda venda) {
    FILE *f;
    strcpy(venda.motivo, "Sem estoque");
    f = fopen("database/vendas-erradas.bin", "ab");
    fwrite(&venda, sizeof(Venda), 1, f);
    fclose(f);
}

void salvarVendaSemEstoque(Venda venda) {
    FILE *f;
    strcpy(venda.motivo, "Quantidade mínima atingida");
    f = fopen("database/vendas-erradas.bin", "ab");
    fwrite(&venda, sizeof(Venda), 1, f);
    fclose(f);
}

Venda lerVenda() {
    Venda novoVenda;
    novoVenda.codigo = 0;

    printf("Data (dd/mm/aaaa): ");
    stread(novoVenda.data, 11);
    while (!datevalid(novoVenda.data)) {
        printf("Data inválida (%s). Utilize o formato: dd/mm/aaaa\n", novoVenda.data);
        printf("Data da venda: ");
        stread(novoVenda.data, 11);
    }

    int i = 0;
    printf("Código do produto: ");
    scanf("%d", &i);

    while (!existeProduto(i)) {
        printf("Produto não encontrado. Insira um código válido:\n");
        printf("Código do produto: ");
        scanf("%d", &i);
    }

    Produto produto = buscarProduto(i);
    printf("Produto: %s\n", produto.descricao);
    int c = confirm("Produto correto?");
    while (!c) {
        printf("Código do produto: ");
        scanf("%d", &i);

        while (!existeProduto(i)) {
            printf("Produto não encontrado. Insira um código válido:\n");
            printf("Código do produto: ");
            scanf("%d", &i);
        }
        produto = buscarProduto(i);
        printf("Produto: %s\n", produto.descricao);
        c = confirm("Funcionário correto?");
        i = 0;
    }

    novoVenda.produto_codigo = produto.codigo;

    printf("Preço (%.2f): ", produto.preco);
    scanf("%f", &novoVenda.preco);

    printf("Quantidade: ");
    scanf("%d", &novoVenda.quantidade);
    printf("Valor total: %.2f\n", novoVenda.quantidade * novoVenda.preco);

    printf("Código do funcionario: ");
    scanf("%d", &i);

    while (!existeFuncionario(i)) {
        printf("Funcionário não encontrado. Insira um código válido:\n");
        printf("Código do funcionario: ");
        scanf("%d", &i);
    }

    Funcionario funcionario = buscarFuncionario(i);
    printf("Funcionário: %s\n", funcionario.nome);
    c = confirm("Funcionário correto?");
    while (!c) {
        printf("Código do funcionario: ");
        scanf("%d", &i);

        while (!existeFuncionario(i)) {
            printf("Funcionário não encontrado. Insira um código válido:\n");
            printf("Código do funcionario: ");
            scanf("%d", &i);
        }
        funcionario = buscarFuncionario(i);
        printf("Funcionário: %s\n", funcionario.nome);
        c = confirm("Funcionário correto?");
        i = 0;
    }

    novoVenda.funcionario_codigo = funcionario.codigo;

    return novoVenda;
}

Venda buscarVenda(int codigo) {
    FILE *f;
    f = fopen("database/vendas.bin", "rb");
    Venda tmpVenda;
    while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
        if (tmpVenda.codigo == codigo){
            return tmpVenda;
        }
    }
}

Venda removerVenda(int codigo) {
    FILE *tf, *f;
    Venda tmpVenda;
    Venda removido;
    copiarVendas();
    f = fopen("database/vendas.bin", "wb");
    tf = fopen("database/vendas.tmp.bin", "rb");
    while (fread(&tmpVenda, sizeof(Venda), 1, tf)) {
        if (tmpVenda.codigo != codigo)
            fwrite(&tmpVenda, sizeof(Venda), 1, f);
        else
            removido = tmpVenda;
    }

    remove("database/vendas.tmp.bin");
    fclose(f);
    fclose(tf);

    return removido;
}
