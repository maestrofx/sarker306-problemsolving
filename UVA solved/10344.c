#include<stdio.h>
#define DESTINY 23

long num[6];
int IsExpressible;

void backtrack(long val, int *a, int index){
    int i, j;
    
    if(index==5){
        if(val==DESTINY) IsExpressible=1;
        return;
    }
    
    for(i=0;i<5;i++){
        for(j=0;j<index;j++){
            if(a[j]==i) break;
        }
        if(j<index) continue;
        a[index]=i;
        backtrack(val+num[i], a, index+1);
        backtrack(val-num[i], a, index+1);
        backtrack(val*num[i], a, index+1);
    }
}

void khojthesearch(){
    int i;
    int p[5];
    
    for(i=0;i<5;i++){
        p[0]=i;
        backtrack(num[i], p, 1);
    }
}

int main(){
    int i, flag;
    
    while(1){
        for(i=0, flag=IsExpressible=0;i<5;i++){
            scanf("%ld", &num[i]);
            if(num[i]) flag=1;
        }
        
        if(!flag) break;
        khojthesearch();
        if(IsExpressible) printf("Possible\n");
        else printf("Impossible\n");
    }
    
    return 0;
}
