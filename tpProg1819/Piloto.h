/* 
 * File:   piloto.h
 * Author: João Borges - a21260097
 *
 * Created on 21 de Março de 2019
 */

#ifndef PILOTO_H
#define PILOTO_H

typedef struct Date
{
    int dia;
    int mes;
    int ano;
} Date;

typedef struct
{
    char nome[100];
    int id; // garantir que é unico
    Date dataNasc;
    int peso;        //inteiro? .. > 0
    float exp;       //Experiencia 0.0 quando Novo
    int impedimento; //contador
} Piloto;

//void menuPiloto();

/**
 * Lê Piloto do ficheiro para memória
 * 
 * @param tam - Ponteiro para o tamanho de pilotos
 * @return 
 */
Piloto *ReadPilotos(int *tam);

/**
 * 
 * @param pilotos - Ponteiro para vetor de pilotos existente
 * @param newPiloto - Piloto novo
 * @param tam - Tamanho de elementos dos pilotos lidos
 * @return Ponteiro Para Array de Pilotos
 */
Piloto *AdicionaPiloto(Piloto pilotos[], Piloto newPiloto, int *tam);

int SavePilotos(Piloto pilotos[], int tam);

/**
 * Print de todos os Pilotos e as suas carateristicas
 * 
 * @param piloto - Vetor de pilotos
 * @param tam - Tamanho do vector de pilotos
 */
void MostraPilotos(Piloto piloto[], int tam);

/**
 * Mostra todas as carateristicas de 1 Piloto
 * ´
 * @param piloto
 */
void MostraPiloto(Piloto piloto);

//Carro *GetImpedimento(Carro *car, int totalCar, int id);

int GetImpedimento(int valorImpedimento, int idPiloto);

/**
 * 
 * @param piloto - Vetor de Pilotos
 * 
 * @param idPiloto - Id do piloto a atribuir a penalização
 *
 *  @param valorImpedimento - Valor atribuido "automaticamente"
 * ou pelo utilizador 
 *
 * @param totalPilotos - Total de Pilotos
 */
Piloto *SetImpedimento(Piloto *piloto, int idPiloto, int valorImpedimento, int totalPilotos);

Piloto GetPilotoByID(Piloto *piloto,int totalPilotos, int id);

/*
 *  @param p - vetor de pilotos
 *  
 *  @param tam - tamanho do vetor p, de pilotos
 *  
 *  @param *min - ponteiro com a referencia para o min id que existe nos pilotos
 * 
 *  @param *max - ponteiro com a referencia para o max id que existe nos pilotos
 * 
 *  @return *min, *max - Devolve como referência
 */
void MaxMinIDPilotos(Piloto p[], int tam, int *min, int *max);


/*
 * @param piloto - vetor de pilotos
 * 
 * @param tam - tamanho do array de pilotos
 * 
 * @param *totalPilotos - total de pilotos que vão correr
 * 
 * @return 0 = com impedimentos, 1 sem impedimento
 */
int GetPiloto_Simpedimento(Piloto piloto);

Piloto *PilotosDisponiveis(Piloto *p, int totalPilotos, int *pilotos_disponiveis_conta);


/*
 * Verificar se existe ID no vetor de pilotos
 * 
 * @param pilotos - vetor de Pilotos
 *  
 * @return 0 = existe, 1 Ñ existe.
 */
int ExistPiloto(Piloto pilotos[], int tam, int id_car);


Piloto *eliminarPiloto(Piloto p[], int *tam, int idPiloto);


int GetPilotoAge(Piloto p);

#endif /* PILOTO_H */
