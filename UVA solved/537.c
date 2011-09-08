#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char value[128];
double fll[128];

int main(){
    int test, kase;
    char ch, tmp, num[25], i;
    
    while(scanf("%d", &test) != EOF){
        getchar();
        for( kase = 1 ; kase <= test ; kase++ ){
            value['P'] = value['U'] = value['I'] = 0;
            
            while((ch = getchar()) != '\n'){
                if( ch == 'P' || ch == 'U' || ch == 'I'){
                    tmp = ch;
                    if((ch = getchar()) != '=') tmp = 0;
                    else{
                        i = 0 ;
                        while(isdigit(ch = getchar()) || ch == '.') num[i++] = ch;
                        num[i] = 0;
                        value[tmp] = 1;
                        fll[tmp] = atof(num);
                        switch(ch){
                            case 'M' : fll[tmp] *= 1000000; break;
                            case 'k' : fll[tmp] *= 1000; break;
                            case 'm' : fll[tmp] /= 1000; break;
                        }
                    }
                }
            }
            
            printf("Problem #%d\n", kase);
            if(value['P'] == 0) printf("P=%.2lfW\n\n", fll['U']*fll['I']);
            else if(value['U'] == 0) printf("U=%.2lfV\n\n", fll['P']/fll['I']);
            else printf("I=%.2lfA\n\n", fll['P']/fll['U']);
        }
    }
    
    return 0;
}
