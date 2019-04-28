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

typedef struct {
    Piloto *pilotos;
    Carro *carros;
    int tamPilotos;
    int tamCarros;

} Karts;

void ExitProgram() {
    printf("Erro ao Carregar informação");
    exit(EXIT_FAILURE);
}

Karts ReadProgram() {
    Karts k;

    k.pilotos = ReadPilotos(&k.tamPilotos);
    k.carros = ReadCarros(&k.tamCarros);

    if (k.pilotos == NULL || k.carros == NULL) {
        ExitProgram();
    }

    return k;
}



void menuPiloto(Piloto *p) {
    int tam = 0;
    char *op[] = {"Mostrar Pilotos", "Voltar"};
    int opcoes = (sizeof (op) / sizeof (op[0])), val;

    int voltar = 1;

        p = ReadPilotos(&tam);
    
        if (p == NULL)
        {
            ExitProgram();
        }

    while (voltar) {
        //        system("cls");
        printf("----------------menuPiloto-------------\n\n");
        for (int i = 0; i < opcoes; i++) {
            printf("%d - %s \n", i + 1, *(op + i));
        }

        do {
            printf("\nEscolha uma opção do menu: ");
            scanf("%d", &val) == 1;

        } while (val > opcoes || val <= 0);

        switch (val) {
            case 1:
                system("cls");
                MostraPilotos(p, tam);
                break;

            case 2:
                voltar = 0;
                break;
        }
    }

    //SetImpedimento(p, 3, 15, tam);

    //SavePilotos(p, tam);
}

void menuCarro(Carro *c) {
    int tam = 0;
    char *op[] = {"Mostrar Carros", "Voltar"};
    int opcoes = (sizeof (op) / sizeof (op[0])), val;

    int voltar = 1;

        c = ReadCarros(&tam);
    
        if (c == NULL)
        {
            ExitProgram();
        }

    while (voltar) {
        printf("+---------------menuCarro-------------+\n");

        for (int i = 0; i < opcoes; i++) {
            printf("%d - %s \n", i + 1, *(op + i));
        }

        do {
            printf("\nEscolha uma opção do menu: ");
            scanf("%d", &val) == 1;

        } while (val > opcoes || val <= 0);

        switch (val) {
            case 1:
                system("cls");
                MostraCarros(c, tam);
                break;

            case 2:
                voltar = 0;
                break;
        }
    }
}

void menuCorridas() {
}

int SaveData(Karts k) {
    int savePilotos, saveCarros, saveCorrida;

    savePilotos = SavePilotos(k.pilotos, k.tamPilotos);

    saveCarros = SaveCarros(k.carros, k.tamCarros);
}

void menu(Piloto *pilotos, Carro *carro) {

    char *op[] = {"Menu Pilotos", "Menu Carros", "Menu Corridas", "Modo Campeonato", "Exit"};
    int val, valid;

    for (int i = 0; i < (sizeof (op) / sizeof (op[0])); i++) {
        printf("%d - %s \n", i + 1, *(op + i));
    }

    do {
        printf("\nEscolha uma opção do menu: ");
        scanf("%d", &val) == 1;

    } while (val > 4 || val <= 0);

    switch (val) {
        case 1:
            system("cls");
            menuPiloto(pilotos);
            break;

        case 2:
            system("cls");
            menuCarro(carro);
            break;

        case 3:
            menuCorridas();
            break;

        case 4:
            exit(0);
            break;

        default:
            menu(pilotos, carro);
    }
}

int main(int argc, char **argv) {
    //setlocale(LC_ALL, "Portuguese_Portugal.1252");
    Karts k;


    //    k = ReadProgram();

    while (1) {
        system("cls");
        menu(k.pilotos, k.carros); 
        
    } 

    return (EXIT_SUCCESS);
}