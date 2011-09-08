#include<stdio.h>

#define SIZE 10010

long M;

int comp(long a, long b, long m)
{
    long res1, res2;
    char odd1, odd2;
    
    res1=a%m;
    res2=b%m;
    
    if(res1<res2) return 1;
    else if(res1>res2) return -1;
    
    odd1=a&1;
    odd2=b&1;
    
    if(odd1 && !odd2) return 1;
    if(!odd1 && odd2) return -1;
    
    if(odd1 && odd2)
    {
        if(a>b) return 1;
        else if(a<b)return -1;
    }
    
    if(!odd1 && !odd2)
    {
        if(a>b) return -1;
        else if(a<b)return 1;
    }
    
    return 0;
}

void quick_sort(long *items, long left, long right)
{
	register long i, j;
	long x,y;
	i=left, j=right;
	x=items[(left+right)/2];
	do
	{
		while(comp(items[i],x, M)==1&&(i<right))
			i++;
		while(comp(items[j],x, M)==-1&&(j>left))
			j--;
		if(i<=j)
		{
			y=items[i];
			items[i]=items[j];
			items[j]=y;
			i++;
			j--;
		}
	}while(i<=j);
	if (j>left) quick_sort(items, left, j);
	if (i<right) quick_sort(items, i, right);
	return;
}

int main()
{
    long N;
    long number[SIZE];
    char flag;
    long i;
    
    while(scanf("%ld%ld", &N, &M)!=EOF)
    {
        printf("%ld %ld\n", N, M);
        
        if(N==0 && M==0) break;
        
        for(i=0;i<N;i++) scanf("%ld", &number[i]);
        
        quick_sort(number, 0, N-1);
        
        for(i=0;i<N;i++) printf("%ld\n", number[i]);
    }
    
    return 0;
}
        
