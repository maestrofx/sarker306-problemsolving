#include<stdio.h>
#define SIZE 1000002
char sieve[SIZE];
long circular[SIZE];

void check_circular(long n){
    char w[7][10];
    int i, j, x;
    long m[7];

    sprintf(w[0], "%ld", n);
    x = strlen(w[0]);
    for(i = 1 ; i < x ; i++ ){
        for(j = 1 ; w[i - 1][j]; j++) w[i][j] = w[i-1][j-1];
        w[i][0] = w[i-1][j-1];
        w[i][j] = 0;
        sscanf(w[i], "%ld", &m[i]);
        if(sieve[m[i]]) return;
    }

    for(i = 1 ; i < x ; i++ ) circular[m[i]] = 1;
    circular[n] = 1;
}

int main(){
    long i, j;

    for( i = 4 ; i < SIZE ; i += 2 ) sieve[i] = 1;
    for( i = 3 ; i <= 1000 ; i += 2 ){
        if( sieve[i] == 0 )
            for( j = i * i ; j < SIZE ; j += i) sieve[j] = 1;
    }

    for( i = 10 ; i < SIZE ; i++ ) if(sieve[i] == 0 && circular[i] == 0) check_circular(i);
    for( i = 10 ; i < SIZE ; i++) circular[i] += circular[i-1];
    while(scanf("%ld%ld", &i, &j)==2){
        j = circular[j] - circular[i-1];
        switch(j){
            case 0 : puts("No Circular Primes."); break;
            case 1 : puts("1 Circular Prime."); break;
            default: printf("%ld Circular Primes.\n", j);
        }
    }

    return 0;
}
