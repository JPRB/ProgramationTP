/* 
 * File:   Campeonato.h
 * Author: João Borges - a21260097
 *
 * Created on 29 de Maio de 2019, 18:34
 */

#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "Carro.h"
#include "Piloto.h"
#include "Corrida.h"

#include "utils.h"

typedef struct corrida
{
    int id; // n.º da corrida || id max = nProvas
    Corredor *corredores;
    int nVoltas;
    struct corrida *prox;
} Corridas;

typedef struct classGeral
{
    int idpiloto;
    float pontuacao;
    int nCorridas;
    struct classGeral *prox;
} RankGeral;

typedef struct championship
{
    int nProvas;
    int nProvas_realizadas;
    Corridas *corrida;
    RankGeral *rankingGeral;
} Campeonato;

RankGeral *PreencheClassGeral(Piloto *p, int tam);

Campeonato ChampionShip(Piloto *pilotos, Carro *carros, int totalPilotos, int totalCarros, int *champ, Campeonato lista);

int SaveCampeonato(char *nomeFich, Campeonato lista);

RankGeral *OrdenaRankgeral(RankGeral *lista);

void swap(RankGeral *x, RankGeral *y);

void libertaCampeonato(Campeonato c);

Campeonato ReadCampeonato(char *nomeFich);
#endif /* CAMPEONATO_H */
