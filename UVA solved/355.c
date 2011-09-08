#include <stdio.h>

char val[128];
int main(){
    int b1, b2, i;
    char inp[100];
    unsigned long long n;

    for(i=0;i<28;i++) val[i]=127;
    for(i=0;i<10;i++) val[i+'0']=i, val[i]=i+'0';
    for(i=10;i<16;i++) val[i]=i+'A'-10;
    val['A']=10, val['B']=11, val['C']=12, val['D']=13, val['E']=14, val['F']=15;
    val['a']=10, val['b']=11, val['c']=12, val['d']=13, val['e']=14, val['f']=15;

    while(scanf("%d%d%s", &b1, &b2, inp)!=EOF){
        for(i=n=0;inp[i];i++){
            if(val[inp[i]]>=b1) break;
            n=b1*n+val[inp[i]];
        }

        if(inp[i]) printf("%s is an illegal base %d number\n", inp, b1);
        else{
            printf("%s base %d = ", inp, b1);
            for(i=0;n;i++, n/=b2) inp[i]=val[n%b2];
            if(i==0) inp[i++]='0';
            for(--i;i>=0;i--) putchar(inp[i]);
            printf(" base %d\n", b2);
        }
    }

    return 0;
}
