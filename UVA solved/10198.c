#include<stdio.h>
#include<string.h>
#define MAX 450

char array[1001][450]={"0", "2", "5", "13"};

void reverse(char *from, char *to );
void call_sum(char *first, char *sec, char *result);

int main()
{
    int n;
    int i, j, k, l, carry;
    char temp[MAX], temp2[MAX];
    for(i=4;i<1001;i++)
    {
        for(j=0; array[i-1][j];j++) temp[j]=(array[i-1][j]-'0')*2;
        temp[j]=0;
        for(k=j-1, carry=0;k+1;k--)
        {
            l=temp[k]+carry;
            temp[k]=l%10+'0';
            carry=l/10;
        }
        if(carry) for(k=j+1;k;k--) temp[k]=temp[k-1];
        temp[k]=carry+'0';
        call_sum(temp, &array[i-2][0], temp2);
        strcpy(temp, temp2);
        call_sum(temp, &array[i-3][0], temp2);
        strcpy(array[i], temp2);
    }
    while(scanf("%d", &n)==1)
    {
        l=strlen(array[n]);
        for(i=0;i<l;i++) putchar(array[n][i]);
        printf("\n");
    }
    return 0;
}

void reverse(char *from, char *to )
{
    int len=strlen(from);
    int l;
    for(l=0;l<len;l++)
    to[l]=from[len-l-1];
    to[len]='\0';
}

void call_sum(char *first, char *sec, char *result)
{
    char F[MAX], S[MAX], Res[MAX];
    int f,s,sum,extra,now;
    f=strlen(first);
    s=strlen(sec);
    reverse(first,F);
    reverse(sec,S);
    for(now=0,extra=0;(now<f && now<s);now++)
    {
        sum=(F[now]-'0') + (S[now]-'0') + extra;
        Res[now]=sum%10 +'0';
        extra= sum/10;
    }
    for(;now<f;now++){
        sum=F[now] + extra-'0';
        Res[now]=sum%10 +'0';
        extra=sum/10;
    }
    for(;now<s;now++)
    {
        sum=F[now] + extra-'0';
        Res[now]=sum%10 +'0';
        extra=sum/10;
    }
    if(extra!=0) Res[now++]=extra+'0';
    Res[now]='\0';
    if(strlen(Res)==0) strcpy(Res,"0");
    reverse(Res,result);
}

