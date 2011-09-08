#include<stdio.h>
#include<string.h>

#define SIZE 250

int main()
{
    char code[SIZE];
    int i, n;
    
    while(gets(code))
    {
        if(code[0]>='0' && code[0]<='9')
        {
            /*decode*/
            i=strlen(code);
            for(;i;)
            {
                n=code[--i]-'0';
                if(i) n=10*n+code[--i]-'0';
                if(n<32 && i) n=10*n+code[--i]-'0';
                printf("%c", n);
            }
            printf("\n");
        }
        else
        {
            /*encode*/
            i=strlen(code);
            for(;i;)
            {
                n=code[--i];
                while(n)
                {
                    printf("%d", n%10);
                    n/=10;
                }
            }
            printf("\n");
        }
    }
    return 0;
}
