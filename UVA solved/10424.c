#include<stdio.h>

#define SIZE 30

int main()
{
    char s1[SIZE], s2[SIZE];
    char *ptr;
    int a, b, temp;
    double ratio;
    while(gets(s1))
    {
        gets(s2);
        a=b=0;
        for(ptr=s1;*ptr!=0;ptr++)
        {
            if(*ptr>='A'&& *ptr<='Z') a+=*ptr-'A'+1;
            else if(*ptr>='a'&& *ptr<='z') a+=*ptr-'a'+1;
        }
        for(ptr=s2;*ptr!=0;ptr++)
        {
            if(*ptr>='A'&& *ptr<='Z') b+=*ptr-'A'+1;
            else if(*ptr>='a'&& *ptr<='z') b+=*ptr-'a'+1;
        }
        a%=9, b%=9;
        a=a+9*(a==0), b=b+9*(b==0);
        if(a>b)
        {
            temp=a;
            a=b;
            b=temp;
        }
        ratio=(double)a/b;
        if(a==b) printf("100.00 %c\n", '%');
        else printf("%.2lf %c\n",100*ratio, '%');
    }
    return 0;
}
