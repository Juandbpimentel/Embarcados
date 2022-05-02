#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#define NUM_BIT_SIZE 32

void printBinary(unsigned long int num, int n){    
    char string[n];
    printf("\n");
    int i=n-1;
    while(i>=0){
        string[i] = ((num&1)+'0');
        num >>= 1;
        i--;
    }
    for (size_t i = 0; i < n; i++){
        printf("%c",string[i]);
    }
    

}


unsigned long int setBits(int boolean, unsigned long int i, unsigned long int j, unsigned long int value){
    unsigned long int outputValue=0, aux=0;
        for(int k = 0; k<32; k++){
            if(k>0)aux <<= 1;
            aux |= (value & 1);
            value>>=1;
        }

        char output[NUM_BIT_SIZE];
        printBinary(aux,NUM_BIT_SIZE);
        printf("\n%ld\n",aux);

        char output2[NUM_BIT_SIZE];
        for(int k = NUM_BIT_SIZE-1; k>=0; k--){
            printBinary(outputValue,NUM_BIT_SIZE);
            printf("\n%lx\n",outputValue);

            if(k>0){outputValue <<= 1;}
            if (k>=i && k<=j){
                outputValue |= boolean;
            }else{
                outputValue |= ((aux & 1) == 1 ?1:0);
            }
            aux>>=1;
            
        }

}

int main(){
    unsigned long int num = 0 ;

    //printf("Insert the binary number: ");
    //scanf(" %ld", &num);
    setBits(1,0,1,1);
    //char output[NUM_BIT_SIZE];
    
    //printf("The number after shift is this: %s\n", output);
    //printf("%s", "\n");
    
    return 0;
}