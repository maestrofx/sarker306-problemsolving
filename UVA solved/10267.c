#include<stdio.h>

#define SIZE 251

char photo[SIZE][SIZE];
int m,n;

void fillregion(int, int, char, char);

int main()
{
	char ch='\0', ch1;
	int x=0, y=0, x1=0, x2=0, y1=0, y2=0;
	int i, j;
	char name[100], cmd[5000], cmd2[5];

	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	photo[i][j]='O';

	while(gets(cmd))
	{
	    sscanf(cmd, "%s", cmd2);
	    if(cmd2[0]=='X') break;
		switch(cmd2[0])
		{
			case 'I':   sscanf(cmd, "%*s%d%d", &m, &n);
			            for(i=0;i<n;i++)
			            for(j=0;j<m;j++)
			            photo[i][j]='O';
					    break;
			case 'L':   sscanf(cmd, "%*s%d%d%s", &x, &y, cmd2);
			            photo[y-1][x-1]=cmd2[0];
			            break;
			case 'V':   sscanf(cmd, "%*s%d%d%d%s", &x, &y1, &y2, cmd2);
                        if(y1>y2) y1^=y2^=y1^=y2;
						for(i=y1;i<=y2;i++) photo[i-1][x-1]=cmd2[0];
						break;
			case 'C':   for(i=0;i<n;i++)
			            for(j=0;j<m;j++)
			            photo[i][j]='O';
			            break;
			case 'H':   sscanf(cmd, "%*s%d%d%d%s", &x1, &x2, &y, cmd2);
                        if(x1>x2) x1^=x2^=x1^=x2;
			            for(j=x1;j<=x2;j++) photo[y-1][j-1]=cmd2[0];
			            break;
			case 'K':   sscanf(cmd, "%*s%d%d%d%d%s", &x1, &y1, &x2, &y2, cmd2);
						for(i=y1;i<=y2;i++)
						for(j=x1;j<=x2;j++)
						photo[i-1][j-1]=cmd2[0];
						break;
			case 'F':   sscanf(cmd, "%*s%d%d%s", &x, &y, cmd2);
			            fillregion(x, y, photo[y-1][x-1], cmd2[0]);
			            break;
			case 'S':   sscanf(cmd, "%*s%s", name);
			            printf("%s\n", name);
			            for(i=0;i<n;i++)
			            {
							for(j=0;j<m;j++)
							printf("%c", photo[i][j]);
							printf("\n");
						}
						break;
			default:
					    break;
		}
	}

	return 0;
}

void fillregion(int x, int y, char col1, char col2)
{
    if(col1==col2) return;
	if(y>=1&&y<=n)
	if(x>=1&&x<=m)
	if(photo[y-1][x-1]==col1)
	{
		photo[y-1][x-1]=col2;
		fillregion(x-1, y, col1, col2);
		fillregion(x+1, y, col1, col2);
		fillregion(x, y-1, col1, col2);
		fillregion(x, y+1, col1, col2);
	}

	return;
}
