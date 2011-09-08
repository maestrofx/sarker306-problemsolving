#include<stdio.h>

#define NUMBER 1000

long array[NUMBER];

int main()
{
    int n, test;
    int i, j;
    long temp;
    long counter, sum_counter;
    scanf("%d", &test);
    for(j=0;j<test;j++)
    {
        scanf("%d", &n);
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
        printf("Optimal train swapping takes %ld swaps.\n", sum_counter);
    }
    return 0;
}
