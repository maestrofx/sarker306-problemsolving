#include<stdio.h>

#define SIZE 1000001
#define INF 1<<30

long L[SIZE], R[SIZE], array[SIZE];

long merge(long left, long mid, long midd, long right){
    long i, j, k, n1, n2, count=0;
    
    for(i=0, n1=mid-left+1;i<n1;i++) L[i]=array[left+i];
    for(i=0, n2=right-midd+1;i<n2;i++) R[i]=array[midd+i];
    
    for(k=left, i=0, j=0; i<n1 && j<n2; k++){
        if(L[i]<=R[j]) array[k]=L[i++];
        else{
            count+=n1-i;
            array[k]=R[j++];
        }
    }
    
    for( ; i<n1 ; i++, k++) array[k]=L[i];
    for( ; j<n2 ; j++, k++) array[k]=R[j];
    
    return count;
}

long merge_sort(long left, long right){
    long mid=(left + right)>>1;
    long inversion_count=0;
    
    if(left==right) return 0;
    inversion_count=merge_sort(left, mid);
    inversion_count+=merge_sort(mid+1, right);
    inversion_count+=merge(left, mid, mid+1, right);
    
    return inversion_count;
}

int main(){
    long i, n;
    
    while(scanf("%ld", &n)!=EOF){
        for(i=0;i<n;i++) scanf("%ld", array+i);
        printf("%ld\n", merge_sort(0, n-1));
    }
    
    return 0;
}
