#include<stdio.h>

#define MAXROW 100
#define MAXCOL 100

char grid[MAXROW+3][MAXCOL+3];
char visit[MAXROW+3][MAXCOL+3];
int row, col;
typedef struct{
    int val;
    char ch;
}foo;
foo arr[26];
int xdir[]={1,-1,0,0};
int ydir[]={0,0,1,-1};

void resetall(void){
    int i, j;
    
    for(i=0;i<=row;i++){
        for(j=0; j<=col; j++){
            grid[i][j]=0;
            visit[i][j]=0;
        }
    }
    
    for(i=0;i<26;i++){
        arr[i].ch=i;
        arr[i].val=0;
    }
}

int safe(int x, int y, char ch){
    if(x<0 || x>=row) return 0;
    if(y<0 || y>=col) return 0;
    if(grid[x][y]!=ch) return 0;
    if(visit[x][y]) return 0;
    return 1;
}

void floodfill(int x, int y, char ch){
    int i, u, v;
    
    visit[x][y]=arr[ch-'a'].val;
    for(i=0;i<4;i++){
        u=x+xdir[i], v=y+ydir[i];
        if(safe(u, v, ch)){
            floodfill(u, v, ch);
        }
    }
}

void traverse(void){
    int i, j;
    
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(visit[i][j]==0){
                arr[grid[i][j]-'a'].val++;
                floodfill(i,j, grid[i][j]);
            }
        }
    }
}

int comp(foo a, foo b){
    if(a.val!=b.val) return a.val-b.val;
    return b.ch-a.ch;
}

void quick_sort(foo *items, int left, int right){
	register int i, j;
	foo x,y;
	i=left, j=right;
	x=items[(left+right)/2];
	do
	{
		while(comp(items[i],x)>0&&(i<right))
			i++;
		while(comp(items[j],x)<0&&(j>left))
			j--;
		if(i<=j)
		{
			y=items[i];
			items[i]=items[j];
			items[j]=y;
			i++;
			j--;
		}
	}while(i<=j);
	if (j>left) quick_sort(items, left, j);
	if (i<right) quick_sort(items, i, right);
	return;
}

int main(){
    int i, j, test;
    
    for(i=0;i<26;i++) arr[i].ch=i;
    scanf("%d", &test);
    for(j=1;j<=test;j++){
        scanf("%d%d", &row, &col);
        for(i=0;i<row; i++) scanf("%s", grid[i]);
        
        traverse();
        quick_sort(arr, 0, 25);
        printf("World #%d\n", j);
        for(i=0;i<26;i++){
            if(arr[i].val==0) break;
            printf("%c: %d\n", arr[i].ch+'a',arr[i].val);
        }

        if(j!=test) resetall();
    }
    
    return 0;
}
