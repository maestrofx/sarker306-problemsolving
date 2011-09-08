#include<stdio.h>

int main()
{
    long n;
    
    while(scanf("%ld", &n)!=EOF)
    {
        if(n>7 && n<14)
        {
            switch(n)
            {
                case 8: printf("40320"); break;
                case 9: printf("362880"); break;
                case 10: printf("3628800"); break;
                case 11: printf("39916800"); break;
                case 12: printf("479001600"); break;
                case 13: printf("6227020800"); break;
            }
        }
        else if(n<8 && n>=0) printf("Underflow!");
        else if(n>13 || n%2) printf("Overflow!");
        else printf("Underflow!");
        printf("\n");
    }
    
    return 0;
}
