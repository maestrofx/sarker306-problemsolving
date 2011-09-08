#include<stdio.h>
#define MAX 102

long length[MAX][MAX];
long height[MAX][MAX];
int row, col;
int xdir[]={-1, 1, 0, 0};
int ydir[]={0, 0, 1, -1};

long findlength(int r, int c){
    register int i, x, y;
    
    for(i=0;i<4;i++){
        x=r+xdir[i], y=c+ydir[i];
        if(x>=0 && x<row && y>=0 && y<col)
        if(height[x][y]<height[r][c]){
            length[x][y]=findlength(x, y);
            if(length[x][y]+1>length[r][c]) length[r][c]=length[x][y]+1;
        }
    }
    
    return length[r][c];
}

long searchfor(void){
    register int i, j, k;
    long max;
    
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            findlength(i, j);
        }
    }
    
    for(i=0, max=0;i<row;i++){
        for(j=0;j<col;j++){
            if(max<length[i][j]) max=length[i][j];
        }
    }
    
    return max;
}

int main(){
    register int i, j;
    int test;
    char place[100];
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%s%d%d", place, &row, &col);
            
            for(i=0;i<row;i++)
                for(j=0;j<col;j++){
                    scanf("%ld", height[i]+j);
                    length[i][j]=0;
                }
            
            printf("%s: %ld\n", place, searchfor()+1);
        }
    }
    
    return 0;
}
