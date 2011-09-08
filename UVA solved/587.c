#include<stdio.h>
#include<string.h>
#include<math.h>

double rat = sqrt(0.5);
char inp[10000];
char token[100];

void parse(char *arr, double *x, double *y){
    char *tmp;
    int n;
    double a;

    while(*arr && *arr!='.'){
        while(*arr==' ' || *arr==',') arr++;
        if(isdigit(*arr)){
            n = 0;
            while(isdigit(*arr)) n = 10*n + *arr++ -'0';
            a = n*rat;
        }
        while(*arr==' ') arr++;
        if(isalpha(*arr)){
            tmp = token;
            while(isalpha(*arr)) *tmp++=*arr++;
            *tmp = 0;

            if(token[0]=='N'){
                switch(token[1]){
                    case 0   : *x = *x + n; break;
                    case 'E' : *x = *x + a, *y = *y + a; break;
                    case 'W' : *x = *x + a, *y = *y - a;
                }
            }
            else if(token[0]=='S'){
                switch(token[1]){
                    case 0   : *x = *x - n; break;
                    case 'E' : *x = *x - a, *y = *y + a; break;
                    case 'W' : *x = *x - a, *y = *y - a;
                }
            }
            else if(token[0]=='E') *y = *y + n;
            else *y = *y - n;
        }
    }
}

int main(){
    double x, y;
    int test=0;

    while(gets(inp)){
        x=0, y=0;
        if(strcmp("END", inp)==0) break;
        parse(inp, &y, &x);
        printf("Map #%d\n", ++test);
        printf("The treasure is located at (%.3lf,%.3lf).\nThe distance to the treasure is %.3lf.\n\n", x, y, sqrt(x*x+y*y));
    }

    return 0;
}
