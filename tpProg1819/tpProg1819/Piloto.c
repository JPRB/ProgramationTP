#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Piloto.h"

//void menuPiloto(){
//
//}

Piloto *ReadPilotos(int *tam)
{
    FILE *fpiloto;
    Piloto *pilotos, piloto;

    fpiloto = fopen("Pilotos.txt", "r");

    if (fpiloto == NULL)
    {
        printf("Erro no acesso ao ficheiro\n");
        *tam = 0;
        return NULL;
    }

    //Memory alocated to Piloto Size
    pilotos = (Piloto *)malloc(sizeof(Piloto));

    if (pilotos == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        fclose(fpiloto);
        return NULL;
    }
    else
    {

        //While can read
        while (fscanf(fpiloto, " %99[^\n] %d %d %d %d %d %f %d ", piloto.nome, &piloto.id, &piloto.dataNasc.dia,
                      &piloto.dataNasc.mes, &piloto.dataNasc.ano, &piloto.peso, &piloto.exp, &piloto.impedimento) == 8)
        {
            pilotos = AdicionaPiloto(pilotos, piloto, tam);
        }
    }

    fclose(fpiloto);

    return pilotos;
}

Piloto *AdicionaPiloto(Piloto pilotos[], Piloto newPiloto, int *tam)
{
    Piloto *aux;
    int new_size = (*tam + 1);

    aux = realloc(pilotos, new_size * sizeof(Piloto));

    if (aux == NULL)
    {
        //        printf("aux null \n");
        return pilotos;
    }

    pilotos = aux;
    //INC Tam value
    (*tam)++;

    //Associar novo piloto para o array de pilotos
    pilotos[*tam - 1] = newPiloto;

    return pilotos;
}

void MostraPilotos(Piloto piloto[], int tam)
{

    printf("+--------------------------------------+-------------+---------------------+"
           "--------+--------------+-------------+\n"
           "|                Nome                  |      ID     |  Data de nascimento "
           "|  Peso  | Experiencia  | Impedimento |\n"
           "+--------------------------------------+-------------+---------------------"
           "+--------+--------------+-------------+\n");

    for (int i = 0; i < tam; i++)
    {
        printf("| %-36s | %-11d | %.2d/%.2d/%-13d | %-6d | %-12.1f | %-10d |\n",
               piloto[i].nome, piloto[i].id, piloto[i].dataNasc.dia, piloto[i].dataNasc.mes,
               piloto[i].dataNasc.ano, piloto[i].peso, piloto[i].exp, piloto[i].impedimento);
    }

    printf("+--------------------------------------+-------------+---------------------+"
           "------------+--------------+-------------+\n");

    //     rpintf("Size: %d Tam: %d", sizeof(piloto), tam);
}

void MostraPiloto(Piloto piloto)
{
    printf(" Nome: %s \t Id: %d \t Data de nascimento: %d/%d/%d \t Peso: %d \t Exp: %.2f \t Imp: %d \n",
           piloto.nome, piloto.id, piloto.dataNasc.dia, piloto.dataNasc.mes,
           piloto.dataNasc.ano, piloto.peso, piloto.exp, piloto.impedimento);
}

int SavePilotos(Piloto pilotos[], int tam)
{

    FILE *fpiloto;
    Piloto *p;

    fpiloto = fopen("PilotosTest.txt", "w");

    if (fpiloto == NULL)
    {
        fprintf(stderr, "Erro a criar ficheiro\n");
        //*tam = 0;
        //free(pilotos);
        return -1;
    }

    for (p = pilotos; p < (pilotos + tam); p++)
    {
        fprintf(fpiloto, "%s\n%d %d %d %d %d %.1f %d\n\n", p->nome, p->id, p->dataNasc.dia,
                p->dataNasc.mes, p->dataNasc.ano, p->peso, p->exp, p->impedimento);
    }

    fclose(fpiloto);
    free(p);
    free(pilotos);
    return 0;
}

/*Carro *GetImpedimento(Carro *car, int totalCar, int id) {

    for (int i = 0; i < totalCar; i++)
        if (car[i]->id == id)
            return car[i];

    return 0;
}*/

//int GetImpedimento(Piloto piloto[], int totalPilotos, int idPiloto) {
//
//    for (int i = 0; i < totalPilotos; i++) {
//        if (piloto[i].id == idPiloto) {
//            return piloto[i].impedimento;
//        }
//    }
//    return -1;
//}

Piloto *SetImpedimento(Piloto p[], int idPiloto, int valorImpedimento, int totalPilotos)
{
    if (p != NULL)
    {
        for (int i = 0; i < totalPilotos; i++)
        {
            if (p[i].id == idPiloto)
            {
                p[i].impedimento += valorImpedimento;
                return p;
            }
        }
    }
    else
    {
        fprintf(stderr, "Piloto não encontrado!");
    }

    return NULL;
}

Piloto GetPilotoByID(Piloto piloto[], int tam, int id)
{
    if (piloto != NULL)
    {
        for (int i=0; i < tam; i++)
        {
            if (piloto[i].id == id)
            {
                return piloto[i];
            }
        }
    }
}

int GetPiloto_Simpedimento(Piloto piloto)
{   
    if (piloto.impedimento > 0)
    {
        // há impedimento
        return 0;
    }

    return 1;
}

void MaxMinIDPilotos(Piloto p[], int tam, int *min, int *max) // (void *)v
{

    *max = p->id;
    *min = p->id;

    //printf("max %d min %d, NOme: %s\n", *max, *min);
    for (int i = 0; i < tam; i++)
    {
        if (*min > p[i].id)
        {
            *min = p[i].id;
        }

        if (*max < p[i].id)
        {

            *max = p[i].id;
        }
        //printf("New max: %d New min: %d\n\n", *max, *min);
    }
}

Piloto *PilotosDisponiveis(Piloto *p, int totalPilotos, int *pilotos_disponiveis_conta)
{

    Piloto *pilotos_disponiveis, *aux;

    *pilotos_disponiveis_conta = 0;
    pilotos_disponiveis = malloc(sizeof(Piloto));

    if (!pilotos_disponiveis)
    {
        fprintf(stderr, "Erro a alocar memoria\n");
        return NULL;
    }

    for (int i = 0; i < totalPilotos; i++)
    {
        if (GetPiloto_Simpedimento(p[i]))
        {
            //     printf("Piloto sem impoedimento: %s\n", p[i].nome);
            pilotos_disponiveis = AdicionaPiloto(pilotos_disponiveis, *(p + i), pilotos_disponiveis_conta);
        }
        // printf("ID: %d \t Nome: %s\n", pilotos_disponiveis[0].id, pilotos_disponiveis[0].nome);
    }

    // Verificar se ha' pilotos disponiveis
    if (*pilotos_disponiveis_conta == 0)
    {
        fprintf(stderr, "Nao e' possivel efetuar corridas sem corredores\n");
        return NULL;
    }

    return pilotos_disponiveis;
}

int ExistPiloto(Piloto pilotos[], int tam, int id_car)
{
    if (pilotos != NULL)
    {
        for (int i = 0; i < tam; i++)
        {
            // existe - return 0
            if (pilotos[i].id == id_car)
            {
                return 0;
            }
        }

        return 1;
    }
}

Piloto *eliminarPiloto(Piloto p[], int *tam, int idPiloto)
{
    Piloto aux;
    int j;
    if (p != NULL)
    {
        for (int i = 0; i < *tam; i++)
        {
            if (p[i].id == idPiloto)
            {
                aux = p[i];
                j = i + 1;
                while (j < *tam)
                {
                    p[j - 1] = p[j];
                    j++;
                }
                (*tam)--;
            }
        }
    }

    return p;
}