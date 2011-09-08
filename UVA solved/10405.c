#include <stdio.h> 
#include <string.h> 
#define MAX 1005

int LCSlength(void);

char X[MAX],Y[MAX]; 
int i,j,m,n,c[MAX][MAX]; 

int main()
{
    while(gets(X))
    {
        gets(Y);
        printf("%d\n", LCSlength());
    }
    return 0;
}

int LCSlength(void) 
{ 
  m=strlen(X); 
  n=strlen(Y);
  for (i=1;i<=m;i++) c[i][0]=0;
  for (j=0;j<=n;j++) c[0][j]=0; 
  for (i=1;i<=m;i++) 
    for (j=1;j<=n;j++) 
    { 
      if (X[i-1]==Y[j-1]) c[i][j]=c[i-1][j-1]+1; 
      else if (c[i-1][j]>=c[i][j-1]) c[i][j]=c[i-1][j]; 
      else c[i][j]=c[i][j-1];
    } 
  return c[m][n]; 
}
