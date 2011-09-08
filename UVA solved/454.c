#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int cmp_str(const void *x, const void *y){
    return strcmp(*(char**)x, *(char**)y);
}

int cmp_char(const void *a, const void *b){
    return *(char*)a-*(char*)b;
}

char phrase[200][1000], anagram[200][1000], *ptr[200];

int main(){
    int test, i, j, k, n;

    while(scanf("%d", &test)!=EOF){
        getchar();
        getchar();
        while(test--){
            i=0;
            while(gets(phrase[i])){
                if(phrase[i][0]==0) break;
                ptr[i++]=phrase[i];
            }

            n=i;
            qsort(ptr, n, sizeof(char*), cmp_str);

            for(i=0;i<n;i++){
                for(j=k=0;ptr[i][j];j++)
                    if(!isspace(ptr[i][j])) anagram[i][k++]=ptr[i][j];
                anagram[i][k]=0;
                qsort(anagram[i], k, sizeof(char), cmp_char);
            }

            for(i=0;1+i<n;i++){
                for(j=i+1;j<n;j++){
                    if(strcmp(anagram[i], anagram[j])==0)
                        printf("%s = %s\n", ptr[i], ptr[j]);
                }
            }

            if(test) puts("");
        }
    }

    return 0;
}
