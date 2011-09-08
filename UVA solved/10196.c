#include<stdio.h>
char chess[8][8];
int check_white(int, int);
int check_black(int, int);
int main()
{
	int count=0;
	int i, j, m1, n1, m2, n2, dotctr;
	char ch;
	while(1)
	{
		m1=n1=m2=n2=0;
		dotctr=0;
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;)
			{
				ch=getchar();
				if(ch=='K')
				{
					chess[i][j]=ch;
					m1=i;
					n1=j;
					j++;
				}
				else if(ch=='k')
				{
					chess[i][j]=ch;
					m2=i;
					n2=j;
					j++;
				}
				else if (isalpha(ch))
				{
					chess[i][j]=ch;
					j++;
				}
				else if(ch=='.')
				{
					chess[i][j]=ch;
					j++;
					dotctr++;
				}
			}
		}
		if (dotctr==64) break;
		count++;
		if (check_white(m1, n1)==1)
		printf("Game #%d: white king is in check.\n", count);
		else if (check_black(m2, n2)==1)
		printf("Game #%d: black king is in check.\n", count);
		else printf("Game #%d: no king is in check.\n", count);
	}
	return 0;
}
int check_white(int m, int n)
{
	int flag=0, flag1, flag2, flag3, flag4, flag5, flag6, flag7, flag8, x, i, j;
	flag1=flag2=flag3=flag4=flag5=flag6=flag7=flag8=0;
	for(x=1; x<8; x++)
	{
		if(m-x>=0)
		{
			if (n-x>=0)
			if(!flag1)
			{
				if (chess[m-x][n-x]=='b'||chess[m-x][n-x]=='q')
				flag=1;
				else if (chess[m-x][n-x]!='.') flag1=1;
			}
			if (!flag2)
			{
				if (chess[m-x][n]=='r'||chess[m-x][n]=='q')
				flag=1;
				else if (chess[m-x][n]!='.') flag2=1;
			}
			if (n+x<8)
			if(!flag3)
			{
				if (chess[m-x][n+x]=='q'||chess[m-x][n+x]=='b')
				flag=1;
				else if (chess[m-x][n+x]!='.') flag3=1;
			}
		}
		if(m+x<8)
		{
			if (n-x>=0)
			if (!flag4)
			{
				if (chess[m+x][n-x]=='b'||chess[m+x][n-x]=='q')
				flag=1;
				else if (chess[m+x][n-x]!='.') flag4=1;
			}
			if (!flag5)
			{
				if (chess[m+x][n]=='r'||chess[m+x][n]=='q')
				flag=1;
				else if (chess[m+x][n]!='.') flag5=1;
			}
			if (n+x<8)
			if (!flag6)
			{
				if (chess[m+x][n+x]=='q'||chess[m+x][n+x]=='b')
				flag=1;
				else if (chess[m+x][n+x]!='.') flag6=1;
			}
		}
		if (n-x>=0)
		if (!flag7)
		{
			if (chess[m][n-x]=='r'||chess[m][n-x]=='q')
			flag=1;
			else if (chess[m][n-x]!='.') flag7=1;
		}
		if(n+x<8)
		if(!flag8)
		{
			if (chess[m][n+x]=='r'||chess[m][n+x]=='q')
			flag=1;
			else if (chess[m][n+x]!='.') flag8=1;
		}
		if (flag) return 1;
	}
	for(i=1, j=2; j; i++, j--)
	{
		if (m-i>=0)
		{
			if (n-j>=0)
			if (chess[m-i][n-j]=='n')
			flag=1;
			if (n+j<8)
			if (chess[m-i][n+j]=='n')
			flag=1;
		}
		if (m+i<8)
		{
			if (n-j>=0)
			if (chess[m+i][n-j]=='n')
			flag=1;
			if (n+j<8)
			if (chess[m+i][n+j]=='n')
			flag=1;
		}
		if (flag) return 1;
	}
	if (m-1>=0)
	{
		if (n-1>=0)
		if (chess[m-1][n-1]=='p')
		flag=1;
		if (n+1<8)
		if (chess[m-1][n+1]=='p')
		flag=1;
	}
	return flag;
}
int check_black(int m, int n)
{
	int flag=0, flag1, flag2, flag3, flag4, flag5, flag6, flag7, flag8, x, i, j;
	flag1=flag2=flag3=flag4=flag5=flag6=flag7=flag8=0;
	for(x=1; x<8; x++)
	{
		if(m-x>=0)
		{
			if (n-x>=0)
			if(!flag1)
			{
				if (chess[m-x][n-x]=='B'||chess[m-x][n-x]=='Q')
				flag=1;
				else if (chess[m-x][n-x]!='.') flag1=1;
			}
			if (!flag2)
			{
				if (chess[m-x][n]=='R'||chess[m-x][n]=='Q')
				flag=1;
				else if (chess[m-x][n]!='.') flag2=1;
			}
			if (n+x<8)
			if(!flag3)
			{
				if (chess[m-x][n+x]=='Q'||chess[m-x][n+x]=='B')
				flag=1;
				else if (chess[m-x][n+x]!='.') flag3=1;
			}
		}
		if(m+x<8)
		{
			if (n-x>=0)
			if (!flag4)
			{
				if (chess[m+x][n-x]=='B'||chess[m+x][n-x]=='Q')
				flag=1;
				else if (chess[m+x][n-x]!='.') flag4=1;
			}
			if (!flag5)
			{
				if (chess[m+x][n]=='R'||chess[m+x][n]=='Q')
				flag=1;
				else if (chess[m+x][n]!='.') flag5=1;
			}
			if (n+x<8)
			if (!flag6)
			{
				if (chess[m+x][n+x]=='Q'||chess[m+x][n+x]=='B')
				flag=1;
				else if (chess[m+x][n+x]!='.') flag6=1;
			}
		}
		if (n-x>=0)
		if (!flag7)
		{
			if (chess[m][n-x]=='R'||chess[m][n-x]=='Q')
			flag=1;
			else if (chess[m][n-x]!='.') flag7=1;
		}
		if(n+x<8)
		if(!flag8)
		{
			if (chess[m][n+x]=='R'||chess[m][n+x]=='Q')
			flag=1;
			else if (chess[m][n+x]!='.') flag8=1;
		}
		if (flag) return 1;
	}
	for(i=1, j=2; j; i++, j--)
	{
		if (m-i>=0)
		{
			if (n-j>=0)
			if (chess[m-i][n-j]=='N')
			flag=1;
			if (n+j<8)
			if (chess[m-i][n+j]=='N')
			flag=1;
		}
		if (m+i<8)
		{
			if (n-j>=0)
			if (chess[m+i][n-j]=='N')
			flag=1;
			if (n+j<8)
			if (chess[m+i][n+j]=='N')
			flag=1;
		}
		if (flag) return 1;
	}
	if (m+1<8)
	{
		if (n-1>=0)
		if (chess[m+1][n-1]=='P')
		flag=1;
		if (n+1<8)
		if (chess[m+1][n+1]=='P')
		flag=1;
	}
	return flag;
}
