#include<stdio.h>
#include<stdbool.h>
#include<math.h>

#define SIZE 2000

bool prime[SIZE];

int main()
{
    int i, j, n, number;
    char str[24];
    char *ptr;
    prime[0]=false;
    prime[1]=true;
    j=sqrt(SIZE);
	for(i=2;i<SIZE;i++)
		prime[i]=true;
    for(i=2;i<=j;i++)
	{
		if(prime[i]==true)
		{
			for(n=2*i;n<SIZE;n=n+i)
			{
				prime[n]=false;
			}
		}
	}
	while(scanf("%s", str)==1)
	{
        number=0;
        ptr=str;
        while(*ptr!='\0')
        {
            number+= (*ptr>='a'&&*ptr<='z')? *ptr-'a'+1: *ptr-'A'+27;
            ptr++;
        }
        if(prime[number]==true) printf("It is a prime word.\n");
        else printf("It is not a prime word.\n");
    }
    return 0;
}
