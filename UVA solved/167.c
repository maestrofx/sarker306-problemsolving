#include<stdio.h>
#include<string.h>

#define SIZE 8

int grid[SIZE+2][SIZE+2];
int solution[100][SIZE];
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
    
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(grid[j][i]=='1') break;
        }
        if(j< SIZE)solution[nsol][i]=j;
    }
    nsol++;
}

void solve(int row, int col)
{
    int t, i, j;
 
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
    int i, j, k, sum, max=0;
    
    solve(0, 0);
    
    scanf("%d", &test);
    for(;test;test--){
        max=0;
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                scanf("%d", &grid[i][j]);
            }
        }
        
        for(i=0;i<nsol;i++){
            for(j=0, sum=0; j<SIZE;j++){
                sum+=grid[solution[i][j]][j];
            }
            
            if(max<sum) max=sum;
        }
        printf("%5d\n", max);
    }
    
    return 0;
}
