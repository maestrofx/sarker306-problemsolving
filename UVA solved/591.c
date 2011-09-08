/*
  Name: 591: Box of Bricks
  Copyright: 
  Author: 
  Date: 31/08/09 00:13
  Description: 
*/
#include<stdio.h>
#define NMAX 50
int main()
{
    int A[NMAX];
    int n, i, mean, sum, x, counter=0;
    scanf("%d", &n);
    while(n)
    {
        sum=0;
        for(i=0;i<n;i++)
        {
            scanf("%d", &A[i]);
            sum+=A[i];
        }
        mean=sum/n;
        sum=0;
        for(i=0;i<n;i++)
        {
            x=mean-A[i];
            x=(x>0)? x: -x;
            sum+=x;
        }
        sum/=2;
        printf("Set #%d\nThe minimum number of moves is %d.\n\n", ++counter,sum);
        scanf("%d", &n);
    }
    return 0;
}
