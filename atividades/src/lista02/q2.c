#include <stdio.h>
#include <stdlib.h>

#define NUM_BIT_SIZE 8

long int* splitNumber(unsigned long int number, long int* nums){
    int i=7;

    while(i>=0 && number!=0){
        nums[i] = (number & 15);
        number= number>>4;
        i--;
    }

    return nums;
}

int main(){
    unsigned long int num = 0;
    printf("Insert a number: ");
    scanf("%ld",&num);
    printf("\nThe number %ld becomes the following numbers:\n",num);
    long int nums[8];
    for (size_t i = 0; i < 8; i++){
        nums[i]=0;
    }
    
    splitNumber(num,nums);
    for (int i = 7, n=0; i >= 0; i--,n++){
        printf("Number %d: %ld\n",(n+1),nums[i]);
    }
    
    return 0;
}