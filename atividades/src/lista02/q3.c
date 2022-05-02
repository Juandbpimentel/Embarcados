#include <stdio.h>
#include <stdlib.h>

#define NUM_BIT_SIZE 8

void binaryToStr(unsigned long int num, char* output, int n){    
    int i=n-1;
    unsigned long int vet[n];
    while(i>=0){
        output[i]=(num&1)+'0';
        num = num>>1;
        i--;
    }

}

unsigned long int countHighBits(unsigned int number, int n){
    int count = 0, i = 0;
    
    while(i<n){
        if((number&1) == 1){
            count++;
        }
        number = number>>1;
        i++;
    }

    return count;
}

unsigned long int shiftToLftEnd(unsigned long int num, int n){
    int zeros = n - countHighBits(num,n), i = 0;
    if(num>255)return 0;
    unsigned long int shiftedNum=0;//3 uns 
    //101
    for (int i = 0; i < n; i++){
        if (i>0) shiftedNum <<= 1;
        shiftedNum |=1 ;
    }
    for(int i = 0; i<zeros ; i++){
        shiftedNum <<= 1;
    }

    return shiftedNum;
}

int main(){
    unsigned int num =0;

    //printf("Insert the binary number: ");
    scanf(" %d", &num);

    char output[NUM_BIT_SIZE];
    binaryToStr(shiftToLftEnd(num, NUM_BIT_SIZE),output,NUM_BIT_SIZE);
    
    //printf("The number after shift is this: %s\n", output);
    printf("%s", output);
    
    return 0;
}