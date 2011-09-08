#include<stdio.h>
#define SIZE 1000000

void print_LIS(long *array, long *parent, long n){
    if(parent[n]==0) return;
    print_LIS(array, parent, parent[n]);
    printf("%ld\n", -array[parent[n]]);
}

long lower_bound(long *array, long *key, long n, long x){
    long low=0, high=n+1, mid;

    while(low+1<high){
        mid=(low+high)>>1;
        if(x<key[array[mid]]) high=mid; /* <= for increasing */
        else low=mid;
    }

    return low;
}

long longest_increasing(long *array, long *parent, long *sqn, long n){
    long i, len=1, indx;

    array[0]=-32676, array[n+1]=32767;
    parent[0]=-1;
    for(i=1;i<n; i++) parent[i]=0, sqn[i]=0;
    sqn[n+1]=n+1;

    for(i=1;i<=n+1;i++){
        indx=lower_bound(sqn, array, len, array[i]);
        sqn[indx+1]=i;
        parent[i]=sqn[indx];
        if(indx==len) len++;
    }

    return len-2;
}

long n, array[SIZE+3], parent[SIZE+3], lis[SIZE+3];

int main(){
    long i=1, x, test=0;

    while(scanf("%ld", &x)!=EOF){
        if(x==-1){
            n=i-1;
            if(n==0) break;
            if(test) puts("");
            printf("Test #%ld:\n  maximum possible interceptions: %ld\n",
                   ++test, longest_increasing(array, parent, lis, n));
            /*print_LIS(array, parent, n+1);*/
            i=1;
        }
        else array[i++]=-x;
    }

    return 0;
}
