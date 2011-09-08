#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 102
#define MAXLEN 60

int cmp(const void *a, const void *b){
    return strcmp(*(char**)a, *(char**)b);
}

char words[MAX][MAXLEN+2];
char *sorted[MAX];

int main(){
    int N, i, j, max_file_name, x, cols, rows;
    
    while(scanf("%d", &N)!=EOF){
        for(i=0, max_file_name=0;i<N;i++){
            scanf("%s", words[i]);
            sorted[i]=words[i];
            x=strlen(words[i]);
            max_file_name=(max_file_name>x)? max_file_name:x;
        }
        
        cols=1+(60-max_file_name)/(max_file_name+2);
        rows=(N+cols-1)/cols;
        qsort(sorted, N, sizeof(char*), cmp);
        printf("------------------------------------------------------------\n");
        for(i=0;i<rows;i++){
            printf("%-*s", max_file_name, sorted[i]);
            for(j=1, x=i+rows; j<cols && x<N;j++, x+=rows){
                printf("  %-*s", max_file_name, sorted[x]);
            }
            puts("");
            if(x-rows==N) cols--;
        }
    }
    
    return 0;
}
