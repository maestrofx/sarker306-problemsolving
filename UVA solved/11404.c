#include<stdio.h>
#include<string.h>

#define SIZE 1001

typedef struct{
    char ch;
    int x, y;
}pos;
pos parent[SIZE][SIZE];
int palindrome[SIZE][SIZE];

char str_lex_check(char *a, int x1, int y1, int x2, int y2){
    if ( x1 > y1 || x2 > y2 ) return 0;
    if ( parent[x1][y1].ch != parent[x2][y2].ch ) return parent[x1][y1].ch - parent[x2][y2].ch;
    if(parent[x1][y1].x!=-1 && parent[x1][y1].y!=-1 && parent[x2][y2].x!=-1 && parent[x2][y2].y!=-1){
        return str_lex_check(a, parent[x1][y1].x, parent[x1][y1].y, parent[x2][y2].x, parent[x2][y2].y);
    }
    return 0;
}

int len_longpalin(char *a, int x, int y)
{
    int i, j, m, n;

    if(x>y) return 0;
    if(palindrome[x][y]) return palindrome[x][y];

    /*printf("%d %d\n", x, y);*/
    if(x==y){
        palindrome[x][y]=1;
        parent[x][y].ch=a[x];
    }

    else if(a[x]==a[y]){
        palindrome[x][y]=len_longpalin(a, x+1, y-1)+2;
        parent[x][y].ch=a[x];
        parent[x][y].x=x+1, parent[x][y].y=y-1;
    }
    else{
        m=len_longpalin(a, x+1, y);
        n=len_longpalin(a, x, y-1);
        if(n>m || (m==n && str_lex_check(a, x, y-1, x+1, y) < 0)){ /* parent[x][y-1].ch<=parent[x+1][y].ch*/
            palindrome[x][y]=n;
            parent[x][y].ch=parent[x][y-1].ch;
            parent[x][y].x=parent[x][y-1].x, parent[x][y].y=parent[x][y-1].y;
        }
        else{
            palindrome[x][y]=m;
            parent[x][y].ch=parent[x+1][y].ch;
            parent[x][y].x=parent[x+1][y].x, parent[x][y].y=parent[x+1][y].y;
        }
    }

    return palindrome[x][y];
}

void palindrome_print(int x, int y)
{
    if(x>y) return;
    putchar(parent[x][y].ch);
    if(parent[x][y].x!=-1 && parent[x][y].y!=-1){
        palindrome_print(parent[x][y].x, parent[x][y].y);
        putchar(parent[x][y].ch);
    }
}

int main()
{
    char array[SIZE], ch;
    int n, i, j, len=0;

    for(;(ch=getchar())!=EOF;len=0){
        do{
            if(ch=='\n') break;
            array[len++]=ch;
        }while((ch=getchar())!=EOF);

        for(i=0;i<len;i++){
            for(j=0;j<len;j++){
                palindrome[i][j]=0;
                parent[i][j].ch=0, parent[i][j].x=parent[i][j].y=-1;
            }
        }

        len_longpalin(array, 0, len-1);
        palindrome_print(0, len-1);
        puts("");
    }

    return 0;
}
