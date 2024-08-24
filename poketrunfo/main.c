#include <stdio.h>
#include <string.h>
//#,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,

//defines
#define NAMES 50

//structs
typedef struct  {
    int num_Pokedex;
    char name[NAMES];
    char type1[NAMES];
    char type2[NAMES];
    int all; //total
    int hp;
    int atk;
    int def;
    int sp_atk;
    int sp_def;
}Pokedex;

typedef struct lista2 {
    Pokedex info;
    struct lista2* ant;
    struct lista2* prox;
}Lista2;


// funcoes
Lista2* openarq (); 
Lista2* insere(Lista2* l, Pokedex p); // e esta inserindo tudo na lista duplamente encadeada!
void imprime_Pokedex (Lista2* l); // ok pokedex funcionando!
void busca_pokedex (Lista2* l); // ok busca pokedex funcionando!


int main () {
    //variaveis
    Lista2* lista = NULL;

    //abre o arquivo e preenche a lista
    lista = openarq();

    // busca pokemon na pokedex
    busca_pokedex (lista);


    return 0;
}


Lista2* openarq () {
   FILE *arq = fopen("/Meus Projetos/Trabalho Final AED1/trabalhoaedv3/poketrunfo/pokemon.csv", "rt");

    if (arq == NULL){
    printf("Problemas na abertura do arquivo!\n");
    return;
} printf ("Arquivo lido com sucesso!\n");

    char linha[500]; // tam maximo de cada linha
    Lista2* lista = NULL;

    // ler linha por linha do arquivo
    while (fgets(linha,sizeof(linha), arq)) {
        Pokedex p; // p sao os pokemons
        char* token = strtok (linha, ",");

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

        // Inserir na lista
        lista = insere(lista, p);
    }

    fclose(arq);
    return lista;
    }

/* inserção no início */
Lista2* insere (Lista2* l, Pokedex p){
    Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
    novo->info = p;
    novo->prox = l;
    novo->ant = NULL;
 /* verifica se lista não está vazia */
    if (l != NULL)
        l->ant = novo;
return novo;
}

// nao sei se vai ser usada porem ta aqui
void imprime_Pokedex (Lista2* l) {
    Lista2 *p;
    for (p = l; p != NULL; p = p->prox) {
        printf("Num: %d, Name: %s, Type1: %s, Type2: %s, Total: %d, HP: %d\n",p->info.num_Pokedex, p->info.name, p->info.type1, p->info.type2, p->info.all,p->info.hp);
    }
}

void busca_pokedex (Lista2* l) {
    // var
    char nomepokemon[30];
    Lista2* p;
    int encontrado = 0;

    printf ("Insira o nome que voce deseja buscar na pokedex!\n");
    scanf ("%s", nomepokemon);
    
    for (p=l; p!=NULL; p=p->prox) {
        if (strcasecmp(p->info.name,nomepokemon) == 0) {
        printf("Pokemon encontrado!\n");
        printf("Name: %s",p->info.name);
        encontrado = 1;
        return 1;
        }
    } 
    if (!encontrado) {
        printf("Pokemon nao encontrado na pokedex.\n");
}
}
