#include<stdio.h>
#define SIZE 1000000

void print_LIS(long *array, long *parent, long n){
    if(parent[n]==0) return;
    print_LIS(array, parent, parent[n]);
    printf("%ld\n", array[parent[n]]);
}

long lower_bound(long *array, long *key, long n, long x){
    long low=0, high=n+1, mid;

    while(low+1<high){
        mid=(low+high)>>1;
        if(x<=key[array[mid]]) high=mid; /* < for non-decreasing */
        else low=mid;
    }

    return low;
}

long longest_increasing(long *array, long *parent, long *sqn, long n){
    long i, len=1, indx;

    array[0]=-2147483648, array[n+1]=2147483647;
    parent[0]=-1;
    for(i=1;i<n; i++) parent[i]=0, sqn[i]=0;
    sqn[n+1]=n+1;

    for(i=1;i<=n+1;i++){
        indx=lower_bound(sqn, array, len, array[i]);
      /*  printf("Lower bound of %ldth element in input, %ld is %ldth element in LIS, %ldth element in input, %ld\n",
            i, array[i], indx, sqn[indx], array[sqn[indx]]); */
        sqn[indx+1]=i;
        parent[i]=sqn[indx];
        if(indx==len) len++/*, printf("Len incrased\n")*/;
    }

    if(len>1) return len-2;
    else return 0;
}

long n, array[SIZE+3], parent[SIZE+3], lis[SIZE+3];

int main(){
    long i, test;
    char input[20000];

    while(scanf("%ld", &test)!=EOF){
        getchar();
        getchar();
        while(test--){
            for(i=1; ;i++){
                if(gets(input)==0) break;
                if(input[0]==0) break;
                sscanf(input, "%ld", &array[i]);
            }

            n=i-1;

            printf("Max hits: %ld\n", longest_increasing(array, parent, lis, n));
            print_LIS(array, parent, n+1);
            if(test) puts("");
        }
    }

    return 0;
}
/* 10 3 4 36 14 02 485 76 54 012 15 */
