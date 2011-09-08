/*
  Name: 694
  Copyright: 
  Author: 
  Date: 31/08/09 08:14
  Description: Collatz
*/
#include<stdio.h>
#include<stdbool.h>
int main()
{
    long A, L, x;
    int count, cases=1;
    bool flag;
    scanf("%ld%ld", &A, &L);
    while(A>=0 || L>=0)
    {
        count=1;
        x=A;
        flag=true;
        if (x%2==1 && x>(int)(L-1)/3) flag=false;
        while(flag&& x!=1)
        {
            if (x%2==1 && x>(L-1)/3)
            {
                flag=false;
                break;
            }
            count++;
            x=(x%2)? 3*x+1: x/2;
        }
        printf("Case %d: A = %ld, limit = %ld, number of terms = %d\n", cases++, A, L, count);
        scanf("%ld%ld", &A, &L);
    }
    return 0;
}
