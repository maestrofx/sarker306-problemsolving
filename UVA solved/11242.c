#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 50
#define EPS 1e-6

int cmp(const void *x, const void *y){
    long long *a=(long long*)x, *b=(long long*)y;
    if(*a==*b) return 0;
    if(*a>*b) return 1;
    return -1;
}

int cmp1(const void *x, const void *y){
    double *a=(double*)x, *b=(double*)y;
    if(*a==*b || fabs(*a-*b)<EPS) return 0;
    if(*a>*b) return 1;
    return -1;
}

int main(){
    long long first[MAX], sec[MAX];
    long i, j, k, m1, m2;
    double a[MAX*MAX], rat;
    
    while(scanf("%ld", &m1)!=EOF && m1){
        scanf("%ld", &m2);
        for(i=0;i<m1;i++) scanf("%lld", first+i);
        for(i=0;i<m2;i++) scanf("%lld", sec+i);
        /*(first, m1, sizeof(long long), cmp);
        qsort(sec, m2, sizeof(long long), cmp);
        /*for(i=0;i<m1;i++) printf("%lld ", first[i]); printf("\n");
        for(i=0;i<m2;i++) printf("%lld ", sec[i]);printf("\n");
        a[0]=sec[0]*1.0/first[m1-1], a[1]=sec[0]*1.0/first[m1-2], a[2]=sec[1]*1.0/first[m1-1], a[3]=sec[1]*1.0/first[m1-2];
        qsort(a, 4, sizeof(double), cmp1);
        printf("%.2lf\n", a[3]/a[2]);
        if(m1>1 && m2>1){
            a[0]=sec[m2-1]*1.0/first[0], a[1]=sec[m2-2]*1.0/first[0], a[2]=sec[m2-1]*1.0/first[1], a[3]=sec[m2-2]*1.0/first[1];
            qsort(a, 4, sizeof(double), cmp1);
            rat=a[3]/a[2];
        }
        else if(m1==1 && m2==1) rat=sec[0]*1.0/first[0];
        else{
            if(m1==1) a[0]=sec[1]*1.0/sec[0];
            else a[0]=first[1]*1.0/first[0];
            rat=a[0];
        }
        rat=((long long)(100*rat+0.5))/100.0;
        printf("%.2lf\n", rat);*/
        for(i=0, k=0;i<m1;i++){
            for(j=0;j<m2;j++) a[k++]=sec[j]*1.0/first[i];
        }
        
        qsort(a, k, sizeof(double), cmp1);
        for(i=0, rat=0;i<k-1;i++) if(a[i+1]>rat*a[i]) rat=a[i+1]/a[i];
        printf("%.2lf\n", rat);
    }
    
    return 0;
}
