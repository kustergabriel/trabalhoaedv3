#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// defines
#define NAMES 50
#define MAX 50
#define NUM_VALORES 10

typedef struct pokedex {
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

// lista duplamente encadeada
typedef struct lista2 {
    Pokedex info; 
    struct lista2* ant;
    struct lista2* prox;
} Lista2;


// pokemon ponteiro para pokedex
typedef struct elem {
    Pokedex* pokemon;
    struct elem* prox;
} ElemFila;

typedef struct fila {
    ElemFila* ini;
    ElemFila* fim;
} Fila;

// pilha
typedef struct elemPilha {
    Pokedex* pokemon;
    struct elemPilha* prox;
} ElemPilha;

typedef struct pilha {
    ElemPilha* topo;
} Pilha;


Lista2* openarq();
Lista2* insere(Lista2* l, Pokedex p);
void imprime_Pokedex(Lista2* l);
void busca_pokedex(Lista2* l);
void geravalores(int valores[]);
void liberar_lista(Lista2* l);
void libera_fila(Fila* f);
Fila* cria_fila();
void imprime_fila(Fila* f);
void EmbaralhaEInsere(Lista2* lista, Pilha* p, int valores[]);
void transferePilhaParaFilas(Pilha* pilha, Fila* jog1, Fila* jog2);
void imprime_fila_jogador(Fila* f, int fila_num);
int queminiciabatalha(Fila* jog1, Fila* jog2);
void batalhaaaaa(Fila *jog1, Fila *jog2);
Pokedex* remove_fila(Fila* f);
void insere_fila(Fila* f, Pokedex* pokemon);
Pilha* cria_pilha();
void empilha(Pilha* p, Pokedex* pokemon);
Pokedex* desempilha(Pilha* p);

int main() {
    // variáveis
    Lista2* lista = NULL;
    Fila* fila = cria_fila();
    int valores [NUM_VALORES];
    Fila* filajog1 = cria_fila();
    Fila* filajog2 = cria_fila();
    Pilha* pilha = cria_pilha();
    int telaload = 0;
    // abre o arquivo e preenche a lista
    lista = openarq(); 
    // inserindo os pokemons para a fila
    EmbaralhaEInsere(lista, pilha, valores);
    // transferindo para as filas dos jogadores
    transferePilhaParaFilas(pilha, filajog1, filajog2);

        printf("\n===================================================\n");
        printf("\t BEM VINDO(A) AO POKETRUNFO DUSGURI");
        printf("\n===================================================\n");

    while (telaload != 10) {
        printf("\n");
        printf("\t ESCOLHA UMA ALTERNATIVA!!\n\n");
        printf("\t INICIAR JOGO (0)\n");
        printf("\t CONSULTA POKEDEX (1)\n");
        printf("\t SAIR DO JOGO (10)\n");
        scanf("%d", &telaload);

        switch (telaload) {
            case 0:
                batalhaaaaa(filajog1, filajog2);
                break;

            case 1:
                busca_pokedex(lista);
                break;

            case 2:
                printf ("NAO TEM NADA AQUI!!!!!");
                exit (0);
                break;

                case 10:
                exit (0);
                break;

            default:
                printf("Digita outro numero guri!!!\n");
                break;
        }
    }
 

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

// funcao de busca na pokedex 
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
        valores[i] = rand() % 802;
    }
}

// pega os valores e verifica quais sao na pokedex
void EmbaralhaEInsere(Lista2* lista, Pilha* p, int valores[]) {
    geravalores(valores);

    for (int i = 0; i < NUM_VALORES; i++) {
        Lista2* aux = lista; 
        while (aux != NULL) { 
            if (aux->info.num_Pokedex == valores[i]) {
                empilha(p, &(aux->info)); // endereco
                break;
            }
            aux = aux->prox;
        }
    }
}

// filas

// criar fila 
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

// liberar memoria da fila
void libera_fila(Fila* f) {
    while (f->ini != NULL) {
        ElemFila* t = f->ini;
        f->ini = f->ini->prox;
        free(t);
    }
    free(f);
}

// inserindo na fila 
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

// remove elemento da fila
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

// transfere elementos da pilha principal para as filas dos jogadores
void transferePilhaParaFilas(Pilha* pilha, Fila* jog1, Fila* jog2) {
    int i = 0;

    while (pilha->topo != NULL) { // enquanto ainda tem pokemons
        Pokedex* pokemon = desempilha(pilha);  
        
        if (pokemon != NULL) {
            if (i % 2 == 0) {
                insere_fila(jog1, pokemon);  
            } else {
                insere_fila(jog2, pokemon); 
            }
            i++;
        }
    }
}

// apenas verifica qual pokemon tem no topo da fila
Pokedex* topo_fila(Fila* f) {
    if (f->ini == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }
    return f->ini->pokemon;
}

// impressao de fila
void imprime_fila(Fila* f) {
    ElemFila* t = f->ini;
        printf("Nro Pokedex: %d | Nome: %s | Hp: %d | Ataque: %d | Defesa: %d | Ataque Esp: %d | Defesa Esp: %d |\n", t->pokemon->num_Pokedex, t->pokemon->name,t->pokemon->hp,t->pokemon->atk,t->pokemon->def,t->pokemon->sp_atk,t->pokemon->sp_def);
}

void imprime_filatotal(Fila* f) {
    ElemFila* t = f->ini;
    while (t != NULL) {
        printf("%d | ", t->pokemon->num_Pokedex);
        t = t->prox;
    }
}

// pilhas

Pilha* cria_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (!p) {
        printf("Erro ao criar pilha!\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

void empilha(Pilha* p, Pokedex* pokemon) {
    ElemPilha* novo = (ElemPilha*)malloc(sizeof(ElemPilha));
    if (!novo) {
        printf("Erro ao alocar memória para pilha!\n");
        exit(1);
    }
    novo->pokemon = pokemon;
    novo->prox = p->topo;
    p->topo = novo;
}

Pokedex* desempilha(Pilha* p) {
    if (p->topo == NULL) {
        printf("Pilha vazia!\n");
        return NULL;
    }
    ElemPilha* t = p->topo;
    Pokedex* pokemon = t->pokemon;
    p->topo = t->prox;
    free(t);
    return pokemon;
}

// função de batalha

void batalhaaaaa(Fila *jog1, Fila *jog2) {
    int atributo = 0;
    Pokedex* pkm_jogador1 = NULL;
    Pokedex* pkm_jogador2 = NULL;
    int valorAtributo1 = 0, valorAtributo2 = 0;
    int rodadas = 1;
    int jogadorSorteado;
    int continuar = 0;
    Fila* filauxempate = cria_fila();


    while (jog1->ini != NULL && jog2->ini != NULL) { // loop para continuar ate que um jogador tenha a fila vazia

        printf("\n====================================\n");
        printf("              Rodada %d\n", rodadas);
        printf("====================================\n\n");

    pkm_jogador1 = topo_fila(jog1); // pega a carta do topo da fila sem retirar
    pkm_jogador2 = topo_fila(jog2); // pega a carta do topo da fila sem retirar

// verificar se o pokemon eh lendario
    if (strcmp(pkm_jogador1->legendary, "True") || strcmp(pkm_jogador2->legendary, "True")) {
        if (strcmp(pkm_jogador1->legendary, "True")) {
            printf ("JOGADOR 1 GANHA IMEDIATAMENTE POIS SEU POKEMON EH LENDARIO!!");
            printf ("FILA JOG 1 ");
            imprime_fila (jog1);
            printf ("FILA JOG 2 ");
            imprime_fila (jog2);
            insere_fila(jog1, pkm_jogador2);
            insere_fila(jog1, pkm_jogador1);
        }
            printf ("JOGADOR 2 GANHA IMEDIATAMENTE POIS SEU POKEMON EH LENDARIO!!");
            printf("FILA JOG 1 ");
            imprime_fila(jog1);
            printf("FILA JOG 2 ");
            imprime_fila(jog2);
            insere_fila(jog2, pkm_jogador1);
            insere_fila(jog2, pkm_jogador2);
            
    }

        jogadorSorteado = rand() % 2; // 0 para Jogador 1, 1 para Jogador 2
        if (jogadorSorteado == 0) { // jogador 1
            printf("\tJOGADOR 01 INICIA A RODADA\n");
            printf("\nFila do Jogador 1:\n");
            imprime_filatotal(jog1);
            printf ("\n");
            imprime_fila(jog1);
            printf("\nEscolha um atributo para jogar:\n");
            printf("HP (1) | ATAQUE (2) | DEFESA (3) | ATAQUE.SP (4) | DEFESA.SP (5)\n");
            scanf("%d", &atributo);

            switch (atributo) {
                case 1:
                    valorAtributo1 = pkm_jogador1->hp;
                    printf ("Atributo escolhido: Hp: %d \n", pkm_jogador1->hp);

                    break;
                case 2:
                    valorAtributo1 = pkm_jogador1->atk;
                    printf ("Atributo escolhido: Ataque: %d \n", pkm_jogador1->atk);
                    break;
                case 3:
                    valorAtributo1 = pkm_jogador1->def;
                    printf ("Atributo escolhido: Defesa: %d \n", pkm_jogador1->def);
                    break;
                case 4:
                    valorAtributo1 = pkm_jogador1->sp_atk;
                    printf ("Atributo escolhido: Ataque Esp: %d \n", pkm_jogador1->sp_atk);
                    break;
                case 5:
                    valorAtributo1 = pkm_jogador1->sp_def;
                    printf ("Atributo escolhido: Defesa Esp: %d \n", pkm_jogador1->sp_def);
                    break;
                default:
                    printf("Atributo inválido.\n");
                    return;
            }

        } else { // jogador 2
            printf("\tJOGADOR 02 INICIA A RODADA...\n");
            printf("\nFila do Jogador 2:\n");
            imprime_filatotal(jog2);
            printf ("\n");
            imprime_fila(jog2);
            printf("\nJogador 2 escolhendo seu atributo...\n");
            pkm_jogador1 = topo_fila(jog1); 
            pkm_jogador2 = topo_fila(jog2);
            // pc escolhe atributo aleatorio
            atributo = rand() % 5 + 1;
            switch (atributo) {
                case 1:
                    valorAtributo2 = pkm_jogador2->hp;
                    printf ("Atributo escolhido: Hp %d \n", pkm_jogador2->hp);

                    break;
                case 2:
                    valorAtributo2 = pkm_jogador2->atk;
                    printf ("Atributo escolhido: Ataque %d \n", pkm_jogador2->atk);
                    break;
                case 3:
                    valorAtributo2 = pkm_jogador2->def;
                    printf ("Atributo escolhido: Defesa %d \n", pkm_jogador2->def);
                    break;
                case 4:
                    valorAtributo2 = pkm_jogador2->sp_atk;
                    printf ("Atributo escolhido: Ataque Esp %d \n", pkm_jogador2->sp_atk);
                    break;
                case 5:
                    valorAtributo2 = pkm_jogador2->sp_def;
                    printf ("Atributo escolhido: Defesa Esp %d \n", pkm_jogador2->sp_def);
                    break;
                default:
                    printf("Atributo invalido.\n");
                    return;
            }
        }

        if (valorAtributo1 > valorAtributo2) { // jogador 1 ganha
            printf ("COMPARANDO AS CARTAS...\n");
            imprime_filatotal(jog1); // TESTES
            printf ("FILA JOGADOR 1\n");
            imprime_filatotal(jog2); // TESTES
            printf ("FILA JOGADOR 2\n");
            printf("Jogador 1 venceu esta batalha! O Pokemon %s Nro: %d do Jogador 2 passa para o Jogador 1!\n", pkm_jogador2->name, pkm_jogador2->num_Pokedex);
            insere_fila(jog1, pkm_jogador2); 
            remove_fila(jog2);
            insere_fila(jog1, pkm_jogador1); 
            remove_fila(jog1);
            imprime_filatotal(jog1); // TESTES
            printf ("FILA JOGADOR 1\n");
            imprime_filatotal(jog2); // TESTES
            printf ("FILA JOGADOR 2\n");
            printf ("\nInsira 1 para prosseguir... ");
            scanf ("%d", &continuar);
            if (continuar == 1) {
                printf("\t");
            } else {
                printf ("Jogo encerrado!!");
                return ;
            }
        } else if (valorAtributo2 > valorAtributo1) {
            printf ("COMPARANDO AS CARTAS...\n");
            imprime_filatotal(jog1); // TESTES
            printf ("FILA JOGADOR 1\n");
            imprime_filatotal(jog2); // TESTES
            printf ("FILA JOGADOR 2\n");
            printf("Jogador 2 venceu esta batalha! O Pokemon %s Nro: %d do Jogador 1 passa para o Jogador 2!\n", pkm_jogador1->name, pkm_jogador1->num_Pokedex);
            insere_fila(jog2, pkm_jogador1);
            remove_fila(jog1);
            insere_fila(jog2, pkm_jogador2); // inserir o pokemon jogado no final da fila junto com o pokemon ganho
            remove_fila(jog2);
            imprime_filatotal(jog1); // TESTES
            printf ("FILA JOGADOR 1\n");
            imprime_filatotal(jog2); // TESTES
            printf ("FILA JOGADOR 2\n");
            printf ("\nInsira 1 para prosseguir... ");
            scanf ("%d", &continuar);
            if (continuar == 1) {
                printf("\t");
            } else {
                printf ("Jogo encerrado!!");
                return ;
            }
        } else { // empate
    printf("\n====================================\n");
    printf("Empate! Nenhuma carta eh transferida.\n");
    
    insere_fila(filauxempate, pkm_jogador1);
    insere_fila(filauxempate, pkm_jogador2);
    remove_fila(jog1);
    remove_fila(jog2);

    if(jog1->ini == NULL) { 
        printf("\n--- O jogador 2 venceu o jogo! ---\n");
        break;
    }
    if(jog2->ini == NULL) { 
        printf("\n--- O jogador 1 venceu o jogo! ---\n");
        break;
    }

    imprime_filatotal(filauxempate); 
    pkm_jogador1 = topo_fila(jog1); 
    pkm_jogador2 = topo_fila(jog2); 
    
    jogadorSorteado = rand() % 2; 

    if (jogadorSorteado == 0) { 
        printf("\nEsta com sorte, voce vai escolher seu atributo para jogar o desempate!\n");
        imprime_fila(jog1);
        printf("HP (1) | ATAQUE (2) | DEFESA (3) | ATAQUE.SP (4) | DEFESA.SP (5)\n");
        scanf("%d", &atributo);
        switch (atributo) {
            case 1:
                valorAtributo1 = pkm_jogador1->hp;
                valorAtributo2 = pkm_jogador2->hp;
                printf("Atributo escolhido: HP %d \n", pkm_jogador2->hp);
                break;
            case 2:
                valorAtributo1 = pkm_jogador1->atk;
                valorAtributo2 = pkm_jogador2->atk;
                printf("Atributo escolhido: ATK %d \n", pkm_jogador1->atk);
                break;
            case 3:
                valorAtributo1 = pkm_jogador1->def;
                valorAtributo2 = pkm_jogador2->def;
                printf("Atributo escolhido: DEF %d \n", pkm_jogador1->def);
                break;
            case 4:
                valorAtributo1 = pkm_jogador1->sp_atk;
                valorAtributo2 = pkm_jogador2->sp_atk;
                printf("Atributo escolhido: SP.ATK %d \n", pkm_jogador1->sp_atk);
                break;
            case 5:
                valorAtributo1 = pkm_jogador1->sp_def;
                valorAtributo2 = pkm_jogador2->sp_def;
                printf("Atributo escolhido: SP.DEF %d \n", pkm_jogador1->sp_def);
                break;
            default:
                printf("Atributo inválido.\n");
                return;
        }
    } else { 
        printf("JOGADOR 02 JOGANDO O DESEMPATE!\n");
        imprime_fila(jog2);
        atributo = rand() % 5 + 1;
        switch (atributo) {
            case 1:
                valorAtributo1 = pkm_jogador1->hp;
                valorAtributo2 = pkm_jogador2->hp;
                printf("Atributo escolhido: HP %d \n", pkm_jogador2->hp);
                break;
            case 2:
                valorAtributo1 = pkm_jogador1->atk;
                valorAtributo2 = pkm_jogador2->atk;
                printf("Atributo escolhido: ATK %d \n", pkm_jogador2->atk);
                break;
            case 3:
                valorAtributo1 = pkm_jogador1->def;
                valorAtributo2 = pkm_jogador2->def;
                printf("Atributo escolhido: DEF %d \n", pkm_jogador2->def);
                break;
            case 4:
                valorAtributo1 = pkm_jogador1->sp_atk;
                valorAtributo2 = pkm_jogador2->sp_atk;
                printf("Atributo escolhido: SP.ATK %d \n", pkm_jogador2->sp_atk);
                break;
            case 5:
                valorAtributo1 = pkm_jogador1->sp_def;
                valorAtributo2 = pkm_jogador2->sp_def;
                printf("Atributo escolhido: SP.DEF %d \n", pkm_jogador2->sp_def);
                break;
            default:
                printf("Atributo invalido.\n");
                return;
        }
    }

    if (valorAtributo1 > valorAtributo2) { 
        printf("JOGADOR 01 VENCEU O COMBATE DO EMPATE!!!\n");
        insere_fila(jog1, pkm_jogador1);
        insere_fila(jog1, pkm_jogador2);
        // move todas as cartas da fila auxiliar para o jogador 1
        while (filauxempate->ini != NULL) {
            Pokedex* pkm = topo_fila(filauxempate);
            insere_fila(jog1, pkm);
            remove_fila(filauxempate);
        }
        remove_fila(jog1);
        remove_fila(jog2);
        imprime_filatotal(jog1);
        printf("FILA JOG 1\n");
        imprime_filatotal(jog2);
        printf("FILA JOG 2\n");
    } else { 
        printf("JOGADOR 02 VENCEU O COMBATE DO EMPATE!!!\n");
        insere_fila(jog2, pkm_jogador1);
        insere_fila(jog2, pkm_jogador2);
        // move todas as cartas da fila auxiliar para o jogador 2
        while (filauxempate->ini != NULL) {
            Pokedex* pkm = topo_fila(filauxempate);
            insere_fila(jog2, pkm);
            remove_fila(filauxempate);
        }
        remove_fila(jog1);
        remove_fila(jog2);
        imprime_filatotal(jog1);
        printf("FILA JOG 1\n");
        imprime_filatotal(jog2);
        printf("FILA JOG 2\n");
    }
}
        rodadas++;
    }

    // Verifica o vencedor final
    if (jog1->ini == NULL) {
        printf("\n\nJogador 2 eh o vencedor!!!!\n\n");
        printf ("FILHA GANHADORA ");
        imprime_filatotal(jog2); 

    } else if (jog2->ini == NULL) {
        printf("\n\nJogador 1 eh o vencedor!!!!\n\n");
        printf ("FILHA GANHADORA ");
        imprime_filatotal(jog1);
    }
}