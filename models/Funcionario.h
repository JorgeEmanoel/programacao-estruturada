int funcionario_autoincremento = 0;

typedef struct {
    int codigo;
    char nome[30];
    char cargo[30];
    char data_nascimento[10];
    char sexo[1];
    char telefone[11];
} Funcionario;


void cadastrarFuncionario();
void salvarFuncionario(Funcionario funcionario);
void listarFuncionarios();
void copiarFuncionarios();
int existeFuncionario(int codigo);
int contarFuncionarios();
Funcionario lerFuncionario();
Funcionario buscarFuncionario();
Funcionario removerFuncionario();

int existeFuncionario(int codigo) {
    FILE *f;
    Funcionario tmpFuncionario;
    f = fopen("database/funcionarios.bin", "rb");
    while (fread(&tmpFuncionario, sizeof(Funcionario), 1, f)) {
        if (codigo == tmpFuncionario.codigo) {
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int contarFuncionarios() {
    FILE *f;
    Funcionario tmpFuncionario;
    f = fopen("database/funcionarios.bin", "rb");
    int qtd = 0;
    if (!f) {
        return 0;
    }
    while (fread(&tmpFuncionario, sizeof(Funcionario), 1, f)) {
        qtd++;
    }
    fclose(f);
    return qtd;
}

void copiarFuncionarios() {
    FILE *tf, *f;
    Funcionario tmpFuncionario;
    f = fopen("database/funcionarios.bin", "rb");
    tf = fopen("database/funcionarios.tmp.bin", "wb");
    while (fread(&tmpFuncionario, sizeof(Funcionario), 1, f))
        fwrite(&tmpFuncionario, sizeof(Funcionario), 1, tf);

    fclose(f);
    fclose(tf);
}

void cadastrarFuncionario() {
    printf("Cadastro de funcionario:\n");
    getchar();

    Funcionario funcionario = lerFuncionario();
    salvarFuncionario(funcionario);
    printf("Funcionario salvo com sucesso.");

}

void salvarFuncionario(Funcionario funcionario) {
    FILE *f, *tf;
    Funcionario tmpFuncionario;

    if (funcionario.codigo == 0) {
        funcionario.codigo = ++funcionario_autoincremento;
        f = fopen("database/funcionarios.bin", "ab");
        fwrite(&funcionario, sizeof(Funcionario), 1, f);
    } else {
        copiarFuncionarios();
        f = fopen("database/funcionarios.bin", "wb");
        tf = fopen("database/funcionarios.tmp.bin", "rb");
        while(fread(&tmpFuncionario, sizeof(Funcionario), 1, tf)) {
            if (tmpFuncionario.codigo == funcionario.codigo) {
                fwrite(&funcionario, sizeof(Funcionario), 1, f);
            } else {
                fwrite(&tmpFuncionario, sizeof(Funcionario), 1, f);
            }
        }
        remove("database/funcionarios.tmp.bin");
        fclose(tf);
    }

    fclose(f);
}

void listarFuncionarios() {
    printf("=================== Lista de funcionarios cadastrados ==================\n\n");
    FILE *f;
    f = fopen("database/funcionarios.bin", "rb");
    char tmp;
    Funcionario tmpFuncionario;
    while (fread(&tmpFuncionario, sizeof(Funcionario), 1, f)) {
        printf("Código: %d\n", tmpFuncionario.codigo);
        printf("Nome: %s\n", tmpFuncionario.nome);
        printf("Cargo: %s\n", tmpFuncionario.cargo);
        printf("Data de Nascimento: %s\n", tmpFuncionario.data_nascimento);
        printf("Telefone: %s\n\n", tmpFuncionario.telefone);
    }
    printf("====================================================================\n\n");
    fclose(f);
}

Funcionario lerFuncionario() {
    Funcionario novoFuncionario;
    novoFuncionario.codigo = 0;

    printf("Nome: ");
    stread(novoFuncionario.nome, 30);

    printf("Cargo: ");
    stread(novoFuncionario.cargo, 30);

    printf("Data de Nascimento: ");
    stread(novoFuncionario.data_nascimento, 10);

    printf("Sexo (M/F): ");
    scanf("%c", novoFuncionario.sexo);
    getchar();

    printf("Telefone (apenas números): ");
    stread(novoFuncionario.telefone, 11);

    return novoFuncionario;
}

Funcionario buscarFuncionario(int codigo) {
    FILE *f;
    f = fopen("database/funcionarios.bin", "rb");
    Funcionario tmpFuncionario;
    while (fread(&tmpFuncionario, sizeof(Funcionario), 1, f)) {
        if (tmpFuncionario.codigo == codigo){
            return tmpFuncionario;
        }
    }
}

Funcionario removerFuncionario(int codigo) {
    FILE *tf, *f;
    Funcionario tmpFuncionario;
    Funcionario removido;
    copiarFuncionarios();
    f = fopen("database/funcionarios.bin", "wb");
    tf = fopen("database/funcionarios.tmp.bin", "rb");
    while (fread(&tmpFuncionario, sizeof(Funcionario), 1, tf)) {
        if (tmpFuncionario.codigo != codigo)
            fwrite(&tmpFuncionario, sizeof(Funcionario), 1, f);
        else
            removido = tmpFuncionario;
    }

    remove("database/funcionarios.tmp.bin");
    fclose(f);
    fclose(tf);

    return removido;
}
