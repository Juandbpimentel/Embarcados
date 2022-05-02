#include <stdio.h>
#include "funcoes.h"

int iNum1, iNum2;

int main(int argc, char *argv[])
{

#ifdef DEBUG

    printf("\n\nteste %d\n\n", MAX(10, 4));

#endif

    iNum1 = 10;
    iNum2 = 9;
    printf("%0.2f \n\n", media((float)iNum1, (float)iNum2));
    return 0;
}