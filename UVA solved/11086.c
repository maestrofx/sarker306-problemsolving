#include<stdio.h>

#define SIZE 1048580

char comp_prime[SIZE];

int main()
{
    long i, n, counter;
    
    for(i=2;i<SIZE;i++)
	{
		if(comp_prime[i]==0)
		{
			for(n=i*i;n<SIZE;n=n+i)
			{
				comp_prime[n]=1;
			}
		}
	}
	
	for(i=2;i<SIZE;i++)
	{
		if(comp_prime[i]==1)
		{
			for(n=i*2;n<SIZE;n=n+i)
			{
				comp_prime[n]=0;
			}
		}
	}
	
	while(scanf("%ld", &i)!=EOF)
	{
        counter=0;
        for(i;i;i--)
        {
            scanf("%ld", &n);
            if(comp_prime[n]==1)  counter++;
        }
        
        printf("%ld\n", counter);
    }
      
    return 0;
}
	
