#include<stdio.h>

int main()

{
	
	char line[500];
	
	double x1[12],y1[12],x2[12],y2[12],x,y;

	int i=1,j,m,flag;

	for( ; ; )

	{

		gets(line);

		if(line[0]=='*')

			break;
		
		sscanf(line,"r %lf %lf %lf %lf",&x1[i],&y1[i],&x2[i],&y2[i]);

		i++;

	}

	for(m=1; ;m++)

	{

		scanf("%lf%lf",&x,&y);

		if(x==9999.9 && y==9999.9)

			break;

		flag=0;
		
		for(j=1;j<i;j++)

		{

			if((y<y1[j]) && (y>y2[j]) && (x>x1[j]) && (x<x2[j]))

			{

				printf("Point %d is contained in figure %d\n",m,j);

				if(flag==0)

					flag=1;

			}

		}

		if(flag==0)

			printf("Point %d is not contained in any figure\n",m);

	}
	
	return 0;

}
