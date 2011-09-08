#include<stdio.h>

int main()
{
    unsigned int n, m, test, t;
    char ch;
    scanf("%ld", &test);
    for(;test;test--)
    {
        scanf("%x", &n);
        while(ch=getchar()) if (ch=='+' || ch=='-') break;
        scanf("%x", &m);  
       /*for(t=4096; t>0; t = t/2) 
        if(n & t) printf("1"); 
        else printf("0"); */
        for(t=4096; t>0; t>>= 1) printf("%d", (n & t)!=0);
        printf(" %c ", ch);
        for(t=4096; t>0; t>>= 1) printf("%d", (m & t)!=0);
        printf(" = ");
        if(ch=='+')printf("%d\n", m+n);
        else printf("%d\n", n-m);
    }
    return 0;
}
