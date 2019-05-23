/* 
 * File:   .h
 * Author: João Borges - a21260097
 *
 * 
 */

#ifndef Carro_H
#define Carro_H

typedef struct {
    int id; //unico
    int potencia;
    int avariado; //int? 0 avariado, 1 nAvariado? - Quando avariado (impedimento +1)
} Carro;


//Carro

//Ler carros do ficheiro para memória

Carro* ReadCarros(int *tam);

Carro* AdicionaCarro(Carro carros[], Carro newCarro, int *tam);

//-------------- Ler carros do ficheiro para memória ---------------//


void MostraCarros(Carro carro[], int tam);

int SaveCarros(Carro carros[], int tam);


/*
 * @param c - vetor de Carros
 *  
 * @param tam - tamanho do vetor
 * 
 * @param id - Id do carro
 * 
 * @return c - carro se existir id, senão ñ retorna nada.
 */
Carro GetCarByID(Carro c[], int tam, int id);


Carro *SetAvaria(Carro c[], int tam, int id);

/*
 * @param c - vetor de Carros
 *  
 * @return 0 = com avaria, 1 sem avaria
 */
int GetCarro_SAvaria(Carro c);

void MaxMinIDCarros(Carro c[], int tam, int *min, int *max);

Carro *CarrosDisponiveis(Carro *c, int totalcarros, int *carros_disponiveis_conta);

/*
 * Verificar se exist ID nos Carros disponiveis
 * 
 * @param c - vetor de Carros
 *  
 * @return 0 = existe, 1 Ñ existe.
 */
int ExistCar (Carro pilotos_disponiveis[], int carros_disponiveis_conta, int id_car);


Carro *eliminarCarro(Carro carro[], int *tam, int idCar);


#endif /* Carro_H */

