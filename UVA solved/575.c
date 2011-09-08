#include<stdio.h>
int main()
{
    unsigned long n;
    unsigned long power[31]={1};
    int i, j;
    char num[35];
    for(i=1;i<32;i++) power[i]=(power[i-1]+1)*2-1;
    scanf("%s", num);
    while(num[0]!='0')
    {
        n=0;
        i=strlen(num)-1;
        for(j=0; num[j]!='\0';j++)
        {
            n+=(num[j]-'0')*power[i-j];
        }
        printf("%lu\n", n);
        scanf("%s", num);
    }
    return 0;
}
