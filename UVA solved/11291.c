#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char expr[100000];
char token[100], *prog;

void get_token(){
    char *tmp = token;

    while(*prog==' ') prog++;
    if(*prog=='(' || *prog==')' || *prog=='-') *tmp++ = *prog++;
    else while(*prog && *prog!=' ' && *prog!='(' && *prog!=')' && *prog!='-') *tmp++ = *prog++;

    *tmp=0;
    /*puts(token);*/
}

void eval_exp(double *ans){
    double temp1, temp2, temp3;

    get_token();
    if(token[0]=='('){
        eval_exp(&temp1);
        eval_exp(&temp2);
        eval_exp(&temp3);
        *ans = temp2 + ( 2 * temp1 - 1 ) * temp3;
        /*printf("   %lf\n", *ans);*/
        get_token();
    }
    else if(*token=='-'){
        eval_exp(ans);
        *ans = -(*ans);
        /*printf("             %lf\n", *ans);*/
    }
    else{
        *ans = atof(token);
        /*printf("             %lf\n", *ans);*/
    }
}

int main(){
    double ans;
    while(gets(expr)){
        if(expr[0]=='(' && expr[1]==')' && expr[2]==0) break;
        prog=expr;
        eval_exp(&ans);
        printf("%.2lf\n", ans);
    }

    return 0;
}
