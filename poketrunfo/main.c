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

// pilha
typedef struct elem_pilha {
    Pokedex* pokemon;
    struct elem_pilha* prox;
} ElemPilha;

typedef struct pilha {
    ElemPilha* topo;
} Pilha;



// fila
typedef struct elem{
 float valor;
 struct elem* prox;
}ElemFila;

typedef struct fila{
 ElemFila* ini;
 ElemFila* fim;
}Fila;



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
Pilha* cria_pilha();
void push(Pilha* p, Pokedex* info);
Pokedex* pop(Pilha* p);
int pilha_vazia(Pilha* p);
void libera_pilha(Pilha* p);
void EmbaralhaEInsere(Lista2* lista, Fila* f, int valores[]);
void transferefilaParaPilhas(Fila* fila, Lista2 *lista, Pilha* jog1, Pilha* jog2);
void imprime_pilha(Pilha* p, int pilha_num);
void queminiciabatalha(Pilha* jog1, Pilha* jog2);

int main() {
    // variáveis
    Lista2* lista = NULL;
    Fila* fila = cria_fila();
    int valores[NUM_VALORES];
    Pilha* pilhajog1 = cria_pilha();
    Pilha* pilhajog2 = cria_pilha();
    int *atributo = 0;

    // abre o arquivo e preenche a lista
    lista = openarq();

    // busca pokemon na pokedex
    //busca_pokedex(lista);

    // inserindo os pokemons para a fila
    EmbaralhaEInsere(lista, fila, valores);

    // transferindo para uma pilha a fila
    transferefilaParaPilhas (fila, lista, pilhajog1, pilhajog2);
    printf ("Cartas Jogadores 1 e 2 OK!!!\n");
    printf ("Batalha iniciada\n");
    batalhaaaaa(lista, pilhajog1, pilhajog2);


    liberar_lista(lista);
    libera_fila(fila);

    return 0;
}

Lista2* openarq() {
    FILE *arq = fopen("/Meus Projetos/Trabalho Final AED1/trabalhoaedv3/poketrunfo/pokemon.csv", "rt"); // Use o caminho relativo para o arquivo

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
            if (token && strlen(token) > 0) { // Verifica se o campo type2 não está vazio
                strncpy(p.type2, token, NAMES - 1);
                p.type2[NAMES - 1] = '\0'; // Garantir string terminada
            } else {
                p.type2[0] = '\0'; // Define type2 como string vazia se o campo não for encontrado
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

            lista = insere(lista, p);
        } else {
            printf("Linha inválida: %s\n", linha); // Mensagem de depuração
        }
    }

    fclose(arq);
    return lista;
}

/* inserção no início */ //peguei o codigo da apostila
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

// nao sei se vou usar porem vou deixar aqui
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
    Lista2* p;
    int encontrado;

    for (int i = 0; i < NUM_VALORES; i++) {
        encontrado = 0;
        for (p = lista; p != NULL; p = p->prox) {
            if (p->info.num_Pokedex == valores[i]) {
                // Insere o Pokémon na fila
                ElemFila* novo = (ElemFila*)malloc(sizeof(ElemFila));
                if (!novo) {
                    printf("Erro ao alocar memória para a fila!\n");
                    exit(1);
                }
                novo->valor = valores[i];
                novo->prox = NULL;
                // Insere o novo elemento na fila
                if (f->fim == NULL) {  // Fila vazia
                    f->ini = novo;
                    f->fim = novo;
                } else {
                    f->fim->prox = novo;
                    f->fim = novo;
                }
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("Pokémon com ID %d não encontrado na lista.\n", valores[i]);
        }
    }
}

void transferefilaParaPilhas(Fila* fila, Lista2 *lista, Pilha* jog1, Pilha* jog2) {
    ElemFila* p = fila->ini;
    int metade = 5;
    int count = 0;

    while (p != NULL) {
        Lista2* l = lista;
        Pokedex* pokemon = NULL;

        // Busca o Pokémon na lista com base no número da Pokédex
        while (l != NULL) {
            if (l->info.num_Pokedex == (int)p->valor) {
                pokemon = &(l->info);
                break;
            }
            l = l->prox;
        }

        // Verifica se o Pokémon foi encontrado e o insere na pilha correspondente
        if (pokemon != NULL) {
            if (count < metade) {
                push(jog1, pokemon);
            } else {
                push(jog2, pokemon);
            }

        // Move para o próximo elemento na fila
        p = p->prox;
        count++;
        }
    }
}


void liberar_lista(Lista2* l) {
    Lista2* p = l;
    while (p != NULL) {
        Lista2* temp = p;
        p = p->prox;
        free(temp);
    }
}
// pilhas
Pilha* cria_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}
// ta ai porem nao precisa ser usada eu achooo
void imprime_pilha(Pilha* p, int pilha_num) {
    printf("CARTA NO TOPO DA PILHA %d:\n", pilha_num);
    ElemPilha* atual = p->topo;
    if (atual == NULL) {
        printf("A pilha está vazia.\n");
        return;
    }
        Pokedex* pkm = atual->pokemon;
        printf("Num: %d, Name: %s, Type1: %s, Type2: %s, Total: %d, HP: %d, Atk: %d, Def: %d, Sp.Atk: %d, Sp.Def: %d, Speed: %d, Generation: %d, Legendary: %s",
            pkm->num_Pokedex, pkm->name, pkm->type1, pkm->type2, pkm->all, pkm->hp, pkm->atk, pkm->def, pkm->sp_atk, pkm->sp_def, pkm->speed, pkm->generation, pkm->legendary);
        atual = atual->prox;
    printf("\n");
}

void push(Pilha* p, Pokedex* pokemon) {
    ElemPilha* novo = (ElemPilha*) malloc(sizeof(ElemPilha));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo elemento!\n");
        exit(1);
    }
    novo->pokemon = pokemon;
    novo->prox = p->topo;
    p->topo = novo;
}

Pokedex* pop(Pilha* p) {
    if (p->topo == NULL) {
        printf("Pilha vazia.\n");
        exit(1);
    }
    ElemPilha* temp = p->topo;
    Pokedex* pkm = temp->pokemon;
    p->topo = temp->prox;
    free(temp);
    return pkm;
}


int pilha_vazia(Pilha* p) {
    return p->topo == NULL; // Retorna 1 (true) se a pilha estiver vazia, 0 (false) caso contrário
}

void libera_pilha(Pilha* p) {
    while (p->topo != NULL) {
        ElemPilha* temp = p->topo;
        p->topo = temp->prox;
        free(temp); 
    }
    free(p);
}


// filas
Fila* cria_fila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (!f) {
        printf("Erro ao alocar memória para a fila!\n");
        exit(1);
    }
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void libera_fila(Fila* f) {
    ElemFila* p = f->ini;
    while (p != NULL) {
        ElemFila* temp = p;
        p = p->prox;
        free(temp);
    }
    free(f);
}

void imprime_fila(Fila* f) {
    ElemFila* p = f->ini; 
    if (p == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Pokémons na fila:\n");
    while (p != NULL) {
        printf("%d ", (int)p->valor);  // pega o id do pokemon
        p = p->prox;  // vai pro próximo
    }
    printf("\n");
}

// parte da batalha

void queminiciabatalha(Pilha* jog1, Pilha* jog2) {
    srand(time(NULL));  
    int jogador = rand() % 2; // Gera 0 ou 1

    printf("Quem vai iniciar a batalha: Jogador %d\n", jogador + 1); // Ajusta para 1 ou 2

    // Imprime a carta do topo da pilha do jogador escolhido
    if (jogador == 0) {
        imprime_pilha(jog1, jogador + 1); // Imprime a pilha do jogador 1
    } else {
        imprime_pilha(jog2, jogador + 1); // Imprime a pilha do jogador 2
    }
}

void batalhaaaaa(Lista2 *l, Pilha *jog1, Pilha *jog2) {
    int atributo = 0;
    queminiciabatalha(jog1, jog2); // Escolhe e imprime quem começa a batalha

    printf("Com qual atributo voce deseja jogar?\n");
    printf("HP (1) | ATAQUE (2) | DEFESA (3) | ATAQUE.SP (4) | DEFESA.SP (5)\n");
    scanf("%d", &atributo);

    Pokedex* pkm_jogador;
    if (!pilha_vazia(jog1)) {
        pkm_jogador = pop(jog1); // Remove o Pokémon do topo da pilha (ou use o topo diretamente)
    } else {
        printf("A pilha do jogador está vazia.\n");
        return;
    }
    switch (atributo) {
        case 1:
            printf("Voce escolheu o HP %d do seu Pokemon %s\n", pkm_jogador->hp, pkm_jogador->name);
            break;
        case 2:
            printf("Voce escolheu o ATAQUE %d do seu Pokemon %s\n", pkm_jogador->atk, pkm_jogador->name);
            break;
        case 3:
            printf("Voce escolheu a DEFESA %d do seu Pokemon %s\n", pkm_jogador->def, pkm_jogador->name);
            break;
        case 4:
            printf("Voce escolheu o ATAQUE.SP %d do seu Pokemon %s\n", pkm_jogador->sp_atk, pkm_jogador->name);
            break;
        case 5:
            printf("Voce escolheu a DEFESA.SP %d do seu Pokemon %s\n", pkm_jogador->sp_def, pkm_jogador->name);
            break;
        default:
            printf("Atributo inválido.\n");
            break;
    }

    // Recoloca o Pokémon na pilha após a seleção
    push(jog1, pkm_jogador);
}
