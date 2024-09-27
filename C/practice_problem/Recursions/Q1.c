#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 10
#define MIN_LENGTH 1

void swap(char arr[],int i,int j){
    char temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
long int factorial(int n){
    int k=1;
    for(int i=2;i<=n;i++){
        k*=i;
    }
    return k;
}


void generatepermutations(int lenght,char arr[lenght],int start,int stop,char result[][lenght+1]){
    static int index=0;
    if(start==stop){
        int i;
        for(i=0;i<=stop;i++){
            result[index][i]=arr[i];
        }
        result[index][stop+1]='\0';
        // printf("%s\n",arr);
        index++;


    }
    else{
        for(int i=start;i<=stop;i++){
            if(arr[start]==arr[i] && i!=start)continue;
            swap(arr,start,i);
            generatepermutations(lenght,arr,start+1,stop,result);
            swap(arr,start,i);
        }
    }
}

int main(){
    char string[MAX_LENGTH+1];
    scanf("%10s",string);
    int k=strlen(string);
    char result[factorial(k)][k+1];
    generatepermutations(k,string,0,k-1,result);
    for(int i=0;i<factorial(k);i++){
        printf("%s\n",result[i]);
    }
    return 0;
}