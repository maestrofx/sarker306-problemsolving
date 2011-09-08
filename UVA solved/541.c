#include<stdio.h>

int grid[105][105];
int rows[105], col[105];

int main(){
    int i, j, k, n, flagr, flagc, countbit, x, y;

    while(scanf("%d", &n)!=EOF && n){
        for(i=0;i<n; i++) rows[i]=col[i]=0;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                scanf("%d", &grid[i][j]);
                rows[i]+=grid[i][j];
                col[j]+=grid[i][j];
            }
        }

        for(i=flagc=flagr=0;i<n;i++){
            if(rows[i]%2) flagr++, x=i;
            if(col[i]%2) flagc++, y=i;
        }

        if(flagr==flagc && flagc==0) printf("OK\n");
        else if(flagr==1 && flagc==1) printf("Change bit (%d,%d)\n", x+1, y+1);
        else printf("Corrupt\n");
    }

    return 0;
}
