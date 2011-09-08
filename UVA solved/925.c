#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 125

char course[MAX][23];
char *ptrcourse[MAX];
char matrix[MAX][MAX];
int n;

int cmp(const void *a, const void *b){
    return strcmp(*(char**)a, *(char**)b);
}

int init_matrix(){
    int i, j;
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            matrix[i][j]=0;
            
    return 0;
}

void print_matrix(){
    int i, j;
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            putchar(matrix[i][j]+'0');
            putchar(' ');
        }
        
        puts("");
    }
}

void floyd_warshall(){
    int i, j, k;
    
    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(matrix[i][j]==0 && matrix[i][k] && matrix[k][j])
                    matrix[i][j]=1;
            }
        }
    }
    
    /*puts("");
    print_matrix();*/
    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(matrix[i][j]==1 && matrix[i][k] && matrix[k][j])
                    matrix[i][j]++;
            }
        }
    }
    
    /*puts("");
    print_matrix();*/
}

int search(char *str){
    int low=0, high=n, mid, cond;
    
    do{
        mid=(low+high)>>1;
        if((cond=strcmp(str, ptrcourse[mid]))==0) return mid;
        else if(cond<0) high=mid;
        else low=mid;
    }while(low<high);
    
    return -1;
}

void input(){
    int i, j, u, v;
    char crs[MAX];
    int p;
    
    scanf("%d", &n);

    for(i=init_matrix();i<n;i++){
        scanf("%s", course[i]);
        ptrcourse[i]=course[i];
    }
    
    qsort(ptrcourse, n, sizeof(char*), cmp);
    
    scanf("%d", &i);
    while(i--){
        scanf("%s", crs);
        p=search(crs);
        if(p!=-1) u=p;
        
        scanf("%d", &j);
        while(j--){  
            scanf("%s", crs);
            p=search(crs);
            if(p!=-1){
                v=p;
                if(u!=-1) matrix[u][v]=1;
            }
        }
    }
}

void output(){
    char *array[MAX];
    int count, i, j;
    
    for(i=0;i<n;i++){
        for(count=j=0;j<n;j++){
            if(matrix[i][j]==1){
                array[count++]=ptrcourse[j];
            }
        }
        
        if(count==0) continue;
        printf("%s %d", ptrcourse[i], count);
        for(j=0;j<count;j++) printf(" %s", array[j]);
        putchar('\n');
    }
}

int main(){
    int test;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            input();
            /*print_matrix();*/
            floyd_warshall();
            output();
        }
    }
    
    return 0;
}
