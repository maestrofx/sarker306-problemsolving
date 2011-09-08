#include<stdio.h>
#include<string.h>
#define MAXB 130
#define MAXN 102
#define MAX 250

char array[MAXB+2][MAXN+2][2][220];

void reverse(char *from, char *to ){
    int len=strlen(from);
    int l;
    for(l=0;l<len;l++)
    to[l]=from[len-l-1];
    to[len]='\0';
}

void call_sum(char *first, char *sec, char *result){
    char F[MAX], S[MAX], Res[MAX];
    int f,s,sum,extra,now;
    f=strlen(first);
    s=strlen(sec);
    reverse(first,F);
    reverse(sec,S);
    for(now=0,extra=0;(now<f && now<s);now++){
        sum=(F[now]-'0') + (S[now]-'0') + extra;
        Res[now]=sum%10 +'0';
        extra= sum/10;
    }
    for(;now<f;now++){
        sum=F[now] + extra-'0';
        Res[now]=sum%10 +'0';
        extra=sum/10;
    }
    for(;now<s;now++){
        sum=F[now] + extra-'0';
        Res[now]=sum%10 +'0';
        extra=sum/10;
    }
    if(extra!=0) Res[now++]=extra+'0';
    Res[now]='\0';
    if(strlen(Res)==0) strcpy(Res,"0");
    reverse(Res,result);
}

void int_str_mult(char *A, int n, char *B){
    int carry=0, i, x, j, prod;
    char p[20]={0};
    x=strlen(A);
    for(i=x-1, B[x]=0; i+1;i--){
        prod=(A[i]-'0')*n+carry;
        B[i]=prod%10+'0';
        carry=prod/10;
    }
    if(carry){
        prod=carry;
        for(j=0;prod;j++, prod/=10) p[j]=prod%10+'0';
        for(i=x;i+1;i--) B[i+j]=B[i];
        j--;
        for(i=0;j>=0;j--, i++) B[i]=p[j];
    }
}

int main(){
    int b, n, i, j;
    char temp[250], tempp[250];
    
    while(scanf("%d%d", &b, &n)==2){
        if(!b && !n) break;
        if(array[b][n][0][0]==0){
            array[b][0][0][0]='1', array[b][0][1][0]='0';
            for(i=1;i<MAXN;i++){
                int_str_mult(array[b][i-1][0], b-1, temp);
                int_str_mult(array[b][i-1][1], b-2, tempp);
                call_sum(temp,tempp,  array[b][i][0]);
                call_sum(array[b][i-1][0],array[b][i-1][1],  array[b][i][1]);
                /*printf("%s %s %s %s %s %s\n", array[b][i-1][0], array[b][i-1][1], temp, tempp, array[b][i][0], array[b][i][1]);*/
            }
            
            array[b][0][0][0]='0';
        }
        
        printf("%s\n", array[b][n][0]);
    }
    
    return 0;
}

/*
5187594877755244909607508825578214682680509938704885990290989226078775987490839766312159684079569869773624672671391180066115284161934579862199664103542063545831762780156180153274878732489659040159075574879443201
*/
