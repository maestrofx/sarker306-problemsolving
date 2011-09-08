#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 26
#define WHITE 0
#define GRAY 1
#define BLACK 2

char color[MAX], variables[MAX], varid[129];
int adj[MAX][MAX], prec[MAX];
int varcount, isntPossible;

int comp(const void *a, const void *b){ return *(char*)a-*(char*)b; }

void printmatrix(){
    int i, j;
    
    for(i=0;i<varcount;i++){
        for(j=0;j<varcount;j++) printf("%4d", adj[i][j]);
        puts("");
    }
    
    for(i=0;i<varcount;i++) printf("%c = %d ", variables[i], prec[i]);
    puts("");
}

void init(){
    int i, j;

    for(i=0;i<128;i++) varid[i]=-1;
    for(i=0;i<varcount;i++){
        for(j=0;j<varcount;j++) adj[i][j]=0;
        color[i]=WHITE;
        prec[i]=1;
    }
    
    varcount=isntPossible=0;
}

void dfs(int n){
    int i;
    
    color[n]=GRAY;
    for(i=0;i<varcount && isntPossible==0; i++){
        if(adj[n][i]){
            if(color[i]==WHITE){
                dfs(i);
            }
            else if(color[i]==GRAY){
                isntPossible=1;
                return;
            }
        }
    }
    
    color[n]=BLACK;
}

void floyd_warshall(){
    int i, j, k;
    
    for(k=0;k<varcount;k++)
        for(i=0;i<varcount;i++)
            for(j=0;j<varcount;j++){
                adj[i][j]=adj[i][j]||(adj[i][k] && adj[k][j]);
            }
                
    for(i=0;i<varcount;i++){
        for(j=0;j<varcount;j++) prec[j]+=adj[i][j];
    }
}

void backtrack(int *a, int index){
    int i, j, isUsed[MAX], x=index-1;
    
    if(index==varcount){
        for(i=0;i<varcount;i++) printf("%c", variables[a[i]]);
        puts("");
        return;
    }
    
    for(i=0;i<varcount;i++) isUsed[i]=0;
    for(i=0;i<index;i++) isUsed[a[i]]=1;
    
    for(i=0;i<varcount;i++){
        if(isUsed[i]==0){
            for(x=0;x<index;x++){
                if(adj[a[x]][i]==0 && adj[i][a[x]]) break;
                if(adj[a[x]][i] && prec[a[x]]>prec[i]) break;
            }
            
            if(x==index){
                a[index]=i;
                backtrack(a, index+1);
            }
        }
    }
}

void tryit(){
    int i, array[MAX];
    
    for(i='a';i<='z';i++){
        if(varid[i]>=0){
            array[0]=varid[i];
            backtrack(array, 1);
        }
    }
}

int main(){
    int test=0, i;
    char ch, string[1000000], *p;
    
    while(gets(string)){
        if(test) puts("");
        init();
        
        qsort(string, strlen(string), sizeof(char), comp);
        for(p=string; *p ; p++){
            if(*p>='a' && *p<='z'){
                ch=*p;
                varid[ch]=varcount;
                prec[varcount]=1;
                variables[varcount++]=ch;
            }
        }
        
        while(gets(string) && string[0]==0);
        for(p=string; *p ; p++){
            if(*p>='a' && *p<='z'){
                ch=*p++;
                
                while(*p<'a' || *p>'z') p++;
                adj[varid[ch]][varid[*p]]=1;
            }
        }
        
        for(i=0;i<varcount && isntPossible==0 ;i++){
            if(color[i]==WHITE){
                dfs(i);
            }
        }
        
        if(isntPossible==0){
            floyd_warshall();
            tryit();
        }
        test=1;
    }
    
    return 0;
}
