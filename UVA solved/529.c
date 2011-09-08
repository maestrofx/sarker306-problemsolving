#include<stdio.h>
#include<stdlib.h>
#define SIZE 10005
#define TOLERANCE 2

long length, n, flag;
long minlength, minsol[SIZE];

int increasing(long *sequence, long length){
    long i=length-1;
    
    if(sequence[i-1]>=sequence[i]) return 0;
    
    return 1;
}

void backtrack(long *a, long *visited, long length){
    long i, j, flag_inc=1;
    
    if(a[length-1]==n){
        for(i=0;i<length;i++) minsol[i]=a[i];
        minlength=length;
        flag++;
        return;
    }
    
    for( i=length-1 ; i+1 && flag_inc;i-- ){
        for( j=i ; j+1 && flag_inc ; j-- ){
            if(a[i]+a[j]<=n){
                if(visited[a[i]+a[j]]==-1 && length+1<minlength){
                    a[length]=a[i]+a[j];
                    visited[a[length]]=1;
                    if( increasing(a, length+1) ) {
                        if(flag && TOLERANCE*a[length]<minsol[length]) flag_inc=0;
                        else backtrack(a, visited, length+1);
                    }
                    else flag_inc=0;
                    visited[a[length]]=-1;
                }
                
                if(length+1>=minlength) return;
            }
        }
    }
}

void nafisearch(void){    /* nafi vai, doa koiren, apnar name e shuru korlm */
    long array[SIZE], inSequence[SIZE], i;
    
    flag=0;
    minlength=18;
    for(i=0;i<SIZE;i++) array[i]=i+1, inSequence[i]=-1;
    array[0]=1, inSequence[1]=1;
    backtrack(array, inSequence, 1);
}

int main(){
    long i;
    
    while(scanf("%ld", &n)!=EOF && n){
        nafisearch();
        printf("1");
        for(i=1;i<minlength;i++) printf(" %ld", minsol[i]);
        printf("\n");
    }
    
    return 0;
}
