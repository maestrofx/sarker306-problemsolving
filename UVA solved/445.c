#include<stdio.h>

int main()
{
    char ch, temp, flag=0;
    int f=0, i;
    while((ch=getchar())!=EOF)
    {
        if(ch>='0'&&ch<='9')
        {
            f+=ch-'0';
        }
        else if(ch=='\n' || ch=='!')
        {
            printf("\n");
            f=0, temp=0;
        }
        else
        {
            if(ch=='b') ch=' ';
            for(i=0;i<f;i++) putchar(ch);
            f=0;
        }
        temp=ch;
    }
    return 0;
}
