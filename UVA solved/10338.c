#include<stdio.h>

unsigned long long factorial[21]={1,1,2};

int main(){
    int data;
    int i, j;
    unsigned long long x;
    int frq[26];
    char word[30];
    char *p;
    
    for(i=3;i<=20;i++) factorial[i]=factorial[i-1]*i;
    scanf("%d", &data);
    for(i=1;i<=data;i++){
        for(j=0;j<26;j++) frq[j]=0;
        scanf("%s", word);
        for(p=word;*p;p++) frq[*p-'A']++;
        
        for(x=1, j=0;j<26;j++) x*=factorial[frq[j]];
        printf("Data set %d: %llu\n", i, factorial[p-word]/x);
    }
    
    return 0;
}
