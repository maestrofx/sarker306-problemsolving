#include<stdio.h>
#define SIZE 1000000
#define SQRTSIZE 1000

short int moebius[SIZE+2];
long M[SIZE+2];
int dist_factors[SIZE+2];
int factors[SIZE+2];

int main(){
    long long i, j;
    long n;
    
    for(i=2;i<=SIZE;i+=2) dist_factors[i]++, factors[i]=factors[i/2]+1;
    
    for(i=3;i<=SIZE;i+=2){
        if(dist_factors[i]==0){
            for(j=i;j<=SIZE;j+=i)
                dist_factors[j]++, factors[j]=factors[j/i]+1;
            }
    }
    
    for(moebius[1]=1, i=2;i<=SIZE;i++){
        if(factors[i]==dist_factors[i]) moebius[i]=(factors[i]&1)? -1: 1;
        else moebius[i]=0;
    }
    
    for(i=1;i<=SIZE;i++) M[i]=M[i-1]+moebius[i];
    
    while(scanf("%ld", &n)!=EOF && n>0) printf("%8ld%8hd%8ld\n", n, moebius[n], M[n]);
    
    return 0;
}
