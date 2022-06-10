#include "funcoes.h"

float media(float n1, float n2)
{
    return (n1 + n2) / 2;
}

void binaryToStr(unsigned long int num, char* output, int n){    
    int i=n-1;
    printf("\n");
    while(i>=0){
        output[i]=((num&1)+'0');
        num >>= 1;
        i--;
    }

}

unsigned long int strToBinaryInt(char* str, int n){
    unsigned long int number =0;
    for (int i = 0; i < n; i++){
        if (i>0) number <<= 1;
        
        if(str[i] == '1'){
            number |=1;
        }
    }

    return number;
}