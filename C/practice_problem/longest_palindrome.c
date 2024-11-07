#include <stdio.h>
#include <stdlib.h>


int main(){
    printf("Enter the string: ");
    char c;
    char * str=(char*)malloc(sizeof(char));
    int k=0;
    while((c=getchar()!='\n' || c!=' ' || c!=EOF)){
        str[k]=c;
        str=(char*)realloc(str,k+2);
        k++;
    }   
    printf("%s",str); 
    return 0;
}