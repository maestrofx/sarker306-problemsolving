#include<stdio.h>
#define SIZE 12

char grid[SIZE+1][SIZE+1];
char played[SIZE+1][SIZE+1];
int xdir[]={-1,-1,-1, 0, 0, 1, 1, 1};
int ydir[]={ 1, 0,-1, 1,-1, 1, 0,-1};

int ingrid(int x, int y, int n){
    if(x<0 || x>=n) return 0;
    if(y<0 || y>=n) return 0;
    return 1;
}

int numofmines(int x, int y, int n){
    int i, p, q, count=0;
    
    for(i=0;i<8;i++){
        p=x+xdir[i], q=y+ydir[i];
        if(ingrid(p, q, n) && grid[p][q]=='*') count++;
    }
    
    return count;
}

void update(int n){
    int i, j, showmine=0;
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(played[i][j]=='x'){
                if(grid[i][j]=='*') showmine=1;
                else played[i][j]=numofmines(i, j, n)+'0';
            }
        }
    }
    
    if(showmine) for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid[i][j]=='*') played[i][j]='*';
        }
    }
    
    for(i=0;i<n;i++) printf("%s\n", played[i]);
}

int main(){
    int n, i, test;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d", &n);
            for(i=0;i<n;i++) scanf("%s", grid[i]);
            for(i=0;i<n;i++) scanf("%s", played[i]);
            update(n);
            if(test) printf("\n");
        }
    }
    
    return 0;
}
