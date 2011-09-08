#include<stdio.h>
char input[100];

int main(){
    int a, b, c, i, cor=0, sign;
    
    while(gets(input)){
        i=0;
        for(i=0, a=0; input[i]!='+' && input[i]!='-';i++) {
            if(input[i]>='0' && input[i]<='9') a=10*a+input[i]-'0';
        }
        
        sign = (input[i]=='+')*1 - (input[i]=='-')*1;
        
        while(input[i]<'0' || input[i]>'9') i++;
        for(b=0; input[i]!='=';i++) {
            if(input[i]>='0' && input[i]<='9') b=10*b+input[i]-'0';
        }
        
        while( (input[i]<'0' || input[i]>'9') && input[i]!='?' && input[i]) i++;
        for(c=0; input[i]!='?' && input[i];i++) {
            if(input[i]>='0' && input[i]<='9') c=10*c+input[i]-'0';
        }
        
        if(input[i]!='?' && a+b*sign==c) cor++;
    }
    
    printf("%d\n", cor);
    
    return 0;
}
