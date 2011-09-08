#include<stdio.h>

int main()
{
    char ch;
    unsigned long num=0;
    int g;
    while(ch=getchar())
    {
        while(ch!='\n') 
        {
            num+=ch-'0';
            ch=getchar();
        }
        if(num==0) break;
        do
        {
            g=0;
            do
            {
                g+=num%10;
                num/=10;
            }while(num);
            num=g;
        }while(g>9);
        printf("%d\n", g);
        num=0;
    }
    return 0;
}
