#include<stdio.h>
#include<string.h>
#include<math.h>

#define SIZE 10005

int main()
{
    int test, i, j, n, k;
    char array[SIZE];
    
    scanf("%d", &test);
	getchar();
    for(;test;)
    {
        gets(array);
        n=strlen(array);
		if(n==0) continue;
		test--;
        j=sqrt(n);
        if (j*j==n)
        {
            for(i=0, k=0;;i+=j)
            {
                if(i>=n) k++, i=k;
				if(k>=j) break;
                putchar(array[i]);
            }
        }
        else printf("INVALID");
        printf("\n");
    }
    return 0;
}
