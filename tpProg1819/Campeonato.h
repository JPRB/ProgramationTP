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
    Rank *classificacao;
    int nVoltas;
    struct corrida *prox;
} Corridas;

typedef struct championship {
    int nProvas;
    int nProvas_realizadas;
    Corridas *corrida;
} Campeonato;




void ChampionShip(Piloto *pilotos, Carro *carros, int totalPilotos, int totalCarros, int *champion, Campeonato *c);


int SaveCampeonato(char *nomeFich, Campeonato lista);

#endif /* CAMPEONATO_H */

