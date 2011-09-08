#include<stdio.h>

int milo[10001];

int primecheck(long n)
{
    if( n==1) return 0;
    int a;

    if(n%2==0) return 0;
    for ( a=3; a*a<=n; a+=2)
    {
        if ( n%a == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int a,b,i,cou;
    double res;
    
    for ( i=0; i<=10000; i++) if (primecheck(i*i+i+41)) milo[i]=milo[i-1]+1;
    else milo[i]=milo[i-1];
      
    while((scanf("%d%d",&a,&b))!=EOF)
    {
        cou=0;
        /*for (i=a;i<=b;i++)
        {
            if (milo[i]=='1') cou++;
        }*/
        if(a>0) cou=milo[b]-milo[a-1];
        else cou=milo[b];
        res=(double) 100.0*cou/(b-a+1)+0.000001;
        printf("%.2lf\n",res);
    }
    return 0;
}
