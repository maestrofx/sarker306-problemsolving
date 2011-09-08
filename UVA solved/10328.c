#include<stdio.h>
#include<string.h>
#define MAX 50
#define MAXN 101
#define MAXK 101

char array[MAXN][MAXK][MAX];
char power_2[MAXN][MAX];

void reverse(char *from, char *to ){
    int len=strlen(from);
    int l;
    for(l=0;l<len;l++)
    to[l]=from[len-l-1];
    to[len]='\0';
}

int call_minus(char *large, char *small, char *result){
    char L[MAX], S[MAX];
    int l,s,now,hold,diff,sign;
    
    l=strlen(large);
    s=strlen(small);
    if(l<s){
        strcpy(result,large);
        strcpy(large,small);
        strcpy(small,result);
        now=l; l=s; s=now;
        sign = 1;
    }
    if(l==s){
        if(strcmp(large, small)<0){
            strcpy(result,large);
            strcpy(large,small);
            strcpy(small,result);
            now=l; l=s; s=now;
            sign =1;
        }
    }
    reverse(large,L);
    reverse(small,S);
    for(;s<l;s++) S[s]='0';
    S[s]='\0';
    for(now=0,hold=0;now<l;now++){
        diff=L[now]-(S[now]+hold);
        if(diff<0){
            hold=1;
            result[now]=10+diff+'0';
        }
        else{
            result[now]=diff+'0';
            hold=0;
        }
    }
    for(now=l-1;now>0;now--){
        if(result[now]!='0') break;
    }
    result[now+1]='\0';
    reverse(result,L);
    strcpy(result,L);
   
    return sign;
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

void init(){
    int i, j;
    
    for(i=1, power_2[0][0]='1'; i<MAXN;i++){
        int_str_mult(power_2[i-1], 2, power_2[i]);
        for(j=1;j<=MAXK;j++){
            if(i==j) array[i][j][0]='1';
            else array[i][j][0]='0';
        }
    }
}

int main(){
    int i, j;
    char temp[MAX];
    
    init();
    for(i=1;i<MAXN;i++){
        for(j=1;j<i;j++){
            int_str_mult(array[i-1][j], 2, array[i][j]);
            call_sum(array[i][j], power_2[i-j-1], temp);
            call_minus(temp, array[i-j-1][j], array[i][j]);
        }
    }
    
    while(scanf("%d%d", &i, &j)==2) printf("%s\n", array[i][j]);
    
    return 0;
}
