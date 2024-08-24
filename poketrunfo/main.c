#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defines
#define NAMES 50

// estruturas
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
    // variaveis
    Lista2* lista = NULL;

    // abre o arquivo e preenche a lista
    lista = openarq();

    // busca pokemon na pokedex
    busca_pokedex(lista);

    return 0;
}

Lista2* openarq() {
    FILE *arq = fopen("/Meus Projetos/Trabalho Final AED1/trabalhoaedv3/poketrunfo/pokemon.csv", "rt");

    if (arq == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return NULL;
    } 
    printf("Arquivo lido com sucesso!\n");

    char linha[500]; // tamanho máximo de cada linha
    Lista2* lista = NULL;

    // Ler linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arq)) {
        Pokedex p; // Estrutura para armazenar dados do Pokémon
        char* token = strtok(linha, ",");

        p.num_Pokedex = atoi(token);

        token = strtok(NULL, ",");
        strncpy(p.name, token, NAMES);

        token = strtok(NULL, ",");
        strncpy(p.type1, token, NAMES);

        token = strtok(NULL, ",");
        strncpy(p.type2, token, NAMES);

        token = strtok(NULL, ",");
        p.all = atoi(token);

        token = strtok(NULL, ",");
        p.hp = atoi(token);

        token = strtok(NULL, ",");
        p.atk = atoi(token);

        token = strtok(NULL, ",");
        p.def = atoi(token);

        token = strtok(NULL, ",");
        p.sp_atk = atoi(token);

        token = strtok(NULL, ",");
        p.sp_def = atoi(token);

        token = strtok(NULL, ",");
        p.speed = atoi(token);

        token = strtok(NULL, ",");
        p.generation = atoi(token);

        token = strtok(NULL, ",");
        strncpy(p.legendary, token, NAMES);

        // Inserir na lista
        lista = insere(lista, p);
    }

    fclose(arq);
    return lista;
}

/* Inserção no início */ // peguei da apostila e so adaptei
Lista2* insere(Lista2* l, Pokedex p) {
    Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return l;
    }
    novo->info = p;
    novo->prox = l;
    novo->ant = NULL;

    /* Verifica se a lista não está vazia */
    if (l != NULL)
        l->ant = novo;
    
    return novo;
}
// nao sei se vou usa porem ta aq
void imprime_Pokedex(Lista2* l) {
    Lista2* p;
    for (p = l; p != NULL; p = p->prox) {
        printf("Pokedex: %d | Name: %s | Type1: %s | Type2: %s | Total: %d | HP: %d | Atk: %d | Def: %d | Sp.Atk: %d | Sp.Def: %d | Speed: %d | Generation: %d | Legendary: %s\n",p->info.num_Pokedex, p->info.name, p->info.type1, p->info.type2, p->info.all, p->info.hp, p->info.atk, p->info.def, p->info.sp_atk, p->info.sp_def, p->info.speed, p->info.generation, p->info.legendary);
}

void busca_pokedex(Lista2* l) {
    // variaveis
    char nomepokemon[NAMES];
    Lista2* p;
    int encontrado = 0;

    printf("Insira o nome do Pokémon que você deseja buscar na Pokédex: ");
    scanf("%s", nomepokemon);

    for (p = l; p != NULL; p = p->prox) {
        if (strcasecmp(p->info.name, nomepokemon) == 0) {
            printf("Pokémon encontrado!\n");
            printf("Pokedex: %d | Name: %s | Type1: %s | Type2: %s | Total: %d | HP: %d | Atk: %d | Def: %d | Sp.Atk: %d | Sp.Def: %d | Speed: %d | Generation: %d | Legendary: %s\n",p->info.num_Pokedex, p->info.name, p->info.type1, p->info.type2, p->info.all, p->info.hp, p->info.atk, p->info.def, p->info.sp_atk, p->info.sp_def, p->info.speed, p->info.generation, p->info.legendary);
            encontrado = 1;
            break;
        }
    } 

    if (!encontrado) {
        printf("Pokémon não encontrado na Pokédex.\n");
    }
}
