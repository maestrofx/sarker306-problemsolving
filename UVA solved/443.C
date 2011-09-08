#include<stdio.h>
#define SIZE 5900
double min(double a, double b, double c, double d)
{
	double temp;
	temp=(a<b)? a:b;
	temp=(temp<c)? temp: c;
	temp=(temp<d)? temp: d;
	return temp;
}
int main()
{
	unsigned long check2, check3, check5, check7, last, n, m=5850, i, j=1, k;
	double  temp2, temp3, temp5, temp7, temp, humble[SIZE];
	int flag;
	humble[0]=0, humble[1]=1;
	check2=check3=check5=check7=1;
	temp2=2, temp3=3, temp5=5, temp7=7;
	for(i=2;j<m;i++)
	{
	temp=min(temp2, temp3, temp5, temp7);
	flag=1;
	for(k=j;humble[k]>=temp;k--)
	{
		if(humble[k]==temp)
		{
			flag=0;
			break;
		}
	}
	if (flag==1)
	{
		j++;
		humble[j]=temp;
	}
	if(temp==temp2)
	{
		last=2;
		check2++;
	}
	else if(temp==temp3)
	{
		last=3;
		check3++;
	}
	 else if(temp==temp5)
	{
		last=5;
		check5++;
	}
	 else if(temp==temp7)
	{
		last=7;
		check7++;
	}
	 if(last==3)
		 temp3=humble[check3]*3;
	 else if(last==2)
		 temp2=humble[check2]*2;
	 else if(last==5)
		 temp5=humble[check5]*5;
	 else if(last==7)
		 temp7=humble[check7]*7;
}
	scanf("%lu", &n);
	while(n)
	{
		switch(n%10)
		{
		case 1:
			if(n%100==11)printf("The %luth humble number is %.0lf.\n", n, humble[n]);
			else printf("The %lust humble number is %.0lf.\n", n, humble[n]);
			break;
		case 2:
			if(n%100==12)printf("The %luth humble number is %.0lf.\n", n, humble[n]);
			else printf("The %lund humble number is %.0lf.\n", n, humble[n]);
			break;
		case 3:
			if(n%100==13)printf("The %luth humble number is %.0lf.\n", n, humble[n]);
			else printf("The %lurd humble number is %.0lf.\n", n, humble[n]);
			break;
		default:printf("The %luth humble number is %.0lf.\n", n, humble[n]);
			break;
		}
		/*printf("The %luth humble number is %.0lf.\n", n, humble[n]);*/
		scanf("%lu", &n);
	}
	return 0;
}