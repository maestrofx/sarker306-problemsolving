#include<stdio.h>

#define N 1000

long array[N];

int main()
{
    int n;
    int i;
    long temp;
    long counter, sum_counter;
    while(scanf("%d", &n)==1)
    {
        for(i=0; i<n; i++) scanf("%ld", &array[i]);
        sum_counter=0;
        do
        {
            counter=0;
            for(i=0;i<n-1;i++)
            {
                if(array[i]>array[i+1])
                {
                    temp=array[i];
                    array[i]=array[i+1];
                    array[i+1]=temp;
                    counter++;
                    i++;
                }
            }
            sum_counter+=counter;
        }while(counter);
        /*for(i=0; i<n; i++) printf("%ld ", array[i]);*/
        printf("Minimum exchange operations : %ld\n", sum_counter);
    }
    return 0;
}
