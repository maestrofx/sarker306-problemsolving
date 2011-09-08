#include<stdio.h>
#include<string.h>
#define MAX 450

char array[1001][450]={"0", "1", "3"};

void reverse(char *from, char *to );
void call_sum(char *first, char *sec, char *result);

int main(){
    int n, test;
    int i, j, k, l, carry;
    char temp[MAX], temp2[MAX];
	
    for(i=3;i<1001;i++){
		call_sum(array[i-1], array[i-2], temp);
		sprintf(temp2, "%d", i);
        call_sum(temp, temp2, array[i]);
    }
	
    while(scanf("%d", &test)==1){
		for(j=0;j<test;j++){
			scanf("%d", &n);
			if(n>0) printf("%s\n", array[n]);
			else printf("0\n");
		}
    }
	
    return 0;
}

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
