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
#include "Campeonato.h"

void ExitProgram()
{
    printf("\n Erro ao Carregar informacao\n");
    return;
}

int ExitProgram_wSave(Piloto *pilotos, Carro *carro, int tamPilotos, int tamCarros, Campeonato campeonato)
{
    int savePilotos, saveCarros, saveCampeonato;

    savePilotos = SavePilotos(pilotos, tamPilotos);

    saveCarros = SaveCarros(carro, tamCarros);

    saveCampeonato = SaveCampeonato("Campeonato", campeonato);

    if (!savePilotos && !saveCarros && !saveCampeonato)
    {
        return (0);
    }

    fprintf(stderr, "Impossivel sair do programa");
    return 1;
}

void menuPiloto(Piloto *p, int tam)
{
    char *op[] = {"Mostrar Pilotos", "Adicionar Impedimento", "Voltar"};
    int opcoes = (sizeof(op) / sizeof(op[0])), opc;

    int id, imp;
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
            printf("\n Escolha uma opc do menu: ");
            opc = readInt();

        } while (opc > opcoes || opc <= 0);

        switch (opc)
        {
        case 1:
            clear();

            MostraPilotos(p, tam);
            break;

        case 2:
            // comportamento incorreto. penalização
            do
            {
                printf(" Introduza o id do piloto a penalizar: ");
                id = readInt();

            } while (ExistPiloto(p, tam, id) ? printf(" Piloto nao encontrado! \n") : printf(" ######  Piloto encontrado ###### \n\n") && id <= 0);

            do
            {
                printf("\n  Introduza um impedimento (1-3): ");
                imp = readInt();
            } while (imp > 3 || imp <= 0);

            p = SetImpedimento(p, id, imp, tam);

            printf("\n  Piloto penalizado em %d unidades \n\n", imp);
            break;

        case 3:
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
            printf("\n Escolha uma opc do menu: ");
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

void RealizaCorrida(Piloto *pilotos, Carro *carros, int tamPiloto, int tamCarro)
{
    // int nVoltas, compPista, nCarros;

    // Corredor *corrida;
    // Rank *ranking;

    // CriaCorrida(&nVoltas, &compPista, &nCarros);
    // clear();
    // corrida = AtribuiCorredores(&pilotos, &carros, tamPiloto, tamCarro, nCarros, nVoltas);
    // ranking = IniciaCorrida(corrida, nVoltas, compPista);

    Correr(pilotos, carros, tamPiloto, tamCarro);
}

void menu(Piloto *pilotos, Carro *carros, int tamPiloto, int tamCarro, int champ, Campeonato c)
{

    char *op[] = {"Menu Pilotos", "Menu Carros", "Menu Corridas", "Modo Campeonato", "Exit"};
    int val, valid, n_op = (sizeof(op) / sizeof(op[0]));

    int finnish = 1;

    while (finnish)
    {
        //clear();
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
            clear();
            if (champ == 0)
            {    
                printf("+--------------- Corrida Individual -------------+\n\n");
                RealizaCorrida(pilotos, carros, tamPiloto, tamCarro);
            }
            else {
                printf(" Nao e' possivel fazer corridas com o campeonato a decorrer \n");
            }
            break;

        case 4:
            clear();
            printf("+--------------- Campeonato  -------------+\n\n");
            c = ChampionShip(pilotos, carros, tamPiloto, tamCarro, &champ, c);
            break;
        case 5:
            finnish = ExitProgram_wSave(pilotos, carros, tamPiloto, tamCarro, c);
            break;

            // default:
            //     menu(pilotos, carros, tamPiloto, tamCarro, champ);
        }
    }
}

int main(int argc, char **argv)
{
    //setlocale(LC_ALL, "Portuguese_Portugal.1252");
    Piloto *pilotos = NULL;
    Carro *carros = NULL;
    Campeonato c;

    int tamPilotos = 0, tamCarros = 0;
    int champ = 0;

    
    initRandom();
    pilotos = ReadPilotos(&tamPilotos);
    carros = ReadCarros(&tamCarros);

    if (pilotos == NULL || carros == NULL)
    {
        ExitProgram();
        return (EXIT_FAILURE);
    }

    // ver se campeonato está ativo, se estiver
    c.nProvas_realizadas = 0;
    
    menu(pilotos, carros, tamPilotos, tamCarros, champ, c);

    return (EXIT_SUCCESS);
}