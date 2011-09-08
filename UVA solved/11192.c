#include<stdio.h>
#include<string.h>

#define SIZE 110

int main()
{
    int g;
    int part;
    int i, j, k;
    char temp;
    char str[SIZE];
    while(scanf("%d", &g)==1 && g)
    {
        scanf("%s", str);
        part=strlen(str)/g;
        for(i=0;i<g;i++)
        {
            for(j=i*part, k=(i+1)*part-1; j<k; j++, k--)
            {
                temp=str[j];
                str[j]=str[k];
                str[k]=temp;
            }
        }
        printf("%s\n", str);
    }
    return 0;
}
