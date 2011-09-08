#include<stdio.h>

char str[2000];

int main(){
    int i, flag, n;

    while(scanf("%d%s", &n, str)!=EOF){
        if(!n && str[0]=='0' && !str[1]) break;
        for(i=0, flag=0; str[i]; i++){
            if(str[i]==n+'0') continue;
            if(!flag && str[i]>'0') flag=1;
            if(flag) putchar(str[i]);
        }

        if(flag==0) printf("0");
        puts("");
    }

    return 0;
}
