#include <stdio.h>

int countHighBits(unsigned int number){
    int count = 0,i=1;
    while(i<=number){
        if((number&i) == i){
            count++;
        }
        i*=2;
    }

    return count;
}

int main(){
    unsigned int num = 0;
    printf("Insert a number: ");
    scanf("%d",&num);
    printf("\nThe number %d has %d bits in setteds\n",num,countHighBits(num));
    return 0;
}