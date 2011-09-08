#include<stdio.h>
#include<string.h>

int L, n, indx;
char solution[65535];

int is_repeated(char *str, int len){
    int i, x, y, j, flag;

    for(i=1;i*2<=len;i++){
        for(x=len-1, y=len-1-i, j=0, flag=0; j<i; j++){
            if(str[x-j]!=str[y-j]) flag=1;
        }

        if(flag==0) return 0;
    }

    return 1;
}

void print_solution(char *str, int len){
    int i;

    for(i=0;i<len;i++){
        if(i%64==0 && i) putchar('\n');
        else if(i%4==0 && i) putchar(' ');
        putchar(str[i]);
    }

    putchar('\n');
    printf("%d\n", len);
}

void krypton(int len){
    int i, j;

    if(len && len<=80){
        indx++;
        solution[len]=0;
        if(indx==L){
            print_solution(solution, len);
            return ;
        }
    }

    solution[len+1]=0;
    if(len>80) return;

    for(i=0;i<n && indx<L;i++){
        solution[len]=i+'A';
        if(is_repeated(solution, len+1)) krypton(len+1);
    }
}

int main(){
    while(scanf("%d%d", &L, &n)!=EOF && (L||n)){
        indx=solution[0]=0;
        krypton(0);
    }

    return 0;
}
