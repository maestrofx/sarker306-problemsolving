#include<stdio.h>

int main()
{
    long s1, s2, temp;
    char ch;
    int test;
    int i;
    scanf("%d", &test);
    ch=getchar();
    for(i=0;i<test;)
    {
        s1=s2=0;
        while((ch=getchar())!='\n') if(ch=='1' || ch=='0') s1=2*s1+ch-'0';
        while((ch=getchar())!='\n') if(ch=='1' || ch=='0') s2=2*s2+ch-'0';
        if(s1<s2)
        {
            temp=s1;
            s1=s2;
            s2=temp;
        }
        while(s2)
	   {
    		temp=s1;
    		s1=s2;
    		s2=temp%s2;
	   }
	   if(s1>1) printf("Pair #%d: All you need is love!\n", ++i);
	   else printf("Pair #%d: Love is not all you need!\n", ++i);
    }
    return 0;
}
