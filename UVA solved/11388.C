#include<stdio.h>
int main()
{
	int T, i;
	long unsigned G, L;
	scanf("%d", &T);
	for(i=0;i<T;i++)
	{
		scanf("%lu %lu", &G, &L);
		if(L%G) printf("-1\n");
		else printf("%lu %lu\n", G, L);
	}
	return 0;
}