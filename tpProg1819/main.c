 /* 
 * File:   main.c
 * Author: João Borges - a21260097
 *
 * Created on 20 de Março de 2019, 19:37
 */

#include <stdio.h>
#include <stdlib.h>

#include "Piloto.h"
#include "Carro.h"

#include <locale.h>



void menuPiloto(Piloto *p) {
    int tam = 0;

    printf("+---------------menuPiloto-------------+\n");
    p = ReadPilotos(&tam);
    
    MostraPilotos(p, tam);
}

void menuCarro(Carro *c) {
    int tam = 0;

    printf("+---------------menuCarro-------------+\n");
    c = ReadCarros(&tam);
    
    MostraCarros(c, tam);
}

void menuCorridas() {

}

void menu(Piloto *piloto, Carro *carro) {

    char *op[] = {"Menu Pilotos", "Menu Carros", "Menu Corridas"};
    int val;

    for (int i = 0; i < (sizeof (op) / sizeof (op[0])); i++) {
        printf("%d - %s \n", i + 1, *(op + i));

    }

    do {
        printf("Escolha uma opção do menu: ");
        scanf("%d", &val);

    } while (val > 3 || val <= 0);


    switch (val) {
        case 1:
            menuPiloto(piloto);
            break;

        case 2:
            menuCarro(carro);
            break;

        case 3:
            menuCorridas();
            break;

        default:
            menu(piloto, carro);
    }
}

int main(int argc, char** argv) {
    Piloto *p;
    Carro *c;


    menu(p, c);

    return (EXIT_SUCCESS);
}

