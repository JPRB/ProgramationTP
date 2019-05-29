/* 
 * File:   Corrida.h
 * Author: João Borges - a21260097
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
   int ageP;
   Carro carro;
   int desistiu;
   int exp;
   int *ranking;
   int rankingTotal;
   struct corredor *prox;

} Corredor;

typedef struct 
{
   int id;
   Corredor *corredor;
   int tempo;
   //struct obj *prox;

} Rank;


void mostra_ranking_Volta(Rank r);

void mostra_ranking(Rank *r, int nVoltas);

void CriaCorrida(int *nVoltas, int *compPista, int  *nCarros);


/**
 * Atribuir de forma aleatoria um piloto a um carro
 * 
 * Recebe um piloto aleatorio, um carro aleatorio
 * 
 * @return Corredores que vão participar na corrida
 */
Corredor* AtribuiCorredores(Piloto **p, Carro **c, int totalPilotos, int totalCarros, int totalCorredores, int nVoltas);


Corredor *Insere_corredor(Corredor *corrida, Corredor *corredor);

void hmm();


void mostra_desistencias(Corredor *c, int desistencias);

void mostra_corredores(Corredor *c);

void mostra_corredores_Fora(Piloto p_disp[], int tamPil, Piloto piloto[], int ptam, Carro car[], int ctam, Carro c_disp[], int tamCar);

Rank *IniciaCorrida(Corredor *corrida, int nVoltas, int metros);


Corredor* OrderCorredores(Corredor *c, Corredor *novo);

#endif /* CORRIDA_H */

