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



void UpdateFileCarros();


#endif /* Carro_H */

