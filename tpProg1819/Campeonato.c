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
    Piloto *p;
    int i;
    int *campeonato, opc;

    Rank *r;
    RankGeral *classFinal, *novo, *rG;
    Corredor *aux;

    // Corridas *corrida, *aux1;
    Campeonato *camp;

    camp = malloc(sizeof(Campeonato));
    if (!camp)
    {
        fprintf(stderr, "Erro a alocar memoria\n");
        *champ = 0;
        return;
    }

    // if (*champ == 0)
    // {
    //     camp->nProvas_realizadas = 0;
    //     printf ("%d", camp->nProvas_realizadas);
    //     //camp->nProvas_realizadas = 0;
    // }

    if (*champ == 0 && (camp->nProvas = SetNumberOfProvas()) == -1)
    {
        fprintf(stderr, "Criacao de Campeonato Inválido");
        return;
    }

    *champ = 1;
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
        // corrida = malloc(sizeof(Corridas));
        // if (!corrida)
        // {
        //     fprintf(stderr, "Erro a alocar memoria\n");
        //     *champ = 0;
        //     return;
        // }

        classFinal = PreencheClassGeral(pilotos, totalPilotos);

        //c->corrida[c->nProvas_realizadas].classificacao =
        r = Correr(pilotos, carros, totalPilotos, totalCarros);

        if (!r)
        {
            return;
        }

        camp->nProvas_realizadas++;
        
        // Por cada volta, atribuir 0.5 de pontuacao se piloto nao desistiu
        for (int i = 0; i < r->nVoltas; i++)
        {
            aux = r[i].corridaOrdenada;
            if (r[r->nVoltas - 1].corridaOrdenada->desistiu == 0)
            {
                rG = classFinal;
                while (rG != NULL)
                {
                    //printf(" %d\n", rG->idpiloto);
                    if (rG->idpiloto == aux->piloto.id)
                    {
                        rG->pontuacao += 0.5;
                        printf("id %d nome piloto %s pontos: %f\n", aux->piloto.id, aux->piloto.nome, rG->pontuacao);
                    }
                    rG = rG->prox;
                }
            }
        }

        // if (lista != NULL)
        // {
        //     camp = lista;
        // }

        // camp->nProvas_realizadas++;

        // corrida->nVoltas = r->nVoltas;

        // corrida->prox = NULL;

        // while (corrida){
        //     printf ("Voltas %d\n", corrida->nVoltas);

        //     corrida = corrida->prox;
        // }

        // return;
        // if (camp->corrida->prox == NULL)
        // {
        //     camp->corrida = corrida;
        // }
        // else
        // {
        //     aux = camp->corrida;

        //     while (aux->prox != NULL)
        //     {
        //         aux = aux->prox;
        //     }
        //     aux->prox = corrida;
        // }

        // printf("Aqui");

        // printf(" %d", lista->nProvas_realizadas);
        // system("pause");
        // for (int i = 0; i < lista->nProvas_realizadas; i++)
        // {
        //     mostra_ranking(lista->corrida[i].classificacao, lista->corrida[i].nVoltas);
        // }
        //mostra_ranking(lista->corrida->classificacao, lista->corrida->nVoltas);

        // Atribuir 10 pontos de exp ao campeao
        if (camp->nProvas_realizadas == camp->nProvas)
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

int SaveCampeonato(char *nomeFich, Campeonato *lista)
{
    Corredor *c;
    RankGeral *r;
    Corridas *corridas;
    FILE *f = fopen(nomeFich, "wb");

    if (!f)
    {
        fprintf(stderr, "Impossivel abrir o ficheiro");
        fclose(f);
        return -1;
    }

    // n de provas
    fwrite(&lista->nProvas, sizeof(int), 1, f);

    // n de provas realizadas
    fwrite(&lista->nProvas_realizadas, sizeof(int), 1, f);

    r = lista->rankingGeral;

    while (r)
    {

        fwrite(&r->idpiloto, sizeof(int), 1, f);
        fwrite(&r->pontuacao, sizeof(int), 1, f);

        r = r->prox;
    }

    // corridas = lista->corrida;

    // while (corridas)
    // {

    //     fwrite(&corridas->id, sizeof(int), 1, f);
    //     fwrite(&corridas->nVoltas, sizeof(int), 1, f);

    //     c = corridas->corredores;
    //     while (c)
    //     {
    //         fwrite(&c, sizeof(Corredor), 1, f);
    //         c = c->prox;
    //     }

    //     //r = corridas->classificacao;
    //     c = r[r->nVoltas - 1].corridaOrdenada;

    //     while (c)
    //     {
    //         fwrite(&c, sizeof(Corredor), 1, f);
    //         c = c->prox;
    //     }

    //     corridas = corridas->prox;
    // }
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

RankGeral *PreencheClassGeral(Piloto *p, int tam)
{

    RankGeral *classArray = NULL, *novo;

    for (int i = 0; i < tam; i++)
    {

        novo = malloc(sizeof(RankGeral));
        if (!novo)
        {
            fprintf(stderr, "Erro a alocar memoria\n");
            return NULL;
        }

        novo->idpiloto = p[i].id;
        novo->pontuacao = 0.0;
        novo->prox = NULL;

        novo->prox = classArray;
        classArray = novo;
    }
    return classArray;
}
