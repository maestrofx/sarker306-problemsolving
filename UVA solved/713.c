#include<stdio.h>
#include<string.h>

#define MAX 1000

int main()
{
    char a[MAX], b[MAX], temp[MAX];
    int test, counter=0, len_a, len_b, len, x, carry=0, i, zero, j;
    scanf("%d", &test);
    for(;counter<test;counter++)
    {
        scanf("%s%s", a, b);
        carry=zero=0;
        len_a=strlen(a);
        len_b=strlen(b);
        len=(len_a>len_b)?len_a:len_b;
        if(len==len_a)
        {
            for(i=len_b;i<len_a;i++) b[i]='0';
            b[i]=0;
        }
        else
        {
            for(i=len_a;i<len_b;i++) a[i]='0';
            a[i]=0;
        }
        for(i=0;i<len;i++)
        {
            x=carry+a[i]+b[i]-2*'0';
            temp[i]=x%10+'0';
            carry=x/10;
        }
        if(!carry)temp[i]=0;
        else
        {
            temp[i++]=carry+'0';
            temp[i]=0;
        }
        while(temp[zero]=='0') zero++;
    	if(zero)
    	{
    		for(i=zero,j=0;temp[i-1]!='\0';i++, j++) temp[j]=temp[i];
    	}
        printf("%s", temp);
        printf("\n");
    }
    return 0;
}
