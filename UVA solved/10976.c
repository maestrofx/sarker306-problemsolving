#include<stdio.h>

long count;
long array[10000][2];

void reset(){
    int i=0;
    
    for(i=0;i<=count;i++) array[i][0]=array[i][1]=0;
    count=0;
}

int main(){
    long k, i, m;
    
    while(scanf("%ld", &k)!=EOF){
        for(i=k+1, m=2*k; i<=m;i++){
            if((k*i)%(i-k)==0){
                array[count][0]=(k*i)/(i-k), array[count][1]=i;
                count++;
            }
        }
        
        printf("%ld\n", count);
        for(i=0;i<count;i++) printf("1/%ld = 1/%ld + 1/%ld\n", k, array[i][0], array[i][1]);
        reset();
    }
    
    return 0;
}
