#ifndef poketrunfo_h
#define poketrunfo_h

typedef struct pokedex Pokedex;
typedef struct lista2 Lista2;
typedef struct elem ElemFila;
typedef struct fila Fila;

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
void transferefilaParaFilas(Fila* fila, Fila* jog1, Fila* jog2);
void imprime_fila_jogador(Fila* f, int fila_num);
int queminiciabatalha(Fila* jog1, Fila* jog2);
void batalhaaaaa(Fila *jog1, Fila *jog2);
Pokedex* remove_fila(Fila* f);
void insere_fila(Fila* f, Pokedex* pokemon);


#endif