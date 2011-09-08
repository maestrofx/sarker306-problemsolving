#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define SIZE 65536
#define EPS 1e-6

typedef long long llong;
char isnp[SIZE];
char array[100000][25], *ptr[100000];
long count;

int cmp(const void *a, const void *b){
    int x=strlen(*(char**)a), y=strlen(*(char**)b);
    if(x-y) return x-y;
    return strcmp(*(char**)a, *(char**)b);
}

int cmp1(const void *a, const void *b){
    int x=strlen((char*)a), y=strlen((char*)b);
    if(x-y) return x-y;
    return strcmp((char*)a, (char*)b);
}

void int_str_mult(char *A, llong n, char *B){
    llong carry=0, prod;
    int i, x, j;
    char p[25]={0};

    x=strlen(A);
    for(i=x-1; i+1;i--){
        prod=(A[i]-'0')*n+carry;
        B[i]=prod%10+'0';
        carry=prod/10;
    }

    B[x]=0;
    if(carry){
        prod=carry;
        for(j=0;prod;j++, prod/=10) p[j]=prod%10+'0';
        for(i=x;i+1;i--) B[i+j]=B[i];
        j--;
        for(i=0;j>=0;j--, i++) B[i]=p[j];
    }
}

int main(){
    long i, j, k;
    llong ans=1<<31;
    double r;
    char temp[25], temp1[25], limit[25];

    sprintf(limit, "18446744073709551616");

    for(i=4;i<SIZE;i+=2) isnp[i]=1;
    for(i=3;i<256;i+=2){
        if(isnp[i]==0){
            for(j=i*i;j<SIZE;j+=i) isnp[j]=1;
        }
    }

    for(i=2;i<=SIZE;i++){
        ans=i;
        ans*=i;
        sprintf(temp1, "%llu", ans);
        int_str_mult(temp1, ans, temp);
        for(j=4; cmp1(temp, limit)<0; j++){
            if(isnp[j]){
                strcpy(array[count], temp);
                ptr[count++]=array[count];
            }
            int_str_mult(temp, i, temp1);
            strcpy(temp, temp1);
        }
    }

    /*printf("%ld\n", count);*/
    printf("1\n");
    qsort(ptr, count, sizeof(char**), cmp);
    for(i=0;i<count;i++){
        printf("%s\n", ptr[i]);
        while(i+1<count && strcmp(ptr[i], ptr[i+1])==0) i++;
    }

    return 0;
}
