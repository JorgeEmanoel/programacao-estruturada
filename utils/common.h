void breadcrumb(char *str) {
    system("clear");
    printf("--------------------------------------------------------------------\n");
    printf("| %s", str);
    printf("\n--------------------------------------------------------------------\n\n");
}

void wait() {
    getchar();
    printf("Pressione ENTER para continuar\n");
    getchar();
}

int confirm(char *str) {
    getchar();
    printf("[CONFIRMAÇÃO] %s (s/N): ", str);
    char c = getchar();
    if (c != 'n') {
        return 1;
    } else {
        return 0;
    }
}

int datevalid(char *str) {
    if (strlen(str) != 10)
        return 0;

    if (str[2] != '/' || str[5] != '/')
        return 0;

    int dia = ((str[0] - 48) * 10) + (str[1] - 48);
    int mes = ((str[3] - 48) * 10) + (str[4] - 48);
    int ano = ((str[6] - 48) * 1000) + ((str[7] - 48) * 100) + ((str[8] - 48) * 10) + (str[9] - 48);

    if (dia > 31)
        return 0;

    if (mes > 12)
        return 0;

    return 1;
}

int datetoint(char *str) {
    if (strlen(str) != 10)
        return 0;

    if (str[2] != '/' || str[5] != '/')
        return 0;

    char nstr[8] = {str[6], str[7], str[8], str[9], str[3], str[4], str[0], str[1]};

    int centena = ((nstr[5] - 48) * 100) + ((nstr[6] - 48) * 10) + (nstr[7] - 48);
    int milhar = ((nstr[2] - 48) * 100000) + ((nstr[3] - 48) * 10000) + ((nstr[4] - 48) * 1000);
    int milhao = ((nstr[0] - 48) * 10000000) + ((nstr[1] - 48) * 1000000);

    return milhao + milhar + centena;
}
