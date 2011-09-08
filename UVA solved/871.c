#include<stdio.h>

char grid[30][30];
int n, m;
int xdir[]={1, 1, 1, 0, 0, -1, -1, -1};
int ydir[]={-1, 0, 1, -1, 1, -1, 0, 1};

int floodfill(int r, int c){
    int ans=1, i, x, y;

    grid[r][c]='2';
    for(i=0;i<8;i++){
        x=r+xdir[i], y=c+ydir[i];
        if(x>=0 && y>=0 && x<n && y<m && grid[x][y]=='1') ans+=floodfill(x, y);
    }

    return ans;
}

int max_blob(){
    int i, j, max=0, x;

    for(i=0;i<n;i++){
        for(j=0;grid[i][j];j++){
            if(grid[i][j]=='1'){
                x=floodfill(i, j);
                if(max<x) max=x;
            }
        }
    }

    return max;
}

int main(){
    int test;

    while(scanf("%d", &test)!=EOF){
        getchar();
        getchar();
        while(test--){
            n=0;
            while(gets(grid[n])){
                if(grid[n][0]==0) break;
                n++;
            }

            m=strlen(grid[0]);
            printf("%d\n", max_blob());
            if(test) puts("");
        }
    }

    return 0;
}
