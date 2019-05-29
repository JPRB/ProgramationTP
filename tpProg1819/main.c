/* 
 * File:   main.c
 * Author: João Borges - a21260097
 *
 * Created on 20 de Março de 2019, 19:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "Piloto.h"
#include "Carro.h"
#include "Corrida.h"



void ExitProgram()
{
    printf("\n Erro ao Carregar informacao\n");
    return;
}

int ExitProgram_wSave(Piloto *pilotos, Carro *carro, int tamPilotos, int tamCarros)
{
    int savePilotos, saveCarros, saveCorrida = 0;

    savePilotos = SavePilotos(pilotos, tamPilotos);

    saveCarros = SaveCarros(carro, tamCarros);

    if (!savePilotos && !saveCarros && !saveCorrida)
    {
        exit(0);
    }
}

void menuPiloto(Piloto *p, int tam)
{
    char *op[] = {"Mostrar Pilotos", "Voltar"};
    int opcoes = (sizeof(op) / sizeof(op[0])), val;

    int voltar = 1;

    while (voltar)
    {
        //        clear();
        printf("----------------menuPiloto-------------\n\n");
        for (int i = 0; i < opcoes; i++)
        {
            printf(" %d - %s \n", i + 1, *(op + i));
        }

        do
        {
            printf("\n Escolha uma opção do menu: ");
            val = readInt();

        } while (val > opcoes || val <= 0);

        switch (val)
        {
        case 1:
            clear();
            MostraPilotos(p, tam);
            break;

        case 2:
            voltar = 0;
            break;
        }
    }
}

void menuCarro(Carro *c, int tam)
{
    char *op[] = {"Mostrar Carros", "Voltar"};
    int opcoes = (sizeof(op) / sizeof(op[0])), val;

    int voltar = 1;

    while (voltar)
    {
        printf("+---------------menuCarro-------------+\n");

        for (int i = 0; i < opcoes; i++)
        {
            printf(" %d - %s \n", i + 1, *(op + i));
        }

        do
        {
            printf("\n Escolha uma opção do menu: ");
            val = readInt();

        } while (val > opcoes || val <= 0);

        switch (val)
        {
        case 1:
            clear();
            MostraCarros(c, tam);
            break;

        case 2:
            voltar = 0;
            break;
        }
    }
}

void menuCorridas(Piloto *pilotos, Carro *carros, int tamPiloto, int tamCarro)
{
    int nVoltas, compPista, nCarros;

    int opc, nDaVolta;

    int voltar = 1;

    Corredor *corrida;
    Rank *ranking;

    while (voltar)
    {
        clear();
        printf("+--------------- Corrida Individual -------------+\n\n");

        printf(" 1 - Criar Novo Corrida Individual \n");
        printf(" 2 - Ver Raking total \n");
        printf(" 3 - Ver Raking de uma volta \n");
        printf(" 4 - Voltar\n");
        do
        {
            printf("\n Escolha uma opc do menu: ");
            opc = readInt();

        } while (opc > 4 || opc <= 0);

        switch (opc)
        {
        case 1:

            CriaCorrida(&nVoltas, &compPista, &nCarros);
            clear();
            corrida = AtribuiCorredores(&pilotos, &carros, tamPiloto, tamCarro, nCarros, nVoltas);
            ranking = IniciaCorrida(corrida, nVoltas, compPista);
            break;

        case 2:
            // mostra_ranking(ranking, nVoltas);
            // getchar();
            break;

        case 3:
            // do
            // {
            //     printf("\n Introduza a volta: ");
            //     nDaVolta = readInt();

            // } while (nDaVolta < 1 || nDaVolta > nVoltas);

            // mostra_ranking(ranking, nDaVolta);
            // getchar();
            break;

        case 4:
            voltar = 0;
            break;
        }
    }
}

void menu(Piloto *pilotos, Carro *carros, int tamPiloto, int tamCarro)
{

    char *op[] = {"Menu Pilotos", "Menu Carros", "Menu Corridas", "Modo Campeonato", "Exit"};
    int val, valid, n_op = (sizeof(op) / sizeof(op[0]));

    for (int i = 0; i < n_op; i++)
    {
        printf(" %d - %s \n", i + 1, *(op + i));
    }

    do
    {
        printf("\n Escolha uma opção do menu: ");
        val = readInt();

    } while (val > n_op || val <= 0);

    switch (val)
    {
    case 1:
        clear();
        menuPiloto(pilotos, tamPiloto);
        break;

    case 2:
        clear();
        menuCarro(carros, tamCarro);
        break;

    case 3:
        menuCorridas(pilotos, carros, tamPiloto, tamCarro);
        break;

    case 4:
        printf("Ainda n ha aqui nada!");
        break;
    case 5:
        ExitProgram_wSave(pilotos, carros, tamPiloto, tamCarro);
        break;

    default:
        menu(pilotos, carros, tamPiloto, tamCarro);
    }
}

int main(int argc, char **argv)
{
    //setlocale(LC_ALL, "Portuguese_Portugal.1252");
    Piloto *pilotos = NULL;
    Carro *carros = NULL;
    int tamPilotos = 0, tamCarros = 0;

    initRandom();
    pilotos = ReadPilotos(&tamPilotos);
    carros = ReadCarros(&tamCarros);

    if (pilotos == NULL || carros == NULL)
    {
        ExitProgram();
        return (EXIT_FAILURE);
    }

    while (1)
    {
        clear();
        menu(pilotos, carros, tamPilotos, tamCarros);
    }

    return (EXIT_SUCCESS);
}