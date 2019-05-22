/* 
 * File:   Corrida.h
 * Author: João Borges
 *
 * Created on 21 de Março de 2019, 16:29
 */

#ifndef CORRIDA_H
#define CORRIDA_H

#include "Carro.h"
#include "Piloto.h"
#include "utils.h"

typedef struct corredor {

   int id;
   Piloto piloto;
   Carro carro;
   int quit;
   int nVoltas;
   struct corredor *prox;

} Corredor;


void CriaCorrida(int *nVoltas, int *compPista, int  *nCarros);


/**
 * Atribuir de forma aleatoria um piloto a um carro
 * 
 * Recebe um piloto aleatorio, um carro aleatorio
 * 
 * @return Corredores que vão participar na corrida
 */
Corredor* AtribuiCorredores(Piloto **p, Carro **c, int totalPilotos, int totalCarros, int totalCorredores);


Corredor *Insere_corredor(Corredor *corrida, Corredor *corredor);


void mostra_corredores(Corredor *c);

void mostra_corredores_Fora(Piloto p_disp[], int tamPil, Piloto piloto[], int ptam, Carro car[], int ctam, Carro c_disp[], int tamCar);

#endif /* CORRIDA_H */

