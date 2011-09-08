#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define SIZE 55

bool next_permutation(char *F, char * L);

int main()
{
    char str[SIZE];
    char *ptr;
    while(scanf("%s", str)==1)
    {
        for(ptr=str;*ptr!=0;ptr++);
        if(str[0]=='#'&&str+1==ptr) break;
        if (next_permutation(str, ptr-1)==true) printf("%s\n", str);
        else printf("No Successor\n");
    }
    return 0;
}

bool next_permutation(char *F, char * L)
{
	char *I;
	char *Ip;
	char *J;
	char temp;
	I= ++L;
	if (F == L || F == --I)
		return (false);
	for (; ; )
	{
		Ip = I;
		if (*--I < *Ip)
		{
			J = L;
			for (; !(*I < *--J); );
			temp=*I;
			*I=*J;
			*J=temp;
            for (; Ip != L && Ip != --L; ++Ip)
			{
				temp=*Ip;
				*Ip=*L;
				*L=temp;
			}
			return (true);
		}
		if (I == F)
		{
            for (; F != L && F != --L; ++F)
			{
				temp=*F;
				*F=*L;
				*L=temp;
			}
			return (false);
		}
	}
}
