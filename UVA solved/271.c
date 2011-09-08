#include<stdio.h>
#include<ctype.h>
#include<string.h>

char *prog;

int check_syntax(){
    char token = *prog++;
    if( token == 0 ) return 0;
    if(strchr("CDEI", token )){
        if( check_syntax() == 0 ) return 0;
        if( check_syntax() == 0 ) return 0;
    }
    else if(strchr("Npqrstuvuxyz", token)){
        if( token == 'N' && check_syntax()== 0) return 0;
    }

    return 1;
}

int main(){
    char syntax[10000];

    while(gets(syntax)){
        prog = syntax;
        (check_syntax() && *prog == 0) ? puts("YES") : puts("NO");
    }

    return 0;
}
