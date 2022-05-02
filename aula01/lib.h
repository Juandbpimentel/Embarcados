#ifndef TESTE_H_
#define TESTE_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *prox;
} Node;

int *alocacaoDinamicaDeVetor(int *vet, int val, int *size);

void showVet(int *vet, int size);

#endif // TESTE_H_