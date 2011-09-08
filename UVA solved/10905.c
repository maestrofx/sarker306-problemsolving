#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char tmp1[200], tmp2[200];

int cmp(const void *p, const void *q){
    char *a = *(char**)p, *b = *(char**)q;
    strcpy(tmp1, a);
    strcpy(tmp2, b);
    strcat(tmp1, b);
    strcat(tmp2, a);

    return -strcmp(tmp1, tmp2);
}

char number[56][25], *ptr[56];

int main(){
    int n, i;

    while(scanf("%d", &n) != EOF && n > 0){
        for( i = 0 ; i < n ; i++ ){
            scanf("%s", number[i]);
            ptr[i] = number[i];
        }

        qsort(ptr, n, sizeof(char**), cmp);
        for( i = 0 ; i < n ; i++) printf(ptr[i]);
        puts("");
    }

    return 0;
}
