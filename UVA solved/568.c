#include<stdio.h>
#include<string.h>

long long fact[10005];
char temp[50000], temp1[50000];

/*void product(char *a, int n, char *b)
{
    int i, j, carry, value;

    for(j=0; a[j]=='0';j++);

    for(i=0, carry=0;a[j];j++, i++)
    {
        value=(a[j]-'0')*n+carry;
        carry=value/10;
        b[i]=value%10+'0';
    }

    while(carry)
    {
        b[i++]=carry%10+'0';
        carry/=10;
    }

    b[i]=0;
}

int main()
{
    int i, j;

    fact[1]=1;
    temp[0]='1', temp[1]=0;

    for(i=2;i<10001;i++)
    {
        product(temp, i, temp1);
        strcpy(temp, temp1);

        for(j=0;temp1[j]; j++)
        {
            if(temp1[j]!='0') break;
        }

        fact[i]=temp1[j]-'0';
    }

    while(scanf("%d", &i)!=EOF) printf("%5d -> %d\n", i, fact[i]);

    return 0;
}
*/

int main()
{
    int i;
    long n;

    fact[1]=1;

    for(i=2;i<10001;i++)
    {
        fact[i]=(i*fact[i-1])%1000000000;

        while(fact[i]>=10)
        {
            if(fact[i]%10)break;
            else fact[i]=fact[i]/10;
        }
    }

    while(scanf("%d", &i)!=EOF) printf("%5d -> %d\n", i, fact[i]%10);

    return 0;
}
