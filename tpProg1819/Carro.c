
#include <stdio.h>
#include <stdlib.h>
#include "Carro.h"


//Carro

Carro* ReadCarros(int *tam) {
    FILE *f_cars;
    Carro *carros, carro;

    f_cars = fopen("Carros.txt", "r");

    //Se for null Erro no acesso
    if (f_cars == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        *tam = 0;
        return NULL;
    }

    carros = malloc(sizeof (Carro));

    //Se não conseguir alocar memória..
    if (carros == NULL) {
        printf("Erro na alocacao de memoria\n");
        return NULL;
    } else {

        //While not find end-of-File of carros
        while (!feof(f_cars)) {
            if (fscanf(f_cars, " %d %d %d", &carro.id, &carro.potencia, &carro.avariado) == 3) {

                carros = AdicionaCarro(carros, carro, tam);


            } else {
                *tam = 0;
                printf("Erro a ler Carros!\n");
                return NULL;
            }
        }
    }


    fclose(f_cars);

    return carros;
}

Carro* AdicionaCarro(Carro carros[], Carro newCarro, int *tam) {
    Carro *aux;
    int new_size = (*tam + 1);

    aux = realloc(carros, new_size * sizeof (Carro));

    if (aux == NULL)
        return carros;

    carros = aux;

    //incrementar o tamanho
    (*tam)++;
    //Associar novo carro para o array de Carros
    carros[*tam - 1] = newCarro;

    return carros;
}

void MostraCarros(Carro *carro, int tam) {

    printf("+------+-----------+-----------+\n"
            "|  ID  | Potência |  Avariado |\n"
            "+------+-----------+-----------+\n");
    for (int i = 0; i < tam; i++) {
        printf("| %-4d | %-9d | %-9d |\n",
                carro[i].id, carro[i].potencia, carro[i].avariado);
    }

    printf("+------+-----------+-----------+\n");
    getchar();
    getchar();
}

int SaveCarros(Carro carros[], int tam) {

     FILE *fcarros;
    Carro *c;

    fcarros = fopen("CarrosTest.txt", "w");


    if (fcarros == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        //*tam = 0;
        return -1;
    }

    for (c = carros; c < (carros + tam); c++) {
        fprintf(fcarros, "%d  %d  %d\n\n", c->id, c->potencia, c->avariado);
    }


    fclose(fcarros);

    return 0;
}