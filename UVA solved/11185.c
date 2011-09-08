#include<stdio.h>

#define SIZE 23

int main()
{
    long n;
    int i;
    char array[SIZE];
    while(scanf("%ld", &n)==1&& n>=0)
    {
        i=0;
        do
        {
            array[i++]=n%3+'0';
            n/=3;
        }while(n);
        for(--i;i+1;i--) printf("%c", array[i]);
        printf("\n");
    }
    return 0;
}
