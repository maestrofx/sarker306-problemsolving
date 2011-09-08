#include<stdio.h>
#include<stdlib.h>
#define MAX 32

typedef long long llong;
llong array[MAX+2];

int cmp(const void *x, const void *y){
    llong *a=(llong*)x, *b=(llong*)y;
    if(*a==*b) return 0;
    if(*a>*b) return 1;
    return -1;
}

int dfscheck(llong value, llong *item, int index, int size){
    llong xx, *ptr;
    int i, flag=1;
    
    for(i=index+1;i<size && flag;i++){
        xx=value+item[i];
        ptr=(llong*)bsearch(&xx, array, size, sizeof(llong), cmp);
        if(ptr) return 0;
        if(xx<=array[size-1]) flag=dfscheck(xx, item, i, size);
    }
    return flag;
}
 
int check_a_seq(llong *item, int n){
    int i;
    llong tmp=*item;
    
    if(tmp<1) return 0;
    for(i=1;i<n;i++){
        if(tmp>=item[i]) return 0;
        tmp=item[i];
    }
    
    for(i=0;i<n;i++){
        if(!dfscheck(item[i], item, i, n)) return 0;
    }
    
    return 1;
}

int main(){
    int test=0, n, i;
    
    while(scanf("%d", &n)!=EOF){
        for(i=0;i<n;i++) scanf("%lld", array+i);
        /*qsort(array, n, sizeof(llong), cmp);*/
        printf("Case #%d:", ++test); for(i=0;i<n;i++) printf(" %lld", array[i]); printf("\n");
        printf("This is %san A-sequence.\n", (check_a_seq(array, n))?"": "not ");
    }
    
    return 0;
}
