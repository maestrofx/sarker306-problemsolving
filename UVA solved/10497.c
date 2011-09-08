#include<stdio.h>
#include<string.h>

#define SIZE 801
#define MAX 3000

char array[SIZE+2][MAX];

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

void int_str_mult(char *A, int n, char *B)
{
    int carry=0, i, x, j, prod;
    char p[200]={0};
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

int main(){
    int i;
    char temp[MAX];
    
    strcpy(array[0],"0");
    strcpy(array[1],"0");
    strcpy(array[2],"1");
    strcpy(array[3],"2");
    for(i=4;i<SIZE;i++){
        call_sum(array[i-1], array[i-2], temp);
        int_str_mult(temp, i-1, array[i]);
    }
    
    while(scanf("%d", &i)!=EOF){
        if(i<=0 || i>=SIZE) break;
        printf("%s\n", array[i]);
    }
    
    return 0;
}
