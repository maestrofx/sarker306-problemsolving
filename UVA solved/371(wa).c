#include<stdio.h>

int main()
{
    unsigned long first, last;
    unsigned long max, max_num, sequence_count;
    unsigned long n, i;
    while(scanf("%lu%lu", &first, &last)==2 && (first)||(last))
    {
        max=0;
        max_num=first;
        for(i=first;i<=last; i++)
        {
            if(i==1)
            {
                max=3;
                max_num=1;
            }
            n=i;
            sequence_count=0;
            while(n!=1)
            {
                if(n%2) n=3*n+1;
                else if(n>1) n/=2;
                else break;
                sequence_count++;
            }
            if(max< sequence_count)
            {
                max=sequence_count;
                max_num=i;
            }
        }
        printf("Between %lu and %lu, %lu generates the longest sequence of %lu values.\n", first, last, max_num, max);
    }
    return 0;
}
