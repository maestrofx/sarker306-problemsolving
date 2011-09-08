#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char name[15];
    int rank;
    long money;
}names;

names array[15];

int comp(const void *a, const void *b){
    return strcmp(((names*)a)->name, ((names*)b)->name);
}

int comp1(const void *a, const void *b){
    return ((names*)a)->rank-((names*)b)->rank;
}

int main(){
    int n, i, j, x, test=0;
    long money;
    char word[15];
    names *ptr, *ptr1, hmm;
    
    while(scanf("%d", &n)!=EOF){
        for(i=0;i<n;i++) scanf("%s", &array[i].name), array[i].rank=i, array[i].money=0;
        qsort(array, n, sizeof(names), comp);
        for(i=0;i<n;i++){
            scanf("%s", hmm.name);
            ptr=bsearch(&hmm, array, n, sizeof(names), comp);
            scanf("%ld%d", &money, &x);
            if(x==0) continue;
            money-=money%x;
            ptr->money-=money;
            money/=x;
            for(j=0;j<x;j++){
                scanf("%s", hmm.name);
                ptr1=bsearch(&hmm, array, n, sizeof(names), comp);
                ptr1->money+=money;
            }
        }
        
        qsort(array, n, sizeof(names), comp1);
        if(test++) printf("\n");
        for(i=0;i<n;i++) printf("%s %ld\n", array[i].name, array[i].money);
    }
    
    return 0;
}
