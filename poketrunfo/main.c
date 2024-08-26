#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// defines
#define NAMES 50
#define MAX 50
#define NUM_VALORES 10

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

//  lista
typedef struct lista2 {
    Pokedex info;
    struct lista2* ant;
    struct lista2* prox;
} Lista2;

// fila
typedef struct elem {
    Pokedex* pokemon;
    struct elem* prox;
} ElemFila;

typedef struct fila {
    ElemFila* ini;
    ElemFila* fim;
} Fila;

// funções
Lista2* openarq(); 
Lista2* insere(Lista2* l, Pokedex p); 
void imprime_Pokedex(Lista2* l); 
void busca_pokedex(Lista2* l);
void geravalores(int valores[]);
void liberar_lista(Lista2* l);
void libera_fila(Fila* f);
Fila* cria_fila();
void insere_fila(Fila* f, Pokedex* pokemon);
Pokedex* remove_fila(Fila* f);
int fila_vazia(Fila* f);
void imprime_fila(Fila* f);
void EmbaralhaEInsere(Lista2* lista, Fila* f, int valores[]);
void transferefilaParaFilas(Fila* fila, Lista2 *lista, Fila* jog1, Fila* jog2);
void batalhaaaaa(Lista2 *l, Fila *jog1, Fila *jog2);

int main() {
    // variáveis
    Lista2* lista = NULL;
    Fila* fila = cria_fila();
    int valores[NUM_VALORES];
    Fila* filajog1 = cria_fila();
    Fila* filajog2 = cria_fila();

    // abre o arquivo e preenche a lista
    lista = openarq();

    // busca pokemon na pokedex
    //busca_pokedex(lista);

    // inserindo os pokemons para a fila
    EmbaralhaEInsere(lista, fila, valores);

    // transferindo para as filas dos jogadores
    transferefilaParaFilas(fila, lista, filajog1, filajog2);
    printf("BEM VINDO(A) AO POKETRUNFO\n");
    printf("Batalha iniciada\n");

    batalhaaaaa(lista, filajog1, filajog2);

    liberar_lista(lista);
    libera_fila(fila);
    libera_fila(filajog1);
    libera_fila(filajog2);

    return 0;
}

Lista2* openarq() {
    FILE *arq = fopen("/Users/Gabriel Azevedo/Documents/GitHub/trabalhoaedv3/poketrunfo/pokemon.csv", "rt"); // Use o caminho relativo para o arquivo

    if (arq == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return NULL;
    }
    printf("Arquivo lido com sucesso!\n");

    char linha[500]; // tamanho máximo de cada linha
    Lista2* lista = NULL;

    // lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arq)) {
        Pokedex p; // Estrutura para armazenar dados do Pokémon
        char* token = strtok(linha, ",");

        if (token) {
            p.num_Pokedex = atoi(token);

            token = strtok(NULL, ",");
            if (token) {
                strncpy(p.name, token, NAMES - 1);
                p.name[NAMES - 1] = '\0'; // Garantir string terminada
            }

            token = strtok(NULL, ",");
            if (token) {
                strncpy(p.type1, token, NAMES - 1);
                p.type1[NAMES - 1] = '\0'; // Garantir string terminada
            }

            token = strtok(NULL, ",");
            if (token && strlen(token) > 0) { // Verifica se o campo type2 não está vazio
                strncpy(p.type2, token, NAMES - 1);
                p.type2[NAMES - 1] = '\0'; // Garantir string terminada
            } else {
                p.type2[0] = '\0'; // Define type2 como string vazia se o campo não for encontrado
            }

            token = strtok(NULL, ",");
            if (token) {
                p.all = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                p.hp = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                p.atk = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                p.def = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                p.sp_atk = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                p.sp_def = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                p.speed = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                p.generation = atoi(token);
            }

            token = strtok(NULL, ",");
            if (token) {
                strncpy(p.legendary, token, NAMES - 1);
                p.legendary[NAMES - 1] = '\0'; // Garantir string terminada
            }

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
        exit(1); 
    }
    novo->info = p;
    novo->prox = l;
    novo->ant = NULL;
    
    if (l != NULL) {
        l->ant = novo;
    }
    return novo;
}

void imprime_Pokedex(Lista2* l) {
    Lista2* p;
    for (p = l; p != NULL; p = p->prox) {
        printf("Num: %d, Name: %s, Type1: %s, Type2: %s, Total: %d, HP: %d, Atk: %d, Def: %d, Sp.Atk: %d, Sp.Def: %d, Speed: %d, Generation: %d, Legendary: %s\n",
            p->info.num_Pokedex, p->info.name, p->info.type1, p->info.type2, p->info.all, p->info.hp, p->info.atk, p->info.def, p->info.sp_atk, p->info.sp_def, p->info.speed, p->info.generation, p->info.legendary);
    }
}

void busca_pokedex(Lista2* l) {
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

// gera indices para as cartas aleatorios
void geravalores(int valores[]) {
    srand(time(NULL));  
    for (int i = 0; i < NUM_VALORES; i++) {
        valores[i] = rand() % 802;  // Gera um número aleatório entre 0 e 801
    }
}

// pega os valores e verifica quais sao os pokemons do arquivo
void EmbaralhaEInsere(Lista2* lista, Fila* f, int valores[]) {
    geravalores(valores);
    Lista2* p = lista;
    int inseridos = 0;

    while (p != NULL && inseridos < NUM_VALORES) {
        for (int i = 0; i < NUM_VALORES; i++) {
            if (p->info.num_Pokedex == valores[i]) {
                insere_fila(f, &p->info);
                inseridos++;
                break;
            }
        }
        p = p->prox;
    }
}

// criação da fila
Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

// insere no fim da fila
void insere_fila(Fila* f, Pokedex* pokemon) {
    ElemFila* novo = (ElemFila*) malloc(sizeof(ElemFila));
    novo->pokemon = pokemon;
    novo->prox = NULL;
    
    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->ini = novo;
    }
    f->fim = novo;
}

// remove do inicio da fila
Pokedex* remove_fila(Fila* f) {
    if (f->ini == NULL) {
        return NULL;
    }

    ElemFila* t = f->ini;
    Pokedex* pokemon = t->pokemon;
    f->ini = t->prox;
    
    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(t);
    return pokemon;
}

// verifica se a fila está vazia
int fila_vazia(Fila* f) {
    return (f->ini == NULL);
}

// libera fila
void libera_fila(Fila* f) {
    ElemFila* q = f->ini;
    while (q != NULL) {
        ElemFila* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}

// imprime os pokemons da fila
void imprime_fila(Fila* f) {
    ElemFila* q = f->ini;
    while (q != NULL) {
        printf("Num: %d, Name: %s\n", q->pokemon->num_Pokedex, q->pokemon->name);
        q = q->prox;
    }
}

// transfere pokemons da fila para os jogadores
void transferefilaParaFilas(Fila* fila, Lista2 *lista, Fila* jog1, Fila* jog2) {
    int contador = 0;
    Pokedex* p;
    while ((p = remove_fila(fila)) != NULL) {
        if (contador % 2 == 0) {
            insere_fila(jog1, p);
        } else {
            insere_fila(jog2, p);
        }
        contador++;
    }
}

// parte da batalha
void batalhaaaaa(Lista2 *l, Fila *jog1, Fila *jog2) {
    int atributo = 0;
    Pokedex* pkm_jogador1 = NULL;
    Pokedex* pkm_jogador2 = NULL;
    int valorAtributo1 = 0, valorAtributo2 = 0;
    int rodadas = 1;

    while (!fila_vazia(jog1) && !fila_vazia(jog2)) {
        printf("Round %d\n", rodadas);

        pkm_jogador1 = remove_fila(jog1);
        pkm_jogador2 = remove_fila(jog2);

        // Escolher atributo aleatório
        atributo = rand() % 6;

        switch (atributo) {
            case 0:
                valorAtributo1 = pkm_jogador1->atk;
                valorAtributo2 = pkm_jogador2->atk;
                printf("Comparando ATK\n");
                break;
            case 1:
                valorAtributo1 = pkm_jogador1->def;
                valorAtributo2 = pkm_jogador2->def;
                printf("Comparando DEF\n");
                break;
            case 2:
                valorAtributo1 = pkm_jogador1->hp;
                valorAtributo2 = pkm_jogador2->hp;
                printf("Comparando HP\n");
                break;
            case 3:
                valorAtributo1 = pkm_jogador1->sp_atk;
                valorAtributo2 = pkm_jogador2->sp_atk;
                printf("Comparando SP_ATK\n");
                break;
            case 4:
                valorAtributo1 = pkm_jogador1->sp_def;
                valorAtributo2 = pkm_jogador2->sp_def;
                printf("Comparando SP_DEF\n");
                break;
            case 5:
                valorAtributo1 = pkm_jogador1->speed;
                valorAtributo2 = pkm_jogador2->speed;
                printf("Comparando SPEED\n");
                break;
        }

        // Determinar o vencedor
        if (valorAtributo1 > valorAtributo2) {
            printf("Jogador 1 venceu a rodada!\n");
            insere_fila(jog1, pkm_jogador1);
            insere_fila(jog1, pkm_jogador2);
        } else if (valorAtributo1 < valorAtributo2) {
            printf("Jogador 2 venceu a rodada!\n");
            insere_fila(jog2, pkm_jogador1);
            insere_fila(jog2, pkm_jogador2);
        } else {
            printf("Empate na rodada! Ambos os pokemons retornam à fila de seus jogadores.\n");
            insere_fila(jog1, pkm_jogador1);
            insere_fila(jog2, pkm_jogador2);
        }

        rodadas++;
    }

    // Verificar quem é o vencedor
    if (fila_vazia(jog1)) {
        printf("Jogador 2 venceu a batalha!\n");
    } else if (fila_vazia(jog2)) {
        printf("Jogador 1 venceu a batalha!\n");
    }
}
