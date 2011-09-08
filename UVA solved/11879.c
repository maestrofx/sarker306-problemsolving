#include<stdio.h>
char input[100];

int main(){
    int res, i, cor=0;
    
    while(gets(input)){
        for(i=0;input[i]=='0';i++);
        if(input[i]==0) break;
        for(i=0, res=0; input[i]; i++) res=(10*res+input[i]-'0')%17;
        printf("%d\n", res? 0 : 1);
    }
     
    return 0;
}
