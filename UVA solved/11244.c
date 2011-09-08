#include<stdio.h>

#define MAX 103

char sky[MAX][MAX];
int xdir[]={1, 1, 1,-1,-1,-1, 0, 0};
int ydir[]={0, 1,-1, 0, 1,-1, 1,-1};

int ingrid(int x, int y, int row, int col){
    if(x<0 || x>=row) return 0;
    if(y<0 || y>=col) return 0;
    return 1;
}

int safe(int x, int y, int row, int col){
    int i, p, q;
    
    if(ingrid(x, y, row, col) && sky[x][y]=='*'){
        for(i=0;i<8;i++){
            p=x+xdir[i], q=y+ydir[i];
            if(ingrid(p, q, row, col) && sky[p][q]=='*') return 0;
        }
        
        return 1;
    }
    
    return 0;
}

int check(int row, int col){
    int i, j, numofstar=0;
    
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            numofstar+=safe(i, j, row, col);
        }
    }
    
    return numofstar;
}

int main(){
    int row, col, i, j; 
    
    while(scanf("%d%d", &row, &col)==2 && (row || col)){
        for(i=0;i<row;i++) scanf("%s", sky[i]);
        printf("%d\n", check(row, col));
    }
    
    return 0;
}
