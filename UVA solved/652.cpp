#include<cstdio>
#include<queue>
#include<map>
#include<string>
#include<cstring>

#define SIZE 524289

using namespace std;

typedef struct{
    char grid[14];
}pos;

char destiny[]="123456780" ;   // for odd case, "123804765";
map<string, char>visited[SIZE];

int L_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i%3) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i-1]^=dest_grid[zero_i]^=dest_grid[zero_i-1];
}

int R_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i%3!=2) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i+1]^=dest_grid[zero_i]^=dest_grid[zero_i+1];
}

int U_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i>2) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i-3]^=dest_grid[zero_i]^=dest_grid[zero_i-3];
}

int D_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i<6) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i+3]^=dest_grid[zero_i]^=dest_grid[zero_i+3];
}

int (*moves[4])(char *, char *)={R_slide, U_slide, L_slide, D_slide};
char movInd[5]="ruld";
char movNum[128];

int is_destiny(char *grid){
    int i;
    
    for ( i = 0 ; grid[i] ; i++ ) if ( grid[i] != destiny[i] ) break;
    return grid[i] ? 0 : 1;
}

int is_solvable(char *grid){
    int i, j, less, sum = 0;
    char flag, tmpgrid[14];
    
    /*for ( i = 0 ; i<9 ; i++ ) tmpgrid[i] = 0;
    for ( i = 0 ; grid[i] ; i++ ) tmpgrid[ grid[i] - '0' ]++;
    for ( i = 0 ; i < 9 ; i++ ) if ( tmpgrid[i] != 1 ) return 0;*/
    
    for(i=0, j=0;i<3;i++, j++){
        tmpgrid[j] = grid[i];
        if(grid[i]=='0') sum = i&1, tmpgrid[j] = 'A';
    }
    for(i=5;i>=3;i--, j++) {
        tmpgrid[j] = grid[i];
        if(grid[i]=='0') sum = i&1, tmpgrid[j] = 'A';
    }
    for(i=6;i<9;i++, j++){
        tmpgrid[j] = grid[i];
        if(grid[i]=='0') sum = i&1, tmpgrid[j] = 'A';
    }
    
    tmpgrid[j] = tmpgrid[j+1] = 0;
    
    for(i=0 ; tmpgrid[i] ;i++, sum+=less){
        for(j=i+1, less=0;tmpgrid[j];j++){
            if(tmpgrid[j]<tmpgrid[i]) less++;
        }
    }
    
    if(sum&1) return 1;
    else return 0;
}

unsigned long hash(char *str){
    unsigned long x=0;
    
    for(;*str++;){
        x=(x<<5)+x+*str;
    }
    
    x=((x>>19)^(x&(~(-1<<19))))& (~(-1<<19));
    return x;
}

void solveStep(char *grid){
    char temp[14], curMove;
    map<string, char>::iterator mapItr;
    mapItr = visited[hash(grid)].find(string(grid));
    
    while( mapItr->second != 0 ){
        curMove = (movNum[mapItr->second] + 2)%4;
        //printf("%c\n", movInd[curMove]);
        moves[ curMove ](temp, grid); // Left move means reverse to right, etc...
        putchar( movInd[curMove] );
      //  printf(" %s\n", temp);
        grid = temp;
        mapItr = visited[hash(grid)].find(string(grid));
    }
}

void breadth_first(char *start){
    pair< map<string, char>::iterator, bool > isNotVisited;
    queue< pos >Queue;
    
    visited[hash(start)].insert(pair< string, char>(string(start), 0));
    pos startState;
    strcpy(startState.grid, start);
    Queue.push(startState);
    
    while( !Queue.empty() ){
        pos u = Queue.front();
        Queue.pop();
        
        for ( int i = 0 ; i < 4 ; i++ ){
            pos v;
            if ( moves[i]( v.grid, u.grid ) == 0 ) continue;
            isNotVisited = visited[hash(v.grid)].insert(pair<string, char>
                (string(v.grid), movInd[i]));
            if( isNotVisited.second == true )   Queue.push(v);
        }
    }
}

int main(){
    char str[14], inpSlide[4];
    char character[]="0123456789";
    int test, i, x;
    
    movNum['r']=0, movNum['u']=1, movNum['l']=2, movNum['d']=3;
    breadth_first(destiny);
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            for(i=0;i<9;i++){
                scanf("%s", inpSlide);
                if(inpSlide[0] == 'x' ) x = 0;
                else x = inpSlide[0] - '0';
                str[i]=character[x];
            }
            
            str[i]=0;
            if(is_solvable(str)==0) printf("unsolvable\n");
            else{
                solveStep(str);
                puts("");
            }
            
            if(test) puts("");
        }
    }
    
    for ( i = 0 ; i < SIZE ; i++ ) visited[i].clear();
    return 0;
}
/*
12
x 8 7 6 5 4 3 2 1
6 8 7 x 5 4 3 2 1
8 x 7 6 5 4 3 2 1
6 8 7 3 5 4 x 2 1
6 8 7 5 x 4 3 2 1
8 5 7 6 x 4 3 2 1
8 7 x 6 5 4 3 2 1
2 1 8 5 4 3 7 6 x
2 1 x 5 6 8 7 3 4
2 1 8 5 x 6 7 3 4
2 4 1 5 6 8 x 7 3
1 7 8 2 5 4 x 6 3

for odd symmetry
5
1 3 4 8 6 2 7 x 5
2 8 1 x 4 3 7 6 5
2 8 1 4 6 3 x 7 5
5 6 7 4 x 8 3 2 1
1 2 3 8 x 4 7 6 5
*/
