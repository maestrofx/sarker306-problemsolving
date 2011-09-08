#include<stdio.h>
#include<string.h>

#define SIZE 367

char array[SIZE][800];
char temp[800];
    
void int_str_mult(char *, int, char *);

int main()
{
    int i, j, n;
    int digit[10];
    char *ptr;
    array[0][0]='1', array[0][1]=0;
    array[1][0]='1', array[1][1]=0;
    for(i=2; i<SIZE;i++)
    {
        int_str_mult(array[i-1], i, temp);
        strcpy(array[i], temp);
    }
    while(scanf("%d", &n)==1 && n)
    {
        for(i=0;i<10;i++) digit[i]=0;
        printf("%d! --\n   ", n);
        for(ptr=array[n];*ptr;ptr++) digit[*ptr-'0']++;
        for(i=0;i<10;i++)
        {
            if(i==5) printf("\n   ");
            printf("(%d)", i);
            printf("%5d    ", digit[i]);
        }
        printf("\n");
    }
    return 0;
}

void int_str_mult(char *A, int n, char *B)
{
    int carry=0, i, x, j, prod;
    char p[20]={0};
    x=strlen(A);
    for(i=x-1; i+1;i--)
    {
        prod=(A[i]-'0')*n+carry;
        B[i]=prod%10+'0';
        carry=prod/10;
    }
    if(carry)
    {
        prod=carry;
        for(j=0;prod;j++, prod/=10) p[j]=prod%10+'0';
        for(i=x;i+1;i--) B[i+j]=B[i];
        j--;
        for(i=0;j>=0;j--, i++) B[i]=p[j];
    }
}
