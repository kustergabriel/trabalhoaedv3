#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defines
#define NAMES 50

// structs
typedef struct {
    int num_Pokedex;
    char name[NAMES];
    char type1[NAMES];
    char type2[NAMES];
    int all; // total
    int hp;
    int atk;
    int def;
    int sp_atk;
    int sp_def;
    int speed;
    int generation;
    char legendary[NAMES];
} Pokedex;

typedef struct lista2 {
    Pokedex info;
    struct lista2* ant;
    struct lista2* prox;
} Lista2;

// funções
Lista2* openarq(); 
Lista2* insere(Lista2* l, Pokedex p); 
void imprime_Pokedex(Lista2* l); 
void busca_pokedex(Lista2* l);

int main() {
    // variáveis
    Lista2* lista = NULL;

    // abre o arquivo e preenche a lista
    lista = openarq();

    // busca pokemon na pokedex
    busca_pokedex(lista);

    // opcional: imprime a lista para verificar
    //imprime_Pokedex(lista);

    return 0;
}

Lista2* openarq() {
    FILE *arq = fopen("/Meus Projetos/Trabalho Final AED1/trabalhoaedv3/poketrunfo/pokemon.csv", "rt"); // Use o caminho relativo para o arquivo

    if (arq == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return NULL;
    }
    printf("Arquivo lido com sucesso!\n");

    char linha[500]; // Tamanho máximo de cada linha
    Lista2* lista = NULL;

    // Ler linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arq)) {
        Pokedex p; // Estrutura para armazenar dados do Pokémon
        char* token = strtok(linha, ",");

        if (token) {
            p.num_Pokedex = atoi(token);
            //printf("Num: %d\n", p.num_Pokedex); // Depuração

            token = strtok(NULL, ",");
            if (token) {
                strncpy(p.name, token, NAMES - 1);
                p.name[NAMES - 1] = '\0'; // Garantir string terminada
                //printf("Name: %s\n", p.name); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                strncpy(p.type1, token, NAMES - 1);
                p.type1[NAMES - 1] = '\0'; // Garantir string terminada
                //printf("Type1: %s\n", p.type1); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                strncpy(p.type2, token, NAMES - 1);
                p.type2[NAMES - 1] = '\0'; // Garantir string terminada
                //printf("Type2: %s\n", p.type2); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.all = atoi(token);
                //printf("Total: %d\n", p.all); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.hp = atoi(token);
                //printf("HP: %d\n", p.hp); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.atk = atoi(token);
                //printf("Atk: %d\n", p.atk); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.def = atoi(token);
                //printf("Def: %d\n", p.def); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.sp_atk = atoi(token);
                //printf("Sp.Atk: %d\n", p.sp_atk); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.sp_def = atoi(token);
                //printf("Sp.Def: %d\n", p.sp_def); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.speed = atoi(token);
                //printf("Speed: %d\n", p.speed); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                p.generation = atoi(token);
                //printf("Generation: %d\n", p.generation); // Depuração
            }

            token = strtok(NULL, ",");
            if (token) {
                strncpy(p.legendary, token, NAMES - 1);
                p.legendary[NAMES - 1] = '\0'; // Garantir string terminada
                //printf("Legendary: %s\n", p.legendary); // Depuração
            }

            // Inserir na lista
            lista = insere(lista, p);
        } else {
            printf("Linha inválida: %s\n", linha); // Mensagem de depuração
        }
    }

    fclose(arq);
    return lista;
}

/* inserção no início */
Lista2* insere(Lista2* l, Pokedex p) {
    Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        exit(1); // Saia se não conseguir alocar memória
    }
    novo->info = p;
    novo->prox = l;
    novo->ant = NULL;
    
    // Verifica se lista não está vazia
    if (l != NULL) {
        l->ant = novo;
    }
    return novo;
}

// Imprime a lista de Pokémon
void imprime_Pokedex(Lista2* l) {
    Lista2* p;
    for (p = l; p != NULL; p = p->prox) {
        printf("Num: %d, Name: %s, Type1: %s, Type2: %s, Total: %d, HP: %d, Atk: %d, Def: %d, Sp.Atk: %d, Sp.Def: %d, Speed: %d, Generation: %d, Legendary: %s\n",
            p->info.num_Pokedex, p->info.name, p->info.type1, p->info.type2, p->info.all, p->info.hp, p->info.atk, p->info.def, p->info.sp_atk, p->info.sp_def, p->info.speed, p->info.generation, p->info.legendary);
    }
}

void busca_pokedex(Lista2* l) {
    // variáveis
    char nomepokemon[30];
    Lista2* p;
    int encontrado = 0;

    printf("Insira o nome que voce deseja buscar na pokedex!\n");
    scanf("%s", nomepokemon);

    for (p = l; p != NULL; p = p->prox) {
        if (strcasecmp(p->info.name, nomepokemon) == 0) {
            printf("Pokemon encontrado!\n");
            printf("Num: %d, Name: %s, Type1: %s, Type2: %s, Total: %d, HP: %d, Atk: %d, Def: %d, Sp.Atk: %d, Sp.Def: %d, Speed: %d, Generation: %d, Legendary: %s",
                p->info.num_Pokedex, p->info.name, p->info.type1, p->info.type2, p->info.all, p->info.hp, p->info.atk, p->info.def, p->info.sp_atk, p->info.sp_def, p->info.speed, p->info.generation, p->info.legendary);
            encontrado = 1;
            return;
        }
    }
    if (!encontrado) {
        printf("Pokemon nao encontrado na pokedex.\n");
    }
}
