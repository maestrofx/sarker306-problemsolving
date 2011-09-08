#include<stdio.h>
#include<string.h>

#define MAX 220
#define TOTAL_NUM 1003

char array[TOTAL_NUM][MAX]={"0", "1"};
char temp[MAX];

void addition(char *x, char *y, char *temp)
{
    char A[MAX], B[MAX];
   	char carry=0;
	int c,d,i,max;
	strcpy(A, x), strcpy(B, y);
    c=strlen(A);
	d=strlen(B);
	if(c>d)
	{
		max=c;
		for(i=0;i<c-d;i++) temp[i]='0';
		temp[i]='\0';
		strcat(temp,B);
		strcpy(B,temp);
	}
	else
	{
		max=d;
		for(i=0;i<d-c;i++)
			temp[i]='0';
			temp[i]='\0';
		strcat(temp,A);
		strcpy(A,temp);
	}
	for(i=max;i>=0;i--)
	{
		if(A[i]+B[i]+carry-'0'>'9')
		{
			temp[i]=A[i]+B[i]+carry-'0'-10;
			carry=1;
		}
		else
		{
			temp[i]=A[i]+B[i]+carry-'0';
			carry=0;
		}
	}
	temp[max]='\0';
	if(carry)
	{
		for(i=max;i>=0;i--)
			temp[i+1]=temp[i];
		temp[0]='1';
		temp[max+1]='\0';
	}
    return;
}

int main()
{
    int n;
    int i, j, k, l, carry;
    for(i=2;i<TOTAL_NUM;i++)
    {
        addition(array[i-2], array[i-1], temp);
        strcpy(array[i], temp);
    }
    while(scanf("%d", &n)!=EOF && n>=0 && n<=1000)
    {
        l=strlen(array[n+2]);
        for(i=0;i<l;i++) putchar(array[n+2][i]);
        printf("\n");
    }
    return 0;
}
