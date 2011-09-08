#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cmp1(const void *a, const void *b){ return *(char*)a-*(char*)b; }
int cmp2(const void *a, const void *b){ return *(char*)b-*(char*)a; }

int main(){
    char str[20], tmp[20];
    int ln, i;
    long long x, y, z;
    
    while(scanf("%s", str)!=EOF){
        strcpy(tmp, str);
        ln=strlen(str);
        qsort(tmp, ln, sizeof(char), cmp2);
        sscanf(tmp, "%lld", &x);
        strcpy(tmp, str);
        qsort(tmp, ln, sizeof(char), cmp1);
        for(i=0; tmp[i]=='0';i++);
        if(tmp[i] && tmp[0]=='0') tmp[i]^=tmp[0]^=tmp[i]^=tmp[0];
        sscanf(tmp, "%lld", &y);
        z=x-y;
        printf("%lld - %lld = %lld = 9 * %lld\n", x, y, z, z/9);
    }
    
    return 0;
}
