/* 
 * File:   Corrida.h
 * Author: João Borges - a21260097
 *
 * Created on 21 de Março de 2019, 16:29
 */

#ifndef CORRIDA_H
#define CORRIDA_H

#include "utils.h"
#include "Carro.h"
#include "Piloto.h"



typedef struct corredor {
   int id;
   Piloto piloto;
   int ageP;
   Carro carro;
   int desistiu;
   float exp;
   int *ranking;
   int rankingTotal;
   struct corredor *prox;

} Corredor;

typedef struct 
{
   int id;
   Corredor *corridaOrdenada;
   int nVoltas;
} Rank;




void mostra_ranking_Volta(Rank r);

void mostra_ranking(Rank *r, int nVoltas);

Rank *Correr(Piloto *pilotos, Carro *carros, int tamPiloto, int tamCarro);

void CriaCorrida(int *nVoltas, int *compPista, int  *nCarros);

/**
 * Atribuir de forma aleatoria um piloto a um carro
 * 
 * Recebe um piloto aleatorio, um carro aleatorio
 * 
 * @return Corredores que vão participar na corrida
 */
Corredor* AtribuiCorredores(Piloto *p, Carro *c, int totalPilotos, int totalCarros, int totalCorredores, int nVoltas);

void SetImpAvar(Piloto **p, Carro **c, int totalPilotos, int totalCarros);

Rank *IniciaCorrida(Corredor *corrida, int nVoltas, int metros);

Corredor *Insere_corredor(Corredor *corrida, Corredor *corredor);

void mostra_desistencias(Corredor *c, int desistencias);

void mostra_corredores(Corredor *c);

void mostra_corredores_Fora(Piloto p_disp[], int tamPil, Piloto piloto[], int ptam, Carro car[], int ctam, Carro c_disp[], int tamCar);

//Rank *IniciaCorrida(Corredor **corrida, int nVoltas, int metros);

Corredor* OrderCorredoresByRank(Corredor *c, Corredor *novo);

void AtualizaCorredores(Piloto **p, Rank *rank, int totalp);

#endif /* CORRIDA_H */

