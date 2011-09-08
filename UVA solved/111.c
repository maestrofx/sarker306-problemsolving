#include <stdio.h> 
#include <string.h> 
#define MAX 22

int LCSlength(void);

int X[MAX],Y[MAX]; 
int i,j,m,n,c[MAX][MAX],num; 

int main()
{
    scanf("%d",&num);
    for(i=0; ;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&(X[i][j]));
            if(X[i][0]==EOF)
            break;
        }
    while(1)
    {
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
