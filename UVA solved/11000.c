#include<stdio.h>

#define SIZE 55

int main()
{
    long long array[SIZE]={0, 1};
    int i;
    for(i=2;i<SIZE;i++) array[i]=array[i-1]+array[i-2]+1;
    while(scanf("%d", &i)!=EOF && i>-1) printf("%I64d %I64d\n", array[i], array[i+1]);
    return 0;
}
