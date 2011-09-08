#include<stdio.h>

#define SIZE 10000

int main()
{
    char s[SIZE];
    char *ptr;
    char ch;
    while(scanf("%s", s)==1)
    {
        ptr=s;
        while((ch=getchar())!='\n')
        {
            if(*ptr==0) continue;
            if(*ptr==ch) ptr++;
        }
        if(*ptr==0) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
