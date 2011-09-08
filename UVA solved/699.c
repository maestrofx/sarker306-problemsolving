#include<stdio.h>
#define SIZE 200

long left, right;
long leaves[SIZE];

void reset(){
    long i;
    
    for(i=left;i<=right;i++) leaves[i]=0;
    left=right=SIZE>>1;
}

int input(long index){
    long n;
    
    scanf("%ld", &n);
    if(n==-1) return 0;
    
    leaves[index]+=n;
    if(left>index) left=index;
    if(right<index) right=index;
    input(index-1);
    input(index+1);
    return 1;
}

void output(){
    long i;
    static long test=1;
    
    printf("Case %ld:\n", test++);
    printf("%ld", leaves[left]);
    for(i=left+1;i<=right;i++) printf(" %ld", leaves[i]);
    printf("\n\n");
}

int main(){
    left=right=SIZE>>1;
    
    while(input(SIZE>>1)){
        output();
        reset();
    }
    
    return 0;
}
