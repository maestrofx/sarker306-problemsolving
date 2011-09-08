#include<stdio.h>
#define ROOK 'r'

char grid[6][6];
int max_rooks, n;

int safe(int row, int col){
    int i, flag=1;
    
    if(grid[row][col]=='X') return !flag;
    for(i=1;;i++){
        if(row+i>=n) break;
        if(grid[row+i][col]=='X') break;
        if(grid[row+i][col]==ROOK) return !flag;
    }
    
    for(i=1;;i++){
        if(row-i<0) break;
        if(grid[row-i][col]=='X') break;
        if(grid[row-i][col]==ROOK) return !flag;
    }
    
    for(i=1;;i++){
        if(col+i>=n) break;
        if(grid[row][col+i]=='X') break;
        if(grid[row][col+i]==ROOK) return !flag;
    }
    
    for(i=1;;i++){
        if(col-i<0) break;
        if(grid[row][col-i]=='X') break;
        if(grid[row][col-i]==ROOK) return !flag;
    }
    
    return flag;
}

void backtrack(int row, int col, int totlrooks){
    int i, j, flag=0;
    char tmp;
    
    if(row==n){
        /*for(i=0;i<4;i++){
            printf("       %s\n", grid[i]);
        }
        printf("\n");*/
        
        if(max_rooks<totlrooks) max_rooks=totlrooks;
        return ;
    }
    for(i=col;i<n;i++){
        if(i>=n) break;
        flag=safe(row, i);
        tmp=grid[row][i];
        if(flag)grid[row][i]=ROOK;
        if(i+1==n) backtrack(row+1, 0, totlrooks+flag);
        else backtrack(row, i+1, totlrooks+flag);
        grid[row][i]=tmp;
    }
}

void trying(void){
    int i, j;
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid[i][j]!='X') backtrack(i, j, 0);
        }
    }
}

int main(){
    int i;
    
    while(scanf("%d", &n)!=EOF && n){
        for(i=0, max_rooks=0;i<n;i++) scanf("%s", grid[i]);
        trying();
        printf("%d\n", max_rooks);
    }
    
    return 0;
}
