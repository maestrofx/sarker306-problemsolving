#include<stdio.h>

double x1[12],y1[12],x2[12],y2[12], x3[12], y3[12], h[12],k[12],r,cons[12], tria[12], x,y;

int circle(int j)

{

	double res;
	
	res=(x*x)+(y*y)-(2*h[j]*x)-(2*k[j]*y)+(cons[j]);

	if(res>0)

		return 0;

	else 

		return 1;

}

int rectangle(int j)

{

	if((y<y1[j]) && (y>y2[j]) && (x>x1[j]) && (x<x2[j]))

		return 1;

	else

		return 0;

}

int triangle(int j)
{
    
    
    
}

int main()

{
	
	int figure[15];
	
	char humba[50];

	int flag;
	
	int i, j, m, v;
	
	

	for(i=1; ;i++)

	{
        
        gets(humba);
        
        if(humba[0]=='*') break;
		
		if(humba[0]=='r')

		{

            figure[i]=1;
            
			sscanf(humba,"r %lf %lf %lf %lf",&x1[i],&y1[i],&x2[i],&y2[i]);

		}

		else if(humba[0]=='c')

		{
            
            figure[i]=2;

			sscanf(humba,"c %lf %lf %lf",&h[i],&k[i],&r);

			cons[i]=(h[i]*h[i])+(k[i]*k[i])-r*r;

		}
		
		else
		
		{
            
            figure[i]=3;
            
            sscanf(humba, "t %lf %lf %lf %lf %lf %lf", &x1[i],&y1[i],&x2[i],&y2[i],&x3[i],&y3[i]);
            
            
            
        }

	}

	for(m=1; ;m++)

	{

		flag=0;
		
		scanf("%lf %lf",&x,&y);

		if(x==9999.9 && y==9999.9)

			break;

		for(j=1;j<i;j++)

		{

			if(figure[j]==1)

				v=rectangle(j);

			else if(figure[j]==2)

				v=circle(j);
				
			else if(figure[j]==3)
			
			     v=triangle(j);

			if(v)

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
