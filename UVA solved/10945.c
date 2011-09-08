#include<stdio.h>

char array[200000];

int main()
{
    char ch, a, b;
    long i=0, j;
    char flag=1;
    while((ch=getchar())!=EOF)
    {
        if(ch=='\n')
        {
            array[i]=0;
            if(array[0]=='D' && array[1]=='O' && array[2]=='N' && array[3]=='E') break;
            i--;
            for(j=0;j<i;i--, j++)
            { 
                a=array[i], b=array[j];
                if(a>='A' && a<='Z') a+=32;
                if(b>='A' && b<='Z') b+=32;
                if(a!=b)
                {
                    flag=0;
                    break;
                }
            }
            if(flag)printf("You won't be eaten!\n");
            else printf("Uh oh..\n");
            i=0, flag=1;
        }
        else if((ch>='A'&& ch<='Z')||(ch>='a'&& ch<='z'))
        {
            array[i++]=ch;
        }
    }
    return 0;
}
