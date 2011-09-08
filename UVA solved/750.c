#include<stdio.h>
#include<string.h>

#define SIZE 14

char grid[SIZE+2][SIZE+2];
int xdir[]={-1,-1,-1,0,0,1,1,1};
int ydir[]={-1,0,1,-1,1,-1,0,1};
int nsol;

int ingrid(int x, int y)
{
    if(x<0 || x>=SIZE) return 0;
    if(y<0 || y>=SIZE) return 0;
    return 1;
}

int safe(int row, int col)
{
    int i, j, x, y;
    
    if(grid[row][col]=='1') return 1;
    
    for(i=0; i<SIZE;i++){
        for(j=0;j<8;j++){
            x=row+ i*xdir[j];
            y=col+ i*ydir[j];
            if(ingrid(x,y) && grid[x][y]=='1') return 0;
        } 
    }
    
    return 1;
}

void print_solution(void)
{
    int i, j;
    
    nsol++;
    //printf("%2d     ", ++nsol);
    /*for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(grid[j][i]=='1') break;
        }
        if(j< SIZE)printf(" %d", j+1);
    }
    printf("\n");*/
}

void solve(int row, int col)
{
    char t, i, j;
 
    if (col == SIZE)
        print_solution();
    else 
        for(i=0;i<SIZE;i++)
        if(safe(row+i, col)){
        t=grid[row+i][col];
        grid[row+i][col]='1';
        solve(0, col+1);
        grid[row+i][col]=t;
    }
}

int main()
{
    int test;
    int inix, iniy;
    int i, j;
    
    scanf("%d", &test);
    for(;test;test--){
        for(i=0;i<SIZE+2;i++){
            for(j=0;j<SIZE+2;j++){
                grid[i][j]='0';
            }
        }
        
        scanf("%d%d", &inix, &iniy);
        inix--, iniy--;
        nsol=0;
        //grid[inix][iniy]='1';
        //printf("SOLN       COLUMN\n #      1 2 3 4 5 6 7 8\n\n");
        solve(0, 0);
        printf("%d\n", nsol);
        if(test!=1) printf("\n");
    }
    
    return 0;
}
