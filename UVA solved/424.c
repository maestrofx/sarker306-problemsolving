#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX 110

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
    for(;now<f;now++)
    {
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

int main()
{
    int len,i;
    char fir[MAX],sec[MAX],res[MAX];
    scanf("%s%s", fir, sec);
    call_sum(fir, sec, res);
    strcpy(fir, res);
    while(scanf("%s",sec)==1&& sec[0]!='0')
    {
        call_sum(fir,sec,res);
        strcpy(fir, res);
    }
    len=strlen(fir);
    for(i=0;i<len;i++) printf("%c",fir[i]);
    printf("\n");
    return 0;
}
