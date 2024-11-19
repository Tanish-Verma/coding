#include <stdio.h>


void printbytes(long long int N){
    long long int c=1<<31;
    printf("%lld = ",N);
    for(int i=1;i<=32;i++){
        putchar(c&N?'1':'0');
        N<<=1;
        if(i%8==0){
            printf(" ");
        }
    }
    printf("\n");
}

int main(){
    long long int N;
    if(scanf("%lld",&N)==0){
        printf("Input Failed");
    }
    long long int result,C=1<<31;
    
    for(int i=0;i<32;i++){
        result=N&C;
        result>>=1;
        N<<=1;
    }
    printf("%lld\n",result);
    printbytes(result);
    return 0;
}