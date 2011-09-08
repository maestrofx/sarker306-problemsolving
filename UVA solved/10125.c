#include<stdio.h>
#include<stdlib.h>
#define MAX 1001

typedef long long llong;
typedef struct{
    llong add, a, b;
}added;
llong array[MAX+2];
added add[MAX*MAX];

int cmp(const void *x, const void *y){
    llong *a=(llong*)x, *b=(llong*)y;
    if(*a==*b) return 0;
    if(*a>*b) return 1;
    return -1;
}

int cmp1(const void *x, const void *y){
    added *a=(added*)x, *b=(added*)y;
    if(a->add==b->add)return 0;
    if(a->add>b->add) return 1;
    return -1;
}

int main(){
    long n, i, j, k;
    char flag;
    added *ptr, tmp;
    
    while(scanf("%ld", &n)!=EOF && n){
        flag=0;
        for(i=0;i<n;i++) scanf("%lld", array+i);
        qsort(array, n, sizeof(llong), cmp);
        /*for(i=0;i<n;i++) printf("%lld ", *(array+i));
        printf("\n");*/
        for(i=k=0;i<n-1;i++)
            for(j=i+1;j<n;j++){
                add[k].add=array[i]+array[j], add[k].a=array[i], add[k].b=array[j];
                /*printf("%lld + %lld = %lld\n", add[k].a, add[k].b, add[k].add);*/
                k++;
            }
                
        qsort(add, k, sizeof(added), cmp1);
        /*for(i=0;i<k;i++) printf("%lld + %lld = %lld\n", add[i].a, add[i].b, add[i].add);
        printf("\n");*/
        for(i=n-1; i+1;i--){
            for(j=0;j<n;j++){
                if(j==i) continue;
                tmp.add=array[i]-array[j];
               /* printf("%lld  -  %lld    =        %lld\n", array[i], array[j], tmp);*/
                ptr=(added*)bsearch(&tmp, add, k, sizeof(added), cmp1 );
                if(ptr!=NULL){
                    for(;ptr->add==tmp.add;ptr--);
                    for(++ptr;ptr->add==tmp.add && !flag;ptr++){
                        if(ptr->a==array[j]||ptr->b==array[j]||ptr->a==array[i]||ptr->b==array[i]) continue;
                        /*printf("%lld + %lld = %lld\n", ptr->a, ptr->b, ptr->add);*/
                        flag=1;
                        break;
                    }
                }
                
                if(flag) break;
            }
            if(flag) break;
        }
        
        if(flag) printf("%lld\n", array[i]);
        else printf("no solution\n");
    }
    
    return 0;
}
