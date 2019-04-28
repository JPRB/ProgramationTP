/* 
 * File:   piloto.h
 * Author: João Borges
 *
 * Created on 21 de Março de 2019, 15:57
 */

#ifndef PILOTO_H
#define PILOTO_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Date;

typedef struct {
    char nome[100];
    int id; // garantir que é unico
    Date dataNasc;
    int peso; //inteiro? .. > 0
    float exp; //Experiencia 0.0 quando Novo
    int impedimento; //contador
} Piloto;


//void menuPiloto();

/**
 * Lê Piloto do ficheiro para memória
 * 
 * @param tam - Ponteiro para o tamanho de pilotos
 * @return 
 */
Piloto* ReadPilotos(int *tam);


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
 * Print de 1 piloto e as suas carateristicas
 * ´
 * @param piloto
 */
void MostraPiloto(Piloto piloto);

//Carro *GetImpedimento(Carro *car, int totalCar, int id);



int GetImpedimento(int valorImpedimento, int idPiloto);

/**
 * 
 * @param piloto - Vetor de Pilotos
 * @param valorImpedimento - Valor atribuido "automaticamente"
 * ou pelo utilizador 
 * 
 * @param idPiloto - Id do piloto a atribuir a penalização
 * @param totalPilotos - Total de Pilotos
 */
void SetImpedimento(Piloto *piloto, int valorImpedimento, int idPiloto, int totalPilotos);




Piloto *GetPiloto(Piloto *piloto, int idPiloto, int totalPilotos);

#endif /* PILOTO_H */

