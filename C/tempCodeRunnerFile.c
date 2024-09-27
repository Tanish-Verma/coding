//Chat gpt version

// #include <stdio.h>
// #include <math.h>

// int main(){
//     unsigned long long int l=1;
//     unsigned long long int n,temp=0,result=0;
//     unsigned long long int k,count=0; // Adjust k to also be unsigned long long
//     scanf("%llu %llu",&n,&k);

//     for(int i=0;i<k;i++) l *= 10;
//     printf("%llu\n",l);  // Correct format specifier for l

//     unsigned long long int multiplier=1;  // Also use long long for multiplier
//     while(n != 0){
//         temp = n % l;
//         printf(" %llu\n", temp);  // Correct format specifier for temp
//         temp = temp + temp % 10;
//         if(temp >= l) temp %= l;
//         result += temp * multiplier;
//         // printf("Current result: %llu\n", result);  // Correct format specifier for result
//         count++;
//         multiplier *= l;
//         n /= l;
//     }

//     printf("%lu\n",count);
//     printf("%llu\n", result);  // Final output for result
//     return 0;
// }
