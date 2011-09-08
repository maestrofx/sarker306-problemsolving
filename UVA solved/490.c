#include<stdio.h>

#define SIZE 105

int main()
{
    char a[SIZE][SIZE];
    char *ptr[SIZE];
    int i, j, k, max=0;
    for(i=0;;i++) if(gets(a[i])==NULL) break;
    for(j=0;j<i;j++)
    {
        ptr[j]=a[j];
        k=strlen(a[j]);
        max=(max>k)? max: k;
    }
    for(;max;max--)
    {
        for(k=i-1;k+1;k--) 
        {
            if(*ptr[k]==0) printf(" ");
            else
            {
                printf("%c", *ptr[k]);
                ptr[k]++;
            }
        }
        printf("\n");
    }
    getchar();
    getchar();
    return 0;
}
