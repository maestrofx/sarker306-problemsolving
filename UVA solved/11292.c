#include<stdio.h>
#include<stdlib.h>
#define SIZE 20005

long dragonhead[SIZE], knightheight[SIZE];

int cmp(const void *a, const void *b){
	long *x=(long*)a, *y=(long*)b;
    return *x-*y;
}

int main(){
    long n, m, i, j, cuthead;
    long cost;

    while(scanf("%ld%ld", &n, &m)!=EOF){
        if(!n && !m) break;
        for(i=0;i<n;i++) scanf("%ld", dragonhead+i);
        for(i=0;i<m;i++) scanf("%ld", knightheight+i);
        qsort(dragonhead, n, sizeof(long), cmp);
        qsort(knightheight, m, sizeof(long), cmp);
        for(i=0, j=0, cost=0, cuthead=0;i<n && j<m;j++){
            if(knightheight[j]>=dragonhead[i]) cost+=knightheight[j], cuthead++, i++;
        }
        if(cuthead!=n) printf("Loowater is doomed!\n");
        else printf("%ld\n", cost);
    }

    return 0;
}
