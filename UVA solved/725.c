#include<stdio.h>

int main(){
    long n, flag, x, i, cases=0;
    char isUsed[10], tmp[10], isAns[100];

    for(i=0;i<100;i++) isAns[i]=1;
    isAns[79]=0;
    isAns[78]=0;
    isAns[77]=0;
    isAns[76]=0;
    isAns[75]=0;
    isAns[74]=0;
    isAns[73]=0;
    isAns[72]=0;
    isAns[71]=0;
    isAns[70]=0;
    isAns[69]=0;
    isAns[67]=0;
    isAns[65]=0;
    isAns[64]=0;
    isAns[63]=0;
    isAns[61]=0;
    isAns[60]=0;
    isAns[58]=0;
    isAns[57]=0;
    isAns[56]=0;
    isAns[55]=0;
    isAns[54]=0;
    isAns[51]=0;
    isAns[50]=0;
    isAns[49]=0;
    isAns[48]=0;
    isAns[47]=0;
    isAns[45]=0;
    isAns[42]=0;
    isAns[41]=0;
    isAns[40]=0;
    isAns[39]=0;
    isAns[36]=0;
    isAns[34]=0;
    isAns[33]=0;
    isAns[31]=0;
    isAns[30]=0;
    isAns[25]=0;
    isAns[21]=0;
    isAns[20]=0;
    isAns[11]=0;
    isAns[10]=0;

    while(scanf("%ld", &n) != EOF && n){
        flag = 0;
        if(cases) puts("");

        if(isAns[n] != 0) for( x = 0 ; x < 100000 ; x++ ){
            for( i = 0 ; i < 10 ; i++ ) isUsed[i] = 0;
            sprintf(tmp, "%05ld", x);
            for( i = 0 ; tmp[i]; i++ ) isUsed[tmp[i]-'0']++;
            sprintf(tmp, "%05ld", x*n);
            for( i = 0 ; tmp[i]; i++ ) isUsed[tmp[i]-'0']++;
            if(i == 5){
                for( i = 0 ; i < 10 ; i++ ) if(isUsed[i] != 1) break;
                if( i == 10 ){
                    flag=1;
                    printf("%05ld / %05ld = %ld\n",x*n, x, n);
                }
            }
        }

        if(flag == 0) printf("There are no solutions for %ld.\n", n);

        cases++;
    }

    return 0;
}
