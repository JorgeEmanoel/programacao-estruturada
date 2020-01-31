int venda_autoincremento = 0;

typedef struct {
    int codigo;
    int quantidade;
    char data[11];
    float preco;
    int funcionario_codigo;
    int produto_codigo;
} Venda;


void cadastrarVenda();
void salvarVenda(Venda venda);
void listarVendas();
void copiarVendas();
int existeVenda(int codigo);
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

void cadastrarVenda() {
    printf("Cadastro de venda:\n");
    getchar();

    Venda venda = lerVenda();
    salvarVenda(venda);
    printf("Venda salvo com sucesso.");

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
    printf("=================== Lista de vendas cadastrados ==================\n\n");
    FILE *f;
    f = fopen("database/vendas.bin", "rb");
    char tmp;
    Venda tmpVenda;
    while (fread(&tmpVenda, sizeof(Venda), 1, f)) {
        printf("Código: %d\n", tmpVenda.codigo);
        printf("Data: %s\n", tmpVenda.data);
        printf("Preço: %.2f\n", tmpVenda.preco);
        printf("Quantidade: %d\n", tmpVenda.quantidade);
        printf("Valor total: %.2f\n", tmpVenda.quantidade * tmpVenda.quantidade);
    }
    printf("====================================================================\n\n");
    fclose(f);
}

Venda lerVenda() {
    Venda novoVenda;
    novoVenda.codigo = 0;

    printf("Data: ");
    stread(novoVenda.data, 11);

    printf("Código do produto: ");
    scanf("%d", &novoVenda.produto_codigo);

    printf("Preço (%.2f): ", 0);
    scanf("%d", &novoVenda.preco);

    printf("Código do funcionario: ");
    scanf("%d", &novoVenda.funcionario_codigo);

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
