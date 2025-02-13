#include <stdio.h>
int a, b, c = 0;
void prtFun(void);
main( )
{ 
   static int a = 1; /* Line 1 */
   prtFun();
   a += 1;
   prtFun();
   printf("\n %d %d ", a, b);
}
void prtFun(void)
{ 
   static int a=2;   /* Line 2 */
   int b=1;
   a+= ++b;
   printf("\n %d %d ", a, b);
}