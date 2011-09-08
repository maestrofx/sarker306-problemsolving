#include<stdio.h>
#define SIZE 10001

typedef long long ll;
ll ways[SIZE+5];

int main(){
    int n, m, i;

    ways[0]=1;
    for(n=i=1;n<SIZE;n=i*i*i){
        for(m=n;m<SIZE;m++) ways[m]+=ways[m-n];
        i++;
    }

    while(scanf("%d", &n)!=EOF) printf("%lld\n", ways[n]);
    return 0;
}
