#include "lib.h";

int *alocacaoDinamicaDeVetor(int *vet, int val, int *size)
{
    if (vet == NULL)
    {
        vet = (int *)malloc(sizeof(int));
        vet[*size] = val;
        *size += 1;
        return vet;
    }
    else
    {
        vet = (int *)realloc(vet, sizeof(int) * (*size) + 1);
        vet[*size] = val;
        *size += 1;
        return vet;
    }
}

void showVet(int *vet, int size)
{
    printf("\n\n [ ");
    for (int i = 0; i < size - 1; i++)
    {
        printf("%d , ", vet[i]);
    }
    printf("%d ]\n", vet[size - 1]);
}