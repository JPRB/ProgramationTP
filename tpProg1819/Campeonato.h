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


typedef struct corrida {
    int id; // n.º da corrida || id max = nProvas
    Corredor *corredores;
    int nVoltas;
    struct corrida *prox;
} Corridas;

typedef struct classGeral {
    int idpiloto;
    float pontuacao;
    struct classGeral *prox;
} RankGeral;

typedef struct championship {
    int nProvas;
    int nProvas_realizadas;
    Corridas *corrida;
    RankGeral *rankingGeral;
} Campeonato;




RankGeral *PreencheClassGeral(Piloto *p, int tam);

void ChampionShip(Piloto *pilotos, Carro *carros, int totalPilotos, int totalCarros, int *champion, Campeonato *c);


int SaveCampeonato(char *nomeFich, Campeonato *lista);

#endif /* CAMPEONATO_H */

