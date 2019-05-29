/* 
 * File:   Carrida.c
 * Author: João Borges - a21260097
 *
 * Created on 21 de Março de 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Corrida.h"

void CriaCorrida(int *nVoltas, int *compPista, int *nCarros)
{

    do
    {
        printf("Introduza o numero de voltas: ");
        *nVoltas = 6; // readInt();
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

Corredor *AtribuiCorredores(Piloto **p, Carro **c, int totalPilotos, int totalCarros, int maxCorredores, int nVoltas)
{
    Corredor *corrida = NULL, *novo, *aux;

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

    printf("\n\n Maximo de Corredores: %d\n\n", maxCorredores);
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

        novo->ageP = GetPilotoAge(novo->piloto);
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

        // #####################################################################################
        // #####################################################################################

        novo->desistiu = 0;
        novo->ranking = malloc(nVoltas * sizeof(int));

        if (!novo->ranking)
        {
            fprintf(stderr, "Erro a alocar memoria para classificacao");
            free(novo);
            return NULL;
        }

        novo->prox = NULL;
        if (!corrida)
        {
            corrida = novo;
        }
        else
        {
            aux->prox = novo;
        }
        aux = novo;
    }

    //Print dos corredores que vão competir
    mostra_corredores(corrida);

    //print dos pilotos e dos carros que ficaram de fora e a razão
    mostra_corredores_Fora(pilotos_disponiveis, pilotos_disponiveis_conta, *p, totalPilotos, *c, totalCarros,
                           carros_disponiveis, carros_disponiveis_conta);

    // ############# Decrementar impedimentos e avarias a Pilotos/Carros ###################
    // #####################################################################################

    for (int i = 0; i < totalPilotos; i++)
    {
        if (!GetPiloto_Simpedimento((*p)[i]))
        {
            // Decrementar impedimento ao Piloto que está de fora
            *p = SetImpedimento(*p, (*p + i)->id, -1, totalPilotos);
        }
    }

    for (int i = 0; i < totalCarros; i++)
    {
        if (!GetCarro_SAvaria((*c)[i]))
        {
            // Decrementar avaria ao carro que está de fora
            *c = SetAvaria(*c, (*c + i)->id, totalCarros);
        }
    }

    // #####################################################################################
    // #####################################################################################

    return corrida;
}

Rank *IniciaCorrida(Corredor *corrida, int nVoltas, int metros)
{
    Rank *rank, Raux;
    Corredor *aux;
    int desistencias = 0, opc, nDaVolta;
    char resp;

    rank = (Rank *)malloc(sizeof(Rank) * nVoltas);
    if (!rank)
    {
        fprintf(stderr, "Erro a alocar memoria\n");
        return NULL;
    }

    clear();
    for (int i = 0; i < nVoltas; i++)
    {
        rank[i].corredor = NULL;
        rank[i].id = i + 1;

        printf("\n ------------------------------------------ VOLTA: %d -------------------------------------------------\n\n", rank[i].id);
        for (aux = corrida; aux; aux = aux->prox)
        {
            if (aux->desistiu == 0 && probEvento(0.05))
            {
                aux->desistiu = i + 1; // teve acidente na volta i+1
                desistencias++;
                //   SetImpedimento(piloto, idPiloto, 2, total)?
            }

            if (aux->desistiu == 0)
            {
                aux->ranking[i] = calculaSegundos(aux->ageP, aux->piloto.peso, aux->piloto.exp, aux->carro.potencia, metros);

                //printf(" %s  (Id: %d) | Carro %d: ", aux->piloto.nome, aux->piloto.id, aux->carro.id);
                for (int j = 0; j <= i; j++)
                {
                    if (j == 0)
                        aux->rankingTotal = 0;

                    aux->rankingTotal += aux->ranking[j];

                    //printf(" %d + ", aux->ranking[j]);
                }
                


                // Colocar tbm na lista rank os corredores que desistiram, na ultima posicao
                rank[i].corredor = OrderCorredores(rank[i].corredor, aux);
                // printf(" COrredor %s, AUX: %s\n", rank[i].corredor->piloto.nome, aux->piloto.nome);
            }
        }

        mostra_ranking_Volta(rank[i]);

        mostra_desistencias(corrida, desistencias);
        //printf("Po's desistencias %s", corrida->piloto.nome);

        printf("\n ----------------------------------------------------------------------------------------------------- ");

        if (i != (nVoltas-1) )
        {
            printf("\n\n");
            //espera(5);
        }
        printf("\n\n");
    }

    printf(" 1 - Ver Raking total \n");
    printf(" 2 - Ver Raking de uma volta \n");

    do
    {
        printf("\n Escolha uma opc do menu: ");
        opc = readInt();

    } while (opc > 2 || opc <= 0);

    switch (opc)
    {
    case 1:
        mostra_ranking(rank, nVoltas);
        mostra_desistencias(corrida, desistencias);
        break;

    case 2:
        do
        {
            printf("\n Introduza a volta: ");
            nDaVolta = readInt();

        } while (nDaVolta < 1 || nDaVolta > nVoltas);

        mostra_ranking(rank, nDaVolta);
        break;
    }

    getchar();
    getchar();
    return rank;
}

Corredor *OrderCorredores(Corredor *lista, Corredor *new)
{
    Corredor *aux = NULL, *novo;

    novo = (Corredor *)malloc(sizeof(Corredor));
    if (!novo)
    {
        fprintf(stderr, "Erro a alocar memoria.\n");
        return NULL;
    }

    *novo = *new;

    novo->prox = NULL;
    // printf(" Novo %s\n", novo->piloto.nome);
    if (lista == NULL)
    {
        lista = novo;
        // printf(" Lista %s\n", lista->piloto.nome);
    }
    else if (lista->rankingTotal > novo->rankingTotal)
    {
        novo->prox = lista;
        lista = novo;
    }
    else
    {
        aux = lista;
        while (aux->prox != NULL && aux->prox->rankingTotal <= novo->rankingTotal)
        {
            aux = aux->prox;
        }

        novo->prox = aux->prox;
        aux->prox = novo;
    }

    return lista;
}

void mostra_ranking_Volta(Rank r)
{
    Corredor *aux;
    int i = 1;
    aux = r.corredor;

    while (aux != NULL)
    {
        if (aux->desistiu == 0)
        {
            printf("\t %d: %s  (Id: %d) | Carro %d: ", i++, aux->piloto.nome, aux->piloto.id, aux->carro.id);

            for (int j = 0; j < r.id; j++)
            {
                printf(" %d", aux->ranking[j]);

                printf(" + ");
            }
            printf(": %d segundos\n", aux->rankingTotal);
        }
        else
        {
            printf("\t # %s  (Id: %d) | Carro %d - Desistiu na volta: %d\n", aux->piloto.nome, aux->piloto.id, aux->carro.id, aux->desistiu);
        }
        

        aux = aux->prox;
    }
}

void mostra_ranking(Rank r[], int nVoltas)
{
    Corredor *aux;
    int i = 1;

    if (r != NULL)
    {
        aux = r[nVoltas - 1].corredor;
        printf("\n ------------------------------------------ Ranking Geral -------------------------------------------------\n\n");
        while (aux != NULL)
        {
            if (aux->desistiu == 0)
            {
                printf("\t %d:  %s  (Id: %d) | Carro %d: ", i++, aux->piloto.nome, aux->piloto.id, aux->carro.id);

                for (int j = 0; j < nVoltas; j++)
                {
                    printf(" %d + ", aux->ranking[j]);
                }

                printf(": %d segundos\n", aux->rankingTotal);
            }
            else
            {
                printf("\t # %s  (Id: %d) | Carro %d - Desistiu na volta: %d\n", aux->piloto.nome, aux->piloto.id, aux->carro.id, aux->desistiu);
            }
            
            aux = aux->prox;
        }
    }
    else
    {
        fprintf(stderr, "Nao Existe nenhuma corrida efetuada");
    }
}

void mostra_desistencias(Corredor *c, int desistencias)
{
    Corredor *aux = c;

    //printf("Antes ciclo: %s  \n", aux->piloto.nome);
    if (desistencias)
        printf("\n\n\t Desistiu: \n");

    while (aux != NULL)
    {
        //printf("Antes %s  \n", aux->piloto.nome);
        if (aux->desistiu != 0)
        {
            printf("\t    # %s  (Id: %d) | Carro %d - Desistiu na volta: %d\n", aux->piloto.nome, aux->piloto.id, aux->carro.id, aux->desistiu);
        }
        //printf("Antes inc aux %s  \n", aux->prox->piloto.nome);
        aux = aux->prox;
        //printf("Depois inc aux %s\n", aux->piloto.nome);
    }
}

void mostra_corredores(Corredor *c)
{
    Corredor *aux = c;
    printf(" -------------------- Corredores -----------------------\n");
    while (aux != NULL)
    {
        printf(" %s  (Id: %d) | Carro %d IDADE: %d\n", aux->piloto.nome, aux->piloto.id, aux->carro.id, aux->ageP);
        aux = aux->prox;
    }
    free(aux);
}

void mostra_corredores_Fora(Piloto p_disp[], int tamPil, Piloto piloto[], int ptam, Carro car[], int ctam, Carro c_disp[], int tamCar)
{
    //printf("tam Car : %d \t tam Piloto : %d \t p tam: %d \t c tam: %d", tamCar, tamPil, ptam, ctam);
    if (tamCar > 0 || tamPil > 0 || ptam > 0 || ctam > 0)
    {
        printf("\n -------------------- Corredores de Fora ------------------------ \n");
        for (int i = 0; i < tamPil; i++)
            printf(" Nome piloto: %s (ID: %d), Razao: Nao sorteado\n", p_disp[i].nome, p_disp[i].id);

        for (int i = 0; i < tamCar; i++)
            printf(" Carro Id: %d, Razao: Nao sorteado\n", c_disp[i].id);

        for (int i = 0; i < ptam; i++)
        {
            if (!GetPiloto_Simpedimento(piloto[i]))
            {
                printf(" Nome piloto: %s (ID: %d), Razao: Impedido\n", piloto[i].nome, piloto[i].id);
            }
        }

        for (int i = 0; i < ctam; i++)
        {
            if (!GetCarro_SAvaria(car[i]))
            {
                printf(" Carro ID: %d, Razao: Avariado\n", car[i].id);
            }
        }
    }
}
