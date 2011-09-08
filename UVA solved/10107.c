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
        for(j=0;j<i;j++)
        {
            if(n<array[j])
            {
                for(k= i+1; k>j; k--) array[k]=array[k-1];
                break;
            }
        }
        array[j]=n;
        if(i%2==0) printf("%ld\n", array[i/2]);
        else printf("%ld\n", (long)(array[(i-1)/2]+array[(i+1)/2])/2);
        i++;
    }
    return 0;
}
