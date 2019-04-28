#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Piloto.h"


//void menuPiloto(){
//    
//}

Piloto* ReadPilotos(int *tam) {

    FILE *fpiloto;
    Piloto *pilotos, piloto;

    fpiloto = fopen("Pilotos.txt", "r");


    if (fpiloto == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        *tam = 0;
        return NULL;
    }

    //Memory alocated to Piloto Size
    pilotos = (Piloto *) malloc(sizeof (Piloto));

    if (pilotos == NULL) {
        printf("Erro na alocacao de memoria\n");
        fclose(fpiloto);
        return NULL;
    } else {

        //While not find end-of-File
        while (!feof(fpiloto)) {
            //printf("\n \n -------- Tamanho do array: %d  \t \t %d--------- \n", *tam, feof(fpiloto));

            if (fscanf(fpiloto, "%99[^\n] %d %d %d %d %d %f %d ", piloto.nome, &piloto.id, &piloto.dataNasc.dia,
                    &piloto.dataNasc.mes, &piloto.dataNasc.ano, &piloto.peso, &piloto.exp, &piloto.impedimento) == 8) {

                pilotos = AdicionaPiloto(pilotos, piloto, tam);
            } else {
                printf("Erro a ler Pilotos!\n");
                *tam = 0;
                free(pilotos);
                fclose(fpiloto);
                return NULL;
            }

        }
    }

    fclose(fpiloto);

    return pilotos;
}

Piloto* AdicionaPiloto(Piloto pilotos[], Piloto newPiloto, int *tam) {
    Piloto *aux;
    int new_size = (*tam + 1);

    aux = realloc(pilotos, new_size * sizeof (Piloto));

    if (aux == NULL) {
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

void MostraPilotos(Piloto piloto[], int tam) {

    printf("+--------------------------------------+-------------+---------------------+"
            "--------+--------------+-------------+\n"
            "|                Nome                  |      ID     |  Data de nascimento "
            "|  Peso  | Experiencia  | Impedimento |\n"
            "+--------------------------------------+-------------+---------------------"
            "+--------+--------------+-------------+\n");

    for (int i = 0; i < tam; i++) {
        printf("| %-36s | %-11d | %.2d/%.2d/%-13d | %-6d | %-12.1f | %-10d |\n",
                piloto[i].nome, piloto[i].id, piloto[i].dataNasc.dia, piloto[i].dataNasc.mes,
                piloto[i].dataNasc.ano, piloto[i].peso, piloto[i].exp, piloto[i].impedimento);
    }

    printf("+--------------------------------------+-------------+---------------------+"
            "------------+--------------+-------------+\n");

    //     rpintf("Size: %d Tam: %d", sizeof(piloto), tam);
}

void MostraPiloto(Piloto piloto) {
    printf(" Nome: %s \t Id: %d \t Data de nascimento: %d/%d/%d \t Peso: %d \t Exp: %.2f \t Imp: %d \n",
            piloto.nome, piloto.id, piloto.dataNasc.dia, piloto.dataNasc.mes,
            piloto.dataNasc.ano, piloto.peso, piloto.exp, piloto.impedimento);

}

int SavePilotos(Piloto pilotos[], int tam) {

    FILE *fpiloto;
    Piloto *p;

    fpiloto = fopen("PilotosTest.txt", "w");


    if (fpiloto == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        //*tam = 0;
        return -1;
    }

    for (p = pilotos; p < (pilotos + tam); p++) {
        fprintf(fpiloto, "%s\n%d %d %d %d %d %.1f %d\n\n", p->nome, p->id, p->dataNasc.dia,
                p->dataNasc.mes, p->dataNasc.ano, p->peso, p->exp, p->impedimento);
    }
    /*
        while (tam--) {
            /*
                    fprintf(fpiloto, "%99[^\n] %d %d %d %d %d %f %d ", pilotos->nome, pilotos->id, pilotos->dataNasc.dia,
                                pilotos->dataNasc.mes, pilotos->dataNasc.ano, pilotos->peso, pilotos->exp, pilotos->impedimento);
     */


    fclose(fpiloto);

    return 0;
}

/*Carro *GetImpedimento(Carro *car, int totalCar, int id) {

    for (int i = 0; i < totalCar; i++)
        if (car[i]->id == id)
            return car[i];

    return 0;
}*/


//int getImpedimento(Piloto *piloto, int totalPilotos, int idPiloto) {
//
//    for (int i = 0; i < totalPilotos; i++) {
//        if (piloto[i].id == idPiloto) {
//            return piloto[i].impedimento;
//        }
//    }
//    return -1;
//}

void SetImpedimento(Piloto *p, int valorImpedimento, int idPiloto, int totalPilotos) {
    Piloto *piloto;

    piloto = GetPiloto(p, idPiloto, totalPilotos);

    if (piloto != NULL) {
        piloto->impedimento += valorImpedimento;
    } else {
        printf("Piloto não encontrado!");
    }
}

Piloto *GetPiloto(Piloto *piloto, int idPiloto, int totalPilotos) {

    for (int i = 0; i < totalPilotos; i++) {
        if (piloto[i].id == idPiloto) {
            return piloto + i;
        }
    }

    return NULL;
}