#include<stdio.h>
#include<stdbool.h>
#define SIZE 10000
int main()
{
    char div[SIZE];
    int i, d;
    unsigned long div2, rem;
    char op[2];
    bool zeroflag;
    while(scanf("%s%s%lu", div, op, &div2)==3)
    {
        zeroflag=false;
        rem=0;
        if (op[0]=='/')
        {
            for(i=0;div[i]!='\0';i++)
            {
                rem=10*rem+div[i]-'0';
                d=rem/div2;
                if(zeroflag) printf("%d", d);
                else if (d)
                {
                    printf("%d", d);
                    zeroflag=true;
                }
                rem%=div2;
            }
            if (!zeroflag) printf("0");
            printf("\n");
        }
        else
        {
             for(i=0;div[i]!='\0';i++)
                rem=(10*rem+div[i]-'0')%div2;
            printf("%lu\n", rem);
        }
    }
    return 0;
}
