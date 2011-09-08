
#include<stdio.h>
#define SIZE 101
char A[SIZE][SIZE];
void minesweep(int , int);
int main()
{
	int n, m;
	int i, j, count=0;
	char ch;
	scanf("%d%d", &n, &m);
	while((m)||(n))
	{
		if(count) printf("\n");
        count++;
		for(i=0;i<n;i++)
		{
		    for(j=0;j<m;)
			{
				ch=getchar();
				if (ch=='.'||ch=='*')
				{
					A[i][j]=ch;
					j++;
				}
			}
		}
		minesweep(n, m);
		printf("Field #%d:\n", count);
		for(i=0;i<n;i++)
		{
		    for(j=0;j<m;j++) printf("%c", A[i][j]);
		    printf("\n");
		}
		
	    scanf("%d%d", &n, &m);
	}
	return 0;
}
void minesweep(int n, int m)
{
	int x, i, j;
    for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			{
				x=0;
				if (A[i][j]=='*') continue;
				if(i>=1)
				{
					if (j>=1)
					    if(A[i-1][j-1]=='*') x++;
					if (A[i-1][j]=='*') x++;
					if (j<m-1)
					    if (A[i-1][j+1]=='*') x++;
				}
				{
					if (j>=1)
					    if(A[i][j-1]=='*') x++;
					if (j<m-1)
					    if(A[i][j+1]=='*') x++;
				}
				if(i<n-1)
				{
					if (j>=1)
					    if(A[i+1][j-1]=='*') x++;
					if (A[i+1][j]=='*') x++;
					if (j<m-1)
					    if(A[i+1][j+1]=='*') x++;
				}
				A[i][j]=x+'0';
			}
	return;
}
