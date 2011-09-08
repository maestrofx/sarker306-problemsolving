#include<stdio.h>

#define WEIGHT 25000
#define SIZE 102

long max(long a, long b){
    return (a>b)?a:b;
}

long Wi[SIZE+3], C[SIZE+3][WEIGHT+3];

int main(){
    long N, MW, sum, i, w, test;

    while(scanf("%ld", &test)!=EOF){
        while(test--){
            scanf("%ld", &N);
            for(i=1, MW=0;i<=N;i++){
                scanf("%ld", Wi+i);
                MW+=Wi[i];
            }

            sum=MW;
            MW>>=1;

            for (i=0;i<=N ;i++) C[i][0] = 0;
            for (w=0;w<=MW;w++) C[0][w] = 0;

            for (i=1;i<=N;i++) {
                for (w=1;w<=MW;w++){
                    if (Wi[i]>w)
                        C[i][w]=C[i-1][w];
                    else
                        C[i][w]=max(C[i-1][w], C[i-1][w-Wi[i]]+Wi[i]);
                }
            }

            printf("%ld\n", sum-2*C[N][MW]);
        }
    }

    return 0;
}
