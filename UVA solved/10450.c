#include<stdio.h>

int main()
{
    int n, counter=1, test;
    unsigned long long array[52]={1, 2};
    int i, j;
    for(i=2;i<52;i++) array[i]=array[i-1]+array[i-2];
    scanf("%d", &test);
    for(;test;test--)
    {
        scanf("%d", &n);
        printf("Scenario #%d:\n%llu\n\n", counter++, array[n]);
    }
    return 0;
}
