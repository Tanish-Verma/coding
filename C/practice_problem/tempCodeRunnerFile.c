#include <stdio.h>
#include <math.h>

int main()
{
    long int result = 0;

    int s = 0;
    int ispalindrome = 0;
    int start, stop;
    scanf("%d %d", &start, &stop);
    while (s != 1)
    {
        for (int i = stop; i >= start; i--)
        {
            int temp = i, count, reverse = 0;
            while (temp != 0)
            {
                temp /= 10;
                count++;
            }
            temp = i;
            for (int j = 0; j < count; j++)
            {
                int k = temp % 10;
                reverse = reverse * 10 + k;
                temp /= 10;
            }
            if (reverse == i)
            {
                int isprime=1;
                for (int k = 2; k < i; k++)
                {
                    if (i % k == 0)
                        isprime = 0;
                }
                if (isprime)
                {
                    result = i;
                    s = 1;
                }
                else if (i == start)
                {
                    printf("There was no such palindrome.");
                    s = 1;
                }
            }
        }
    }
    printf("The prime palindrome is %d", result);
    return 0;
}