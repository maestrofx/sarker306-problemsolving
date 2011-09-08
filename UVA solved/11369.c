#include<stdio.h>

int price[20000];

void quick_sort(int *items, int left, int right)
{
	register int i, j;
	int x,y;
	i=left, j=right;
	x=items[(left+right)/2];
	do
	{
		while((items[i]<x)&&(i<right))
			i++;
		while((items[j]>x)&&(j>left))
			j--;
		if(i<=j)
		{
			y=items[i];
			items[i]=items[j];
			items[j]=y;
			i++;
			j--;
		}
	}while(i<=j);
	if (j>left) quick_sort(items, left, j);
	if (i<right) quick_sort(items, i, right);
	return;
}

int main()
{
    int test, item;
    int i, j;
    long max;
    scanf("%d", &test);
    for(;test;test--)
    {
        scanf("%d", &item);
        for(j=0;j<item;j++) scanf("%d", &price[j]);
        quick_sort(price, 0, j-1);
        for(i=(j)%3, max=0;i<j ; i+=3) max+=price[i];
        printf("%ld\n", max);
    }
    return 0;
}

