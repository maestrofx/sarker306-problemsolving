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

char phrase[1010][1000], anagram[1010][1000];

int main(){
    int test, i, j, k, n;
    char testword[1010], testword_sorted[1010];

    while(scanf("%d", &test)!=EOF){
        getchar();
        getchar();
        while(test--){
            scanf("%d", &n);
            getchar();
            i=0;
            for(i = 0 ; i < n ; i++ ) gets(phrase[i]);

            for(i=0;i<n;i++){
                for(j=k=0;phrase[i][j];j++)
                    if(!isspace(phrase[i][j])) anagram[i][k++]=phrase[i][j];
                anagram[i][k]=0;
                qsort(anagram[i], k, sizeof(char), cmp_char);
            }

            for(i=1;i<n;i++){
                gets(testword);
                if ( strcmp ( testword, "END" ) == 0 ) break;
                printf("Anagrams for: %s\n", testword);
                strcpy(testword_sorted, testword);
                qsort(testword_sorted, strlen(testword), sizeof(char), cmp_char);
                for(j=k=0;j<n;j++){
                    if(strcmp(testword_sorted, anagram[j])==0)
                        printf("%3d) %s\n", ++k, phrase[j]);
                }
                
                if ( k == 0 ) printf("No anagrams for: %s\n", testword);
            }

            if(test) puts("");
        }
    }

    return 0;
}
