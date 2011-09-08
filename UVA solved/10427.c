#include<stdio.h>

long array[]={0,9,189,2889,38889,488889,5888889,68888889,788888889};
long number[]={0,9,99,999,9999,99999,999999,9999999,99999999};

int main(){
    int i;
    long N, x, m=0;
    char str[15];
    
    while(scanf("%ld", &N)!=EOF){
        for(i=0;array[i]<N;i++) ;
        N-=array[i-1], x=N+i-1;
        m=(x/i)*i-N;
        /*printf("%ld %ld %ld %d ", N, x, i, m);*/
        N=number[i-1]+(x/i);
        sprintf(str,"%ld", N);
        printf("%c\n", str[i-m-1]);
    }
    
    return 0;
}
