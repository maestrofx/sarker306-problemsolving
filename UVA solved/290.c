#include<stdio.h>
#include<string.h>
#define MAX 1000

void reverse(char *from, char *to ){
    int len=strlen(from);
    int l;
    for(l=0;l<len;l++)
    to[l]=from[len-l-1];
    to[len]='\0';
}

void call_sum(char *first, char *sec, char *result, int base){
    char F[MAX], S[MAX], Res[MAX];
    int f,s,sum,extra,now;
    
    f=strlen(first);
    s=strlen(sec);
    reverse(first,F);
    reverse(sec,S);
    for(now=0,extra=0;(now<f && now<s);now++){
        sum=(F[now]-'0') + (S[now]-'0') + extra;
        Res[now]=sum%base +'0';
        extra= sum/base;
    }
    for(;now<f;now++){
        sum=F[now] + extra-'0';
        Res[now]=sum%base +'0';
        extra=sum/base;
    }
    for(;now<s;now++){
        sum=F[now] + extra-'0';
        Res[now]=sum%base +'0';
        extra=sum/base;
    }
    if(extra!=0) Res[now++]=extra+'0';
    Res[now]='\0';
    if(strlen(Res)==0) strcpy(Res,"0");
    reverse(Res,result);
}

int steps_palindrome(char *str, int base){
    char str1[MAX], str2[MAX];
    int step=0;
    
    do{
        reverse(str, str1);
        if(strcmp(str, str1)==0) break;
        call_sum(str, str1, str2, base);
        step++;
        strcpy(str, str2);
    }while(1);
    
    return step;
}

int main(){
    char str[MAX], temp[MAX];
    int i, minbase;
    
    /*freopen("290.txt", "w", stdout);*/
    while(scanf("%s", str)!=EOF){
        for(i=0, minbase=0; str[i]; i++){
            if(str[i]>='A') str[i]=str[i]-'A'+'9'+1;
            minbase=(minbase>str[i]-'0')?minbase:str[i]-'0';
        }
        
        if(minbase==0) minbase=1;
        strcpy(temp, str);
        printf("%d", steps_palindrome(temp, 15));
        for(i=14;i>minbase;i--){
            strcpy(temp, str);
            printf(" %d", steps_palindrome(temp, i));
        }
        
        for(i;i>=2;i--) printf(" ?");
        printf("\n");
    }
    
    return 0;
}
