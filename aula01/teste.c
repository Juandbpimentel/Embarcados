#include "lib.h";

int main(int argc, char const *argv[])
{
    int n = 0, size = 0;
    int *vet = NULL;
    printf("Digite quantos números quer inserir: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int aux = 0;
        printf("\n\n Número %d: ", i);
        scanf("%d", &aux);
        vet = alocacaoDinamicaDeVetor(vet, aux, &size);
    }

    showVet(vet, size);
    return 0;
}
