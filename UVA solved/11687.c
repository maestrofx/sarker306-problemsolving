#include<stdio.h>

int main()
{
    long i=0;
    char ch, temp;
    while(ch=getchar())
    {
        if(ch=='E') break;
        if(ch=='\n')
        {
            if(temp=='1' && i==1) printf("1\n");
            else if(i==1) printf("2\n");
            else if(i<10) printf("3\n");
            else if(i<1000000000) printf("4\n");
            else printf("5\n");
            i=0;
        }
        else
        {
            temp=ch;
            i++;
        }
    }
    return 0;
}
