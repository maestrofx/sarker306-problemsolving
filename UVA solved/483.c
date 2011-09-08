#include<stdio.h>

int main()
{
    char word[10000];
    char ch;
    int i=0, flag=0;
    while((ch=getchar())!=EOF)
    {
        if(ch!=' '&&ch!='\n'&&ch!='\t')
        {
            word[i++]=ch;
            flag=1;
        }
        else
        {
            if(flag)
            {
                for(;i;i--) putchar(word[i-1]);
                flag=0;
                i=0;
            }
            putchar(ch);
        }
    }
    return 0;
}
