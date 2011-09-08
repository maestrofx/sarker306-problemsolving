#include<stdio.h>

#define SIZE 10005

long array[SIZE];

int main()
{
    long n, temp;
    int i=0, j, k, low, high;
    scanf("%ld", &array[i++]);
    printf("%ld\n", array[0]);
    while(scanf("%ld", &n)==1)
    {
        low=0, high=i-1;
        j=(low+high)/2;
        while(j>0 && !(array[j]>=n&&array[j-1]<n)&&!(array[j]<=n&&array[j+1]>n))
		{
			if (array[j]>n) high=j;
			else low=j;
			j=(int)((low+high)/2);
			if(j==low || j==high) break;
		}
		if(j<i && n<=array[j])
		{
            for(k= i+1; k>j; k--) array[k]=array[k-1];
            array[j]=n;
        }
        else if(j<i && n<=array[j+1])
        {
            for(k= i+1; k>j+1; k--) array[k]=array[k-1];
            array[j+1]=n;
        }
        else array[i]=n;
        /*for(j=0;j<i+1;j++) printf("%ld ", array[j]);*/
        if(i%2==0) printf("%ld\n", array[i/2]);
        else printf("%ld\n", (long)(array[(i-1)/2]+array[(i+1)/2])/2);
        i++;
    }
    return 0;
}
