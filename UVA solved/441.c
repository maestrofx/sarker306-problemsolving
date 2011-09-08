#include<stdio.h>

int num[20], k;

void backtrack(int *a, int index){
    int i;
    int available[50];
    
    if(index==6){
        printf("%d", num[a[0]]);
        for(i=1;i<index;i++) printf(" %d", num[a[i]]);
        puts("");
        return;
    }
    
    for(i=0;i<=k;i++) available[i]=0;
    for(i=0;i<index;i++) available[a[i]]=1;
    for(i=index;i<k;i++){
        if(available[i]==0){
            a[index]=i;
            if(num[i]>=num[a[index-1]]) backtrack(a, index+1);
        }
    }
}

void print_solution(){
    int i, j=k-6, array[20];
    
    for(i=0;i<=j;i++){
        array[0]=i;
        backtrack(array, 1);
    }
}

int main(){
    int i, test=0;
    
    while(scanf("%d", &k)!=EOF && k>6){
        for(i=0;i<k;i++) scanf("%d", num+i);
        if(test++) puts("");
        print_solution();
    }
    
    return 0;
}
