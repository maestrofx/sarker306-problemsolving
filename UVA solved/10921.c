#include<stdio.h>

int main()
{
    char ch;
    while((ch=getchar())!=EOF)
    {
        if(ch>='A'&&ch<='Z')
        {
            ch-=65;
            if(ch<15) printf("%d", ch/3+2);
            else if(ch<19) printf("7");
            else if(ch<22) printf("8");
            else printf("9");
        }
        else putchar(ch);
    }
    return 0;
}
