/* 
 * File:   Campeonato.h
 * Author: João Borges - a21260097
 *
 * Created on 29 de Maio de 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Campeonato.h"

int SetNumberOfProvas()
{

    int nProvas;

    nProvas = -1;

    do
    {
        printf("Numero de Provas a realizar (3-8): ");
        nProvas = readInt();
    } while (nProvas < 3 || nProvas > 8);

    return nProvas;
}

void ChampionShip(Piloto *pilotos, Carro *carros, int totalPilotos, int totalCarros, int *champ, Campeonato *lista)
{

    // int nVoltas, compPista, nCarros;

    int *campeonato, opc;
    Rank *r;
    Corridas *corrida;
    *champ = 1;

    if (*champ == 0 && (lista->nProvas = SetNumberOfProvas()) == -1)
    {
        fprintf(stderr, "Criacao de Campeonato Inválido");
        return;
    }

    printf(" 1 - Realizar Corrida\n");
    printf(" 2 - Sair de Campeonato\n");

    do
    {
        printf("Escolha uma opc: ");
        opc = readInt();

    } while (opc > 2 || opc <= 0);

    switch (opc)
    {

    case 1:
        corrida = malloc(sizeof(Corridas));
        if (!corrida)
        {
            fprintf(stderr, "Erro a alocar memoria\n");
            *champ = 0;
            return;
        }

        //c->corrida[c->nProvas_realizadas].classificacao =
        r = Correr(pilotos, carros, totalPilotos, totalCarros);
        lista->nProvas_realizadas++;
        printf("aqui!\n");

        // if (!c->corrida[c->nProvas_realizadas].classificacao)
        // {
        //     fprintf(stderr, "Erro!");
        //     return;
        // }
        //c->corrida->nVoltas = c->corrida->classificacao->nVoltas;

        printf(" %d", lista->nProvas_realizadas);
        corrida->classificacao = r;

        lista->corrida->prox = NULL;
        if (lista->corrida == NULL){
            lista->corrida = corrida;
        }

        // Atribuir 10 pontos de exp ao campeao
        if (lista->nProvas_realizadas == lista->nProvas)
        {
            *champ = 0;
        }
        break;

    case 2:
        break;
    }

    // printf("nVoltas %d", camp.corrida->classificacao->nVoltas);
    // camp.corrida->nVoltas = camp.corrida->classificacao->nVoltas;

    // printf("Classificacao aqui!");
    //mostra_ranking_Volta(camp.corrida->classificacao);
}

int SaveCampeonato(char *nomeFich, Campeonato lista)
{
    Corredor *c;
    Rank *r;
    Corridas *corridas;
    FILE *f = fopen(nomeFich, "wb");

    if (!f)
    {
        fprintf(stderr, "Impossivel abrir o ficheiro");
        fclose(f);
        return -1;
    }

    // n de provas
    fwrite(&lista.nProvas, sizeof(int), 1, f);

    // n de provas realizadas
    fwrite(&lista.nProvas_realizadas, sizeof(int), 1, f);

    corridas = lista.corrida;

    while (corridas)
    {

        fwrite(&corridas->id, sizeof(int), 1, f);
        fwrite(&corridas->nVoltas, sizeof(int), 1, f);

        c = corridas->corredores;
        while (c)
        {
            fwrite(&c, sizeof(Corredor), 1, f);
            c = c->prox;
        }

        r = corridas->classificacao;
        c = r[r->nVoltas - 1].corridaOrdenada;

        while (c)
        {
            fwrite(&c, sizeof(Corredor), 1, f);
            c = c->prox;
        }

        corridas = corridas->prox;
    }
    // fwrite(&lista->idade, sizeof(int), 1, f);

    // fwrite(lista->nome, sizeof(char), strlen(lista->nome), f);

    // fwrite(&lista->nresp, sizeof(int), 1, f);

    // p = lista->dados;
    // while (p)
    // {
    //     fwrite(&p->d, sizeof(info), 1, f);
    //     p = p->prox;
    // }
    // lista = lista->prox;

    return 0;
}
