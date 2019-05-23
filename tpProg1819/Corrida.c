/* 
 * File:   Carro.c
 * Author: João Borges - a21260097
 *
 * Created on 21 de Março de 2019
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Corrida.h"

void CriaCorrida(int *nVoltas, int *compPista, int *nCarros)
{

    do
    {
        printf("Introduza o numero de voltas: ");
        *nVoltas = 5; //readInt();
    } while (*nVoltas < 5 || *nVoltas > 10 || *nVoltas == -1);

    do
    {
        printf("Introduza o comprimento da Pista (m): ");
        *compPista = 500; //readInt();
    } while (*compPista < 500 || *compPista > 1000 || *compPista == -1);

    do
    {
        printf("Introduza o numero de Carros max: ");
        *nCarros = 3; // readInt();
    } while (*nCarros <= 0);
}

Corredor *AtribuiCorredores(Piloto **p, Carro **c, int totalPilotos, int totalCarros, int maxCorredores)
{
    Corredor *corrida = NULL, *novo;

    Piloto *pilotos_disponiveis;
    Carro *carros_disponiveis;

    int min, max, pilotos_disponiveis_conta, carros_disponiveis_conta;
    int id;

    // printf("\nPointer simple: %d\n", (*p + 0)->id);
    // printf("Double Pointer: %d\n", (*(p + 0))->id);
    // printf("What?: %s\n", (*p)[0].nome);

    // system("pause");

    //printf("\n\nPilotos: %d Carros: %d Max Corredores %d \n\n", totalPilotos, totalCarros, maxCorredores);

    //####################### Pilotos Disponiveis para correr ##############################
    pilotos_disponiveis = PilotosDisponiveis(*p, totalPilotos, &pilotos_disponiveis_conta);

    // printf("Pilotos disponiveis: %d \n", pilotos_disponiveis_conta);
    // for (int i = 0; i < pilotos_disponiveis_conta; i++)
    // {
    //     printf("Id: %d \t Nome: %s \t Imped: %d \n", pilotos_disponiveis[i].id, pilotos_disponiveis[i].nome, pilotos_disponiveis[i].impedimento);
    // }

    // #############################################################################################################

    //printf("Conta: %d \t Id: %d Nome: %s Imped: %d \n",pilotos_disponiveis_conta, pilotos_disponiveis->id, pilotos_disponiveis->nome, pilotos_disponiveis->impedimento);

    // ####################### Carros disponiveis para correr ##############################
    carros_disponiveis = CarrosDisponiveis(*c, totalCarros, &carros_disponiveis_conta);

    // printf("\n\nCarros disponiveis: %d \n", carros_disponiveis_conta);
    // for (int i = 0; i < carros_disponiveis_conta; i++)
    // {
    //     printf("Id: %d \t Avariado: %d \n", carros_disponiveis[i].id, carros_disponiveis[i].avariado);
    // }

    //#####################################################################################

    // ######################## Definir Maximo de Corredores ##################################
    /*
     * @  SE (totalpilotos_disponiveis > totalcarros_disponiveis)
     *      totalCorredores = totalcarros_disponiveis
     *    SENÂO
     *      totalCorredores = totalpilotos_disponiveis
     */

    if ((pilotos_disponiveis_conta > carros_disponiveis_conta) && carros_disponiveis_conta <= maxCorredores)
    {
        maxCorredores = carros_disponiveis_conta;
    }
    else if ((pilotos_disponiveis_conta <= carros_disponiveis_conta) && pilotos_disponiveis_conta <= maxCorredores)
    {
        maxCorredores = pilotos_disponiveis_conta;
    }

    printf("\n\nMaximo de Corredores: %d\n\n", maxCorredores);
    // ########################################################################################

    // ##################### $$$$$$$$$$$$$$$$$$$€€€€€€€€€€€€€€€€€€€€€ ##############################
    // ##################### Atribuir Pares (Carros | PILOTOS) #####################################

    if (carros_disponiveis == NULL || pilotos_disponiveis == NULL)
    {
        fprintf(stderr, "Corrida nao e' possivel ser efetuada\n");
        return NULL;
    }

    //Atribuição de pilotos a carros de forma aleatoria
    for (int i = 0; i < maxCorredores; i++)
    {
        novo = malloc(sizeof(Corredor));
        if (novo == NULL)
        {
            fprintf(stderr, "Erro na alocacao de memoria\n");
            return NULL;
        }

        novo->id = i + 1;
        // #################################### Pilotos Disponiveis #####################################
        // ##############################################################################################

        // rnd ID pilotos disponiveis
        MaxMinIDPilotos(pilotos_disponiveis, pilotos_disponiveis_conta, &min, &max);

        // verificar se ID existe em pilotos disponiveis
        do
        {
            id = intUniformRnd(min, max);
        } while (ExistPiloto(pilotos_disponiveis, pilotos_disponiveis_conta, id));

        // Se existir colocar em Corredores
        novo->piloto = GetPilotoByID(pilotos_disponiveis, pilotos_disponiveis_conta, id);
        // retirar da lista de pilotos disponiveis
        pilotos_disponiveis = eliminarPiloto(pilotos_disponiveis, &pilotos_disponiveis_conta, id);

        // ##############################################################################################
        // ##############################################################################################

        // #################################### Carros Disponiveis #####################################
        // #############################################################################################

        //  rnd carros disponiveis
        MaxMinIDCarros(carros_disponiveis, carros_disponiveis_conta, &min, &max);

        //  verificar se ID existe em carros disponiveis - Condição de paragem = 0
        do
        {
            id = intUniformRnd(min, max);
            // printf("Carros Id rnd: %d\n\n", id);
        } while (ExistCar(carros_disponiveis, carros_disponiveis_conta, id));

        //  Colocar em Corredores
        novo->carro = GetCarByID(carros_disponiveis, carros_disponiveis_conta, id);

        //  retirar da lista de carros disponiveis baseado no id
        carros_disponiveis = eliminarCarro(carros_disponiveis, &carros_disponiveis_conta, id);

        corrida = Insere_corredor(corrida, novo);
    }

    // #####################################################################################

    //Print dos corredores que vão competir
    mostra_corredores(corrida);

    //print dos pilotos e dos carros que ficaram de fora e a razão
    mostra_corredores_Fora(pilotos_disponiveis, pilotos_disponiveis_conta, *p, totalPilotos, *c, totalCarros,
                           carros_disponiveis, carros_disponiveis_conta);
    

    for (int i = 0; i < totalPilotos; i++)
    {
        if (!GetPiloto_Simpedimento((*p)[i]))
        {
            // Decrementar impedimento ao Piloto que está de fora
            *p = SetImpedimento(*p, (*p+i)->id, -1, totalPilotos);
        }
    }

    for (int i = 0; i < totalCarros; i++)
    {
        if (!GetCarro_SAvaria((*c)[i]))
        {
            // Decrementar impedimento ao carro que está de fora
            *c = SetAvaria(*c, (*c+i)->id, totalCarros);
        }
    }

    getchar();
    return corrida;
}

Corredor *Insere_corredor(Corredor *corrida, Corredor *corredor)
{
    Corredor *aux;

    if (corrida == NULL)
    {
        corredor->prox = NULL;
        corrida = corredor;
    }
    else
    {
        aux = corrida;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = corredor;
    }

    return corrida;
}

void mostra_corredores(Corredor *c)
{
    Corredor *aux = c;
    printf("-------------------- Corredores -----------------------\n");
    while (aux != NULL)
    {
        printf(" %s  (Id: %d) | Carro %d \n", aux->piloto.nome, aux->piloto.id, aux->carro.id);
        aux = aux->prox;
    }
    free(aux);
}

void mostra_corredores_Fora(Piloto p_disp[], int tamPil, Piloto piloto[], int ptam, Carro car[], int ctam, Carro c_disp[], int tamCar)
{
    //printf("tam Car : %d \t tam Piloto : %d \t p tam: %d \t c tam: %d", tamCar, tamPil, ptam, ctam);
    if (tamCar > 0 || tamPil > 0 || ptam > 0 || ctam > 0)
    {
        printf("\n ------------ Corredores de Fora ------------- \n");
        for (int i = 0; i < tamPil; i++)
            printf(" Nome piloto: %s (ID: %d), Razao: Nao sorteado\n", p_disp[i].nome, p_disp[i].id);
        for (int i = 0; i < ptam; i++)
        {
            if (!GetPiloto_Simpedimento(piloto[i]))
            {
                printf(" Nome piloto: %s (ID: %d), Razao: Impedido\n", piloto[i].nome, piloto[i].id);
            }
        }

        for (int i = 0; i < tamCar; i++)
            printf(" Carro Id: %d, Razao: Nao sorteado\n", c_disp[i].id);

        for (int i = 0; i < ctam; i++)
        {
            if (!GetCarro_SAvaria(car[i]))
            {
                printf(" Carro ID: %d, Razao: Avariado\n", car[i].id);
            }
        }
    }
}
