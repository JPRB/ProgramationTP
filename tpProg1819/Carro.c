
/* 
 * File:   Carro.c
 * Author: João Borges - a21260097
 *
 * Created on 20 de Março de 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include "Carro.h"

//Carro

Carro *ReadCarros(int *tam)
{
    FILE *f_cars;
    Carro *carros, carro;

    f_cars = fopen("Carros.txt", "r");

    //Se for null Erro no acesso
    if (f_cars == NULL)
    {
        printf("Erro no acesso ao ficheiro\n");
        *tam = 0;
        return NULL;
    }

    carros = malloc(sizeof(Carro));

    //Se não conseguir alocar memória..
    if (carros == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        return NULL;
    }

    while (fscanf(f_cars, " %d %d %d", &carro.id, &carro.potencia, &carro.avariado) == 3)
    {
        // validar id (unico) && > 0, potencia > 0
        if (carro.id < 0 || carro.potencia <= 0 || !ExistCar(carros, *tam, carro.id))
        {
            return NULL;
        }
        carros = AdicionaCarro(carros, carro, tam);
    }

    if (!feof(f_cars))
    {
        free(carros);
        fclose(f_cars);
        return NULL;
    }

    fclose(f_cars);

    return carros;
}

Carro *AdicionaCarro(Carro carros[], Carro newCarro, int *tam)
{
    Carro *aux;
    int new_size = (*tam + 1);

    aux = realloc(carros, new_size * sizeof(Carro));

    if (aux == NULL)
        return carros;

    carros = aux;

    //incrementar o tamanho
    (*tam)++;
    //Associar novo carro para o array de Carros
    carros[*tam - 1] = newCarro;

    return carros;
}

void MostraCarros(Carro *carro, int tam)
{

    printf("+------+-----------+-----------+\n"
           "|  ID  | Potencia  |  Avariado |\n"
           "+------+-----------+-----------+\n");
    for (int i = 0; i < tam; i++)
    {
        printf("| %-4d | %-9d | %-9d |\n",
               carro[i].id, carro[i].potencia, carro[i].avariado);
    }

    printf("+------+-----------+-----------+\n");

}

int SaveCarros(Carro carros[], int tam)
{

    FILE *fcarros;
    Carro *c;

    fcarros = fopen("Carros.txt", "w");

    if (fcarros == NULL)
    {
        printf("Erro no acesso ao ficheiro\n");
        //*tam = 0;
        return -1;
    }

    for (c = carros; c < (carros + tam); c++)
    {
        fprintf(fcarros, "%d  %d  %d\n\n", c->id, c->potencia, c->avariado);
    }

    free(carros);
    fclose(fcarros);

    return 0;
}

Carro GetCarByID(Carro c[], int tam, int id)
{
    if (c != NULL)
    {
        for (int i = 0; i < tam; i++)
        {
            if (c[i].id == id)
            {
                return c[i];
            }
        }
    }
}

Carro *SetAvaria(Carro c[], int tam, int id)
{
    if (c != NULL)
    {
        for (int i = 0; i < tam; i++)
        {
            if (c[i].id == id && c[i].avariado == 0)
            {
                c[i].avariado = 1;
                return c;
            }
            else
            {
                c[i].avariado = 0;
                return c;
            }
        }
    }
    else
    {
        fprintf(stderr, "Piloto não encontrado!");
    }

    return NULL;
}

int GetCarro_SAvaria(Carro c)
{
    if (c.avariado > 0)
    {
        // há impedimento
        return 0;
    }

    return 1;
}

void MaxMinIDCarros(Carro c[], int tam, int *min, int *max) // (void *)v
{

    *max = c->id;
    *min = c->id;

    //printf("max %d min %d, NOme: %s\n", *max, *min);
    for (int i = 0; i < tam; i++)
    {
        if (*min > c[i].id)
        {
            *min = c[i].id;
        }

        if (*max < c[i].id)
        {

            *max = c[i].id;
        }
        //printf("New max: %d New min: %d\n\n", *max, *min);
    }
}

Carro *CarrosDisponiveis(Carro *c, int totalcarros, int *carros_disponiveis_conta)
{

    Carro *carros_disponiveis, *aux;

    *carros_disponiveis_conta = 0;
    carros_disponiveis = malloc(sizeof(Carro));

    if (!carros_disponiveis)
    {
        fprintf(stderr, "Erro a alocar memoria\n");
        return NULL;
    }

    for (int i = 0; i < totalcarros; i++)
    {
        if (GetCarro_SAvaria(c[i]))
        {
            carros_disponiveis = AdicionaCarro(carros_disponiveis, *(c + i), carros_disponiveis_conta);
        }
    }

    // Verificar se ha' carros disponiveis
    if (*carros_disponiveis_conta == 0)
    {
        fprintf(stderr, "Nao e' possivel efetuar corridas sem carros\n");
        return NULL;
    }

    return carros_disponiveis;
}

int ExistCar(Carro carros_disponiveis[], int tam, int id_car)
{
    if (carros_disponiveis != NULL)
    {
        for (int i = 0; i < tam; i++)
        {
            // existe - return 0
            if (carros_disponiveis[i].id == id_car)
            {
                return 0;
            }
        }

        return 1;
    }
}

Carro *eliminarCarro(Carro carro[], int *tam, int idCar)
{
    Carro aux;
    int j;
    if (carro != NULL)
    {
        for (int i = 0; i < *tam; i++)
        {
            if (carro[i].id == idCar)
            {
                aux = carro[i];
                j = i + 1;
                while (j < *tam)
                {
                    carro[j - 1] = carro[j];
                    j++;
                }
                (*tam)--;
                return carro;
            }
        }
    }

    return NULL;
}