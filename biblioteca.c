#include <stdio.h>
#include <string.h>

typedef struct {
    char titulo[50];
    char review[200];
    float nota;
} Anime;

int VerificaNota(float x);

void AdicionaAnime() {
    Anime x;
    FILE *file = fopen("biblioteca.dat", "ab");

    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    do {
        printf("Digite o nome do anime: ");
        fgets(x.titulo, sizeof(x.titulo), stdin);
        strtok(x.titulo, "\n");
    } while (strlen(x.titulo) == 0);

    do {
        printf("Digite a nota do anime (0 a 10): ");
        scanf("%f", &x.nota);
        getchar();

        if(VerificaNota(x.nota) ==  0) {
            printf("Nota invalida, por favor digite novamente!\n");
        }

    } while (VerificaNota(x.nota) == 0);

    printf("Digite a review do anime: ");
    fgets(x.review, sizeof(x.review), stdin);
    strtok(x.review, "\n");

    fwrite(&x, sizeof(Anime), 1, file);
    fclose(file);
    printf("Anime adicionado com sucesso!\n");
    printf("---------------------------------\n");
}

void MostraAnime() {
    Anime x;
    FILE *file = fopen("biblioteca.dat", "rb");

    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&x, sizeof(Anime), 1, file) == 1) {
        printf("Título: %s\n", x.titulo);
        printf("Nota: %.2f\n", x.nota);
        printf("Review: %s\n", x.review);
        printf("---------------------------------\n");
    }

    fclose(file);
}

void RetiraAnime() {
    Anime x;
    char titulo[50];
    int resultado = 0;

    FILE *file = fopen("biblioteca.dat", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\n------- Lista de Animes -------\n");

    while (fread(&x, sizeof(Anime), 1, file) == 1) {
        printf("Titulo: %s\n",x.titulo);
    }
    printf("---------------------------------\n");
    rewind(file);

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        printf("Erro ao criar o arquivo temporário.\n");
        return;
    }

    printf("Digite o titulo que deseja remover: ");
    fgets(titulo, sizeof(titulo), stdin);
    strtok(titulo, "\n");

    while (fread(&x, sizeof(Anime), 1, file) == 1) {
        if(strcmp(x.titulo, titulo) != 0) {
            fwrite(&x, sizeof(Anime), 1, temp);
        } else {
            resultado = 1;
        }
    }

    if (resultado) {
    printf("Anime removido com sucesso!\n");
    printf("---------------------------------\n");
    } else {
        printf("Anime não encontrado.\n");
        printf("---------------------------------\n");
    }

    fclose(file);
    fclose(temp);

    remove("biblioteca.dat");
    rename("temp.dat", "biblioteca.dat");
}

void QuantidadeAnime() {
    Anime x;
    int i = 0;
    FILE *file = fopen("biblioteca.dat", "rb");

    while (fread(&x, sizeof(Anime), 1, file) == 1) {
        i++;
    }

    printf("---------------------------------\n");
    printf("Total de animes: %d\n", i);
    printf("---------------------------------\n");
    
    fclose(file);
}

int main() {
    int resposta;

    printf("        Seja bem-vindo!\n"        );
    printf("---------------------------------\n");

    do {   
        printf("Digite 1 para adicionar um anime.\n" );
        printf("Digite 2 para remover um anime.\n");
        printf("Digite 3 para listar os animes.\n");
        printf("Digite 4 para mostrar o total de animes.\n");
        printf("      Digite 5 para sair.\n"      );
        printf("---------------------------------\n");
        scanf("%d", &resposta);
        getchar();

        switch(resposta) {
            case 1:
            AdicionaAnime();
            break;

            case 2:
            RetiraAnime();
            break;

            case 3:
            MostraAnime();
            break;

            case 4:
            QuantidadeAnime();
            break;

            case 5:
            printf("Ate a proxima!");
            break;

            default:
            printf("Opcao nao identificada, tente novamente!\n");
            printf("---------------------------------\n");
            break;
        }

    } while(resposta != 5);

    return 0;
}

int VerificaNota(float x) {
    if(x >= 0 && x <= 10) {
        return 1;
    } else {
        return 0;
    }
}
