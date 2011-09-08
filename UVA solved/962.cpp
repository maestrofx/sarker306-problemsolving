#include<stdio.h>
#include<stdlib.h>
#include<map>

#define MAX 1002
#define LIMIT 1003625000

using namespace std;
long array[MAX*2];
long cube[MAX];
long _count=1;

int cmp(const void *x, const void *y){
    long diff=*(long*)x-*(long*)y;
    if(diff>0) return 1;
    else if(diff<0) return -1;
    else return 0;
}

int main(){
    long i, j, temp, low, high;
    long a, b, c1, c2;
    map<long, int>mapi;
    map<long, int>::iterator pmap;
    
    for(i=0;i<MAX;i++) cube[i]=i*i*i;
    for(i=1;i<MAX;i++){
        low=cube[i];
        for(j=i;j<MAX;j++){
            temp=low+cube[j];
            if(temp>LIMIT) break;
            if((pmap=mapi.find(temp))==mapi.end()) mapi.insert(pair<long, int>(temp, 1));
            else if(pmap->second==1){
                (pmap->second)++;
                array[_count++]=temp;
            }
        }
    }
    //printf("%ld\n", _count);
    qsort(array, _count, sizeof(long), cmp);
    
    while(scanf("%ld%ld", &low, &high)!=EOF){
        high+=low;
        a=0, b=_count;
        while(a+1<b){
            c1=(a+b)>>1;
            if(array[c1]>low) b=c1;
            else a=c1;
        }
        if(array[c1]>=low) while(array[c1]>=low) c1--;
        //printf("%ld %ld %ld\n", array[c1], low, array[c1+1]);
        /*a=0, b=_count;
        while(a+1<b){
            c2=(a+b)>>1;
            if(array[c2]>high) b=c2;
            else a=c2;
        }
        if(array[c2]<=high) while(array[c2]<=high) c2++;*/
        //printf("%ld %ld %ld\n", array[c2], high, array[c2+1]);
        if(array[c1+1]>high) printf("None\n");
        else for(i=c1+1;array[i]<=high;i++) printf("%ld\n", array[i]);
    }
    
    mapi.clear();
    return 0;
}
