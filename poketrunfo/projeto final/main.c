#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "poketrunfo.h"


int main() {
    // variáveis
    Lista2* lista = NULL;
    Fila* fila = cria_fila();
    int valores [10];
    Fila* filajog1 = cria_fila();
    Fila* filajog2 = cria_fila();
    int telaload = 0;
    // abre o arquivo e preenche a lista
    lista = openarq(); 
    // inserindo os pokemons para a fila
    EmbaralhaEInsere(lista, fila, valores);
    // transferindo para as filas dos jogadores
    transferefilaParaFilas(fila, filajog1, filajog2);

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