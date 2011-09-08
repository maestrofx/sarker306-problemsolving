#include<stdio.h>

int main()
{
    char ch;
    while((ch=getchar())!=EOF)
    {
        if(ch=='\n') putchar(ch);
        else putchar(ch-7);
    }
    return 0;
}
