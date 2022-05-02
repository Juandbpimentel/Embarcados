#ifndef TESTE_H_
#define TESTE_H_
    #include <stdio.h>
    #include <stdlib.h>
    float media(float n1, float n2);
    #define SQR(x) ((x) * (x))
    #define MAX(A, B) ((A) > (B) ? (A) : (B))
    #define RECIPROCAL(number) (1.0 / (number))
    void binaryToStr(unsigned long int num, char* output, int n);
    unsigned long int strToBinaryInt(char* str, int n);
#endif // TESTE_H_