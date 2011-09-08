#include<stdio.h>

int main()
{
    long long catalan[25], n;
    int i;
    catalan[0]=0, catalan[1]=1;
    for(i=1;i<24;i++)
    {
        catalan[i+1]=catalan[i]*(2*i+1)*2;
        catalan[i+1]/=i+2;
    }
    while(scanf("%I64d", &n)!=EOF)
    {
        for(i=0;i<25;i++) if(catalan[i]==n) break;
        if(i<25) printf("%d\n", i);
    }
    return 0;
}
