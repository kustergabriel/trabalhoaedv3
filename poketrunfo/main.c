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
void imprime_fila(Fila* f);
void EmbaralhaEInsere(Lista2* lista, Fila* f, int valores[]);
void transferefilaParaFilas(Fila* fila, Lista2* lista, Fila* jog1, Fila* jog2);
void imprime_fila_jogador(Fila* f, int fila_num);
int queminiciabatalha(Fila* jog1, Fila* jog2);
void batalhaaaaa(Lista2* l, Fila* jog1, Fila* jog2);
Pokedex* remove_fila(Fila* f);
void insere_fila(Fila* f, Pokedex* pokemon);

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

   // liberar_lista(lista);
    libera_fila(fila);
    libera_fila(filajog1);
    libera_fila(filajog2);

    return 0;
}

Lista2* openarq() {
    FILE *arq = fopen("pokemon.csv", "rt"); // Use o caminho relativo para o arquivo

    if (arq == NULL) {
        printf("Problemas na abertura do arquivo!\n");
        return NULL;
    }
    printf("Arquivo lido com sucesso!\n");

    char linha[500]; // tamanho máximo de cada linha
    Lista2* lista = NULL;

    // le linha por linha do arquivo
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

    // verifica se lista não está vazia
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

// pega os valores e verifica quais sao na pokedex
void EmbaralhaEInsere(Lista2* lista, Fila* f, int valores[]) {
    geravalores(valores);

    for (int i = 0; i < NUM_VALORES; i++) {
        Lista2* p = lista;
        while (p != NULL) {
            if (p->info.num_Pokedex == valores[i]) {
                insere_fila(f, &(p->info));
                break;
            }
            p = p->prox;
        }
    }
}

Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (!f) {
        printf("Erro ao criar fila!\n");
        exit(1);
    }
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void libera_fila(Fila* f) {
    while (f->ini != NULL) {
        ElemFila* t = f->ini;
        f->ini = f->ini->prox;
        free(t);
    }
    free(f);
}

void insere_fila(Fila* f, Pokedex* pokemon) {
    ElemFila* novo = (ElemFila*) malloc(sizeof(ElemFila));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo->pokemon = pokemon;
    novo->prox = NULL;

    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->ini = novo;
    }
    f->fim = novo;
}

Pokedex* remove_fila(Fila* f) {
    if (f->ini == NULL) {
        printf("Fila vazia!\n");
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

// transfere elementos da fila principal para as filas dos jogadores
void transferefilaParaFilas(Fila* fila, Lista2* lista, Fila* jog1, Fila* jog2) {
    int i = 0;
    while (fila->ini != NULL) {
        Pokedex* pkm = remove_fila(fila);
        if (i % 2 == 0) {
            insere_fila(jog1, pkm);
        } else {
            insere_fila(jog2, pkm);
        }
        i++;
    }
}
Pokedex* topo_fila(Fila* f) {
    if (f->ini == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }
    // O ponteiro 'ini' aponta para o primeiro elemento da fila
    return f->ini->pokemon;
}


// imprime a fila
/*void imprime_fila(Fila* f) {
    ElemFila* t = f->ini;
        printf("Nro Pokedex: %d | Nome: %s | Hp: %d | Ataque: %d | Defesa: %d | Ataque Esp: %d | Defesa Esp: %d |\n", t->pokemon->num_Pokedex, t->pokemon->name,t->pokemon->hp,t->pokemon->atk,t->pokemon->def,t->pokemon->sp_atk,t->pokemon->sp_def);
}*/

void imprime_fila(Fila* f) {
    ElemFila* t = f->ini;
        printf("Nro Pokedex: %d \n", t->pokemon->num_Pokedex);
}

void imprime_filatotal(Fila* f) {
    ElemFila* t = f->ini;
    while (t != NULL) {
        printf("Num: %d | ", t->pokemon->num_Pokedex);
        t = t->prox;
    }
}

// função de batalha
void batalhaaaaa(Lista2 *l, Fila *jog1, Fila *jog2) {
    int atributo = 0;
    Pokedex* pkm_jogador1 = NULL;
    Pokedex* pkm_jogador2 = NULL;
    int valorAtributo1 = 0, valorAtributo2 = 0;
    int rodadas = 1;
    int jogadorSorteado;
    int continuar = 0;

    while (jog1->ini != NULL && jog2->ini != NULL) { // loop para continuar até que um jogador tenha a fila vazia
        jogadorSorteado = rand() % 2; // 0 para Jogador 1, 1 para Jogador 2
        printf("Rodada %d\n", rodadas);
        
        if (jogadorSorteado == 0) { // jogador 1
            printf ("Fila jogador 1\n");
            imprime_filatotal(jog1);
            printf("Com qual atributo voce deseja jogar?\n");
            printf("HP (1) | ATAQUE (2) | DEFESA (3) | ATAQUE.SP (4) | DEFESA.SP (5)\n");
            scanf("%d", &atributo);

            pkm_jogador1 = topo_fila(jog1);
            pkm_jogador2 = topo_fila(jog2);
            //imprime_filatotal (jog1);
            // Obtém o valor do atributo escolhido para ambos os jogadores
            switch (atributo) {
                case 1:
                    valorAtributo1 = pkm_jogador1->hp;
                    valorAtributo2 = pkm_jogador2->hp;
                    printf ("Atributo escolhido: HP %d \n", pkm_jogador2->hp);

                    break;
                case 2:
                    valorAtributo1 = pkm_jogador1->atk;
                    valorAtributo2 = pkm_jogador2->atk;
                    printf ("Atributo escolhido: ATK %d \n", pkm_jogador1->atk);
                    break;
                case 3:
                    valorAtributo1 = pkm_jogador1->def;
                    valorAtributo2 = pkm_jogador2->def;
                    printf ("Atributo escolhido: DEF %d \n", pkm_jogador1->def);
                    break;
                case 4:
                    valorAtributo1 = pkm_jogador1->sp_atk;
                    valorAtributo2 = pkm_jogador2->sp_atk;
                    printf ("Atributo escolhido: SP.ATK %d \n", pkm_jogador1->sp_atk);
                    break;
                case 5:
                    valorAtributo1 = pkm_jogador1->sp_def;
                    valorAtributo2 = pkm_jogador2->sp_def;
                    printf ("Atributo escolhido: SP.DEF %d \n", pkm_jogador1->sp_def);
                    break;
                default:
                    printf("Atributo inválido.\n");
                    return;
            }

        } else { // Jogador 2
            imprime_fila(jog2);
            printf("Jogador 2 escolhendo seu atributo...\n");
            //printf ("Atributo escolhido: ");
            pkm_jogador1 = topo_fila(jog1); 
            pkm_jogador2 = topo_fila(jog2);
            // pc escolhe atributo aleatorio
            atributo = rand() % 5 + 1;
            switch (atributo) {
                case 1:
                    valorAtributo1 = pkm_jogador1->hp;
                    valorAtributo2 = pkm_jogador2->hp;
                    printf ("Atributo escolhido: HP %d \n", pkm_jogador2->hp);

                    break;
                case 2:
                    valorAtributo1 = pkm_jogador1->atk;
                    valorAtributo2 = pkm_jogador2->atk;
                    printf ("Atributo escolhido: ATK %d \n", pkm_jogador2->atk);
                    break;
                case 3:
                    valorAtributo1 = pkm_jogador1->def;
                    valorAtributo2 = pkm_jogador2->def;
                    printf ("Atributo escolhido: DEF %d \n", pkm_jogador2->def);
                    break;
                case 4:
                    valorAtributo1 = pkm_jogador1->sp_atk;
                    valorAtributo2 = pkm_jogador2->sp_atk;
                    printf ("Atributo escolhido: SP.ATK %d \n", pkm_jogador2->sp_atk);
                    break;
                case 5:
                    valorAtributo1 = pkm_jogador1->sp_def;
                    valorAtributo2 = pkm_jogador2->sp_def;
                    printf ("Atributo escolhido: SP.DEF %d \n", pkm_jogador2->sp_def);
                    break;
                default:
                    printf("Atributo inválido.\n");
                    return;
            }
        }


        // Determina o vencedor da rodada
        if (valorAtributo1 > valorAtributo2) { // Jogador 1 ganha
            printf("Jogador 1 venceu esta batalha! O Pokemon %s do Jogador 2 passa para o Jogador 1!\n", pkm_jogador2->name);
            insere_fila(jog1, pkm_jogador2); // Adiciona o Pokémon do Jogador 2 na fila do Jogador 1
            remove_fila(jog2);
            imprime_filatotal(jog1); // DEPURACAO
            printf ("Insira 1 para prosseguir...");
            scanf ("%d", &continuar);
            if (continuar == 1) {
                printf("\n\n");
            } else {
                printf ("Jogo encerrado!!");
                return ;
            }
        } else if (valorAtributo2 > valorAtributo1) { // Jogador 2 ganha
            printf("Jogador 2 venceu esta batalha! O Pokemon %s do Jogador 1 passa para o Jogador 2!\n", pkm_jogador1->name);
            insere_fila(jog2, pkm_jogador1); // Adiciona o Pokémon do Jogador 1 na fila do Jogador 2
            remove_fila(jog1);
            imprime_filatotal(jog2); // DEPURACAO
            printf ("Insira 1 para prosseguir...");
            scanf ("%d", &continuar);
            if (continuar == 1) {
                printf("\n\n");
            } else {
                printf ("Jogo encerrado!!");
                return ;
            }
        } else { // Empate
            printf("Empate! Nenhuma carta eh transferida.\n");
            // Os Pokémons vão para o final da fila do mesmo jogador
            insere_fila(jog1, pkm_jogador1);
            insere_fila(jog2, pkm_jogador2);
        }
        rodadas++;
    }

    // Verifica o vencedor final
    if (jog1->ini == NULL) {
        printf("Jogador 2 é o vencedor!!!!\n");
        imprime_fila(jog2);
    } else if (jog2->ini == NULL) {
        printf("Jogador 1 é o vencedor!!!!\n");
        imprime_fila(jog1);
    }
}
