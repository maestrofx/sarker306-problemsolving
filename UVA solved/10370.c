#include<stdio.h>
#define SIZE 1020
int main()
{
	long int sum_of_scores;
	float average, average_of_std;
	int count, i, j, k, tag, number_of_std, score[SIZE];
	scanf("%d", &count);
	for(i=0;i<count;i++)
	{
		scanf("%d",&number_of_std);
		sum_of_scores=0;
		for(j=0;j<number_of_std;j++)
		{
			scanf("%d", &score[j]);
			sum_of_scores+=score[j];
		}
		average=(float)sum_of_scores/number_of_std;
		k=0;
		for(tag=j-1;tag>=0;tag--)
		{
			if(score[tag]>average)
				k++;
		}
		average_of_std=(float)k/number_of_std*100;
		printf("%.3f%\n", average_of_std);
	}
	return 0;
}
