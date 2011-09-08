#include<stdio.h>

int main(){
    int test, amax, amin, bmax, bmin, mmax, mmin, k, i, j;
    long long answer;

    while(scanf("%d", &test)!=EOF){
        for(k=1;k<=test;k++){
            scanf("%d%d%d%d%d%d", &amin, &amax, &bmin, &bmax, &mmin, &mmax);
            for(answer=0, i=bmin;i<=bmax;i++)
                for(j=mmin;j<=mmax;j++)
                    if((2*i)%j==0) answer++;

            printf("Case %d: %lld\n", k, answer*(amax-amin+1));
        }
    }

    return 0;
}
