#include<stdio.h>

#define MAXNODE 129

char index[MAXNODE];
char matrix[MAXNODE][MAXNODE];
char n;

void init(){
    int i, j;
    
    for(i=0;i<128;i++){
		index[i]=-1;
        for(j=0;j<128;j++) matrix[i][j]=0;
    }
}

void input(){
    int m;
    char u[3], v[3];
    
    n=0;
    scanf("%d", &m);
    while(m--){
        scanf("%s%s", u, v);
        
        if(index[u[0]]==-1) index[u[0]]=n++;
        if(index[v[0]]==-1) index[v[0]]=n++;
        matrix[index[u[0]]][index[v[0]]]=1;
    }
}

void floyd_warshall(){
    int i, j, k;
    
    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(matrix[i][j]==0 && matrix[i][k]==1 && matrix[k][j]==1)
                    matrix[i][j]=1;
            }
        }
    }
}

int verify(){
    char flag=1;
    char u[3], v[3];
    int m;
    
    scanf("%d", &m);
    while(m--){
        scanf("%s%s", u, v);
        
        if(index[u[0]]==-1) flag=0;
        if(index[v[0]]==-1) flag=0;
        if(matrix[index[u[0]]][index[v[0]]]==0) flag=0;
    }
    
    return flag;
}

int main(){
    int test=0;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            init();
            input();
            floyd_warshall();
            
            if(verify()==0) puts("NO");
            else puts("YES");
            if(test) puts("");
        }
    }
    
    return 0;
}
