#include<stdio.h>

long unsigned Cycle(long unsigned m)
{
long unsigned n=1;
while(m!=1)
{
if((m%2)==0) m/=2; else m=(3*m)+1;
n++;
}
return n;
}

int main()
{
unsigned long tmp,max,i,j,p,q, m;
while(scanf("%lu %lu",&i,&j)==2)
{
if((i==0)&&(j==0))
{
break;
}
else
{
i = (i>j) ? i + j - (j=i) : i;
}
p=q = i;
max = Cycle(i);
for(i+=1;i<(j+1);i++)
{
m=i;
tmp=1;
while(m!=1)
{
if((m%2)==0) m/=2; else m=(3*m)+1;
tmp++;
}
if (tmp>max)
{
max = tmp;
p = i;
}
}
if(p==1) max=4;
printf("Between %lu and %lu,",q,j);
printf(" %lu generates the longest",p);
printf(" sequence of %lu values.\n",(max-1));
}
return 0;
}
