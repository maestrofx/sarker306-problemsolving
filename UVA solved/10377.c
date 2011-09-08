#include<stdio.h>
#include<iostream>
using namespace std;
#define SIZE 65
#define NORTH 0

char maze[SIZE][SIZE+1];
int row,col;
int ydir[]={0,1,0,-1};
int xdir[]={-1,0,1,0};
char dirs[]="NESW";

int safe(int x, int y){
    if(x>=0 && y>=0 && x<=row-1 && y<=col-1)
    {
       if(maze[x][y]=='*')
         return 0;
       return 1;
    }
    return 0;
}

int main(){
    int test, i, j, x, y, dir;
    char ch;
    
    while(scanf("%d", &test)!=EOF){
        int var=0;
        while(test--){
            if(!var)    var=1;
            else printf("\n");
            scanf("%d%d", &row, &col);
            for(i=0;i<SIZE;i++) memset(maze[i], SIZE, sizeof(char));
            getchar();

            for(i=0;i<row; i++) gets(maze[i]);
            scanf("%d%d", &x, &y);
            x--, y--;
            dir=NORTH;
            
            while((ch=getchar())!=EOF && ch!='Q'){    // error
                if(ch=='L') dir=(dir+3)%4;
                else if(ch=='R') dir=(dir+1)%4;
                else if(ch=='F' && safe(x+xdir[dir], y+ydir[dir])) x+=xdir[dir], y+=ydir[dir];
            }
            
            printf("%d %d %c\n", x+1, y+1, dirs[dir]);
            //if(test) puts("");
        }
    }
    //getchar();
    //getchar();
    return 0;
}
