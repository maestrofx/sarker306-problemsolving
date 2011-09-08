#include<cstdio>
#include<queue>
#include<set>
#include<map>
#include<string>
#include<cstring>

#define CONSTANT_1 6  /* 2.016 sec, with (C1,C2) = (3,4) 0.604 sec, with (C1,C2)=(3,5) 0.280 sec */
#define CONSTANT_2 7
#define SIZE 1048583

using namespace std;

typedef struct{
    char grid[20];
    long cost;
}pos;

class state{
public:
    char cost, currentMove;
    
    state(int _cost, int _currentMove){
        cost = _cost, currentMove = _currentMove;
    }
    
    void setState(int _cost, int _currentMove){
        cost = _cost, currentMove = _currentMove;
    }
};

char destiny[]="123456789ABCDEF0";
map<string, state>visited[SIZE];

long index_of(char *str){
    long power=1<<15, i=0, value=0;
    
    for(; str[i]; i++, power>>=1){
        if(str[i]>='0' && str[i]<='9') value+=power*(str[i]-'0');
        else value+=power*(str[i]-'A'+10);
    }
    
    return value;
}

long heuristics(char *grid){
    int i=0, x, y, c;
    long not_in_final_position=0, sum_manhattan;
    //for( ; grid[i]; i++) not_in_final_position+=(grid[i]!=destiny[i] && grid[i]!='0');
    for(i = 0, sum_manhattan=0; grid[i] ; i++){
        if( grid[i] == '0' ) continue;
        c = ( grid[i] < 'A' ) ? grid[i] - '1' : grid[i] - 'A' + 9;
        x = c%4 - i%4;
        y = c/4 - i/4;
        sum_manhattan += ( x > 0 ? x : -x ) + ( y > 0 ? y : -y );
    }
    
    return sum_manhattan;
}

int L_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i%4) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i-1]^=dest_grid[zero_i]^=dest_grid[zero_i-1];
}

int R_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i%4!=3) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i+1]^=dest_grid[zero_i]^=dest_grid[zero_i+1];
}

int U_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i>3) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i-4]^=dest_grid[zero_i]^=dest_grid[zero_i-4];
}

int D_slide(char *dest_grid, char *source_grid){
    int i, flag, zero_i=0;
    
    for(i=0, flag=0; ;i++){
        dest_grid[i]=source_grid[i];
        if(source_grid[i]=='0' && i<12) flag=1, zero_i=i;
        if(source_grid[i]==0) break;
    }
    
    if(!flag) return 0;
    dest_grid[zero_i]^=dest_grid[zero_i+4]^=dest_grid[zero_i]^=dest_grid[zero_i+4];
}

int (*moves[4])(char *, char *)={R_slide, U_slide, L_slide, D_slide};
char movInd[5]="RULD";
char movNum[128];

int is_destiny(char *grid){
    int i;
    
    for ( i = 0 ; grid[i] ; i++ ) if ( grid[i] != destiny[i] ) break;
    return grid[i] ? 0 : 1;
}

int is_solvable(char *grid){
    int i, j, less, sum = 0;
    char flag, tmpgrid[20];
    
    for(i=0, j=0;i<4;i++, j++){
        tmpgrid[j] = grid[i];
        if(grid[i]=='0') sum = ~i&1, tmpgrid[j] = 'G';
    }
    for(i=7;i>=4;i--, j++) {
        tmpgrid[j] = grid[i];
        if(grid[i]=='0') sum = i&1, tmpgrid[j] = 'G';
    }
    for(i=8;i<12;i++, j++){
        tmpgrid[j] = grid[i];
        if(grid[i]=='0') sum = ~i&1, tmpgrid[j] = 'G';
    }
    for(i=15;i>=12;i--, j++){
        tmpgrid[j] = grid[i];
        if(grid[i]=='0') sum = i&1, tmpgrid[j] = 'G';
    }
    tmpgrid[j] = tmpgrid[j+1] = 0;
    //puts(tmpgrid);
    /*for(i = 0 ; grid[i]!='0' ; i++ );
    grid[i] = 'G';*/
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
    
    //printf("%lu %lu %lu\n", x, x>>20, x&~(-1<<20));
    
    x=((x>>20)^(x&(~(-1<<20))))& (~(-1<<20));
    return x;
}

void setpos(pos *x, char value){
    x->grid[18] = value;
    x->cost=CONSTANT_1 * value + CONSTANT_2 * heuristics(x->grid);
}

class cmp{
public:
    bool operator()(const pos &a, const pos &b){
        return a.cost > b.cost;
    }
};

void solveStep(char *grid){
    char temp[20], curMove;
    map<string, state>::iterator mapItr;
    mapItr = visited[hash(grid)].find(string(grid));
    
    if( mapItr->second.currentMove != 0 ){
        curMove = mapItr->second.currentMove;
       // printf("%c\n", curMove);
        moves[ (movNum[curMove] + 2)%4 ](temp, grid); // Left move means reverse to right, etc...
        solveStep(temp);
        putchar(curMove);
    }
}

void branch_bound_search(char *start){
    priority_queue<pos, vector<pos>, cmp>Queue;
    pair< map<string, state>::iterator, bool > isNotVisited;
    pos u, v;
    long i;
    
   // branch_bound_init(start);
    state startState(0, 0);
    visited[hash(start)].insert(pair<string, state>(string(start), startState));
    strcpy(u.grid, start);
    u.grid[18] = u.cost = 0;
    if ( is_destiny(u.grid) == 0 ) Queue.push(u);
    
    while( Queue.empty() == false ){
        u = Queue.top();
        Queue.pop();
      //  printf("%s %d %d\n", u.grid, u.grid[18], u.cost);
        if( is_destiny(u.grid)) break;
        
        for ( i = 0 ; i < 4 ; i++ ){
            pos v;
            if(moves[i](v.grid, u.grid) == -1) continue;
            setpos(&v, (char)u.grid[18] + 1);
            state nowState(v.cost, movInd[i]);
            isNotVisited = visited[hash(v.grid)].insert(pair<string, state>
                (string(v.grid), nowState));
            if( isNotVisited.second == true  ){
               // if ( is_destiny(v.grid) ) break;
              //  printf("     -> %s %d\n", v.grid, v.cost);
                Queue.push(v);
            }
           /* else{
                map<string, state>::iterator visitedPtr = isNotVisited.first;
                if(visitedPtr->second.cost <= v.cost) continue;
                visitedPtr->second.setState(v.cost, movInd[i]);
              //  if ( is_destiny(v.grid) ) break;
              //  printf("     -> %s %d\n", v.grid, v.cost);
                Queue.push(v);
            }*/
        }
    }
    
    while(Queue.empty() == false) Queue.pop();
    solveStep(destiny);
    puts("");
    for( i = 0 ; i < SIZE ; i++ ) visited[i].clear();
}

int main(){
    char str[20], str1[20];
    char character[]="0123456789ABCDEF";
    int test, i, x;
    
   // printf("%d\n", heuristics(destiny));
    movNum['R']=0, movNum['U']=1, movNum['L']=2, movNum['D']=3;
    while(scanf("%d", &test)!=EOF){
        while(test--){
            for(i=0;i<16;i++){
                scanf("%d", &x);
                str[i]=character[x];
            }
            
            str[i]=0;
            if(is_solvable(str)==0) printf("This puzzle is not solvable.\n");
            else{
               // printf("Good luck!\n");
                branch_bound_search(str);
              //  printf("Solved!\n");
            }
        }
    }
    
    return 0;
}
/* 6 2 8 4
12 14 1 10
13 15 3 9
11 0 5 7

6 8 4 2
12 14 1 10
13 15 3 9
11 0 5 7

2 15 10 0
1 3 8 12
5 14 7 4
9 6 13 11

2 3 4 0
1 5 7 8
9 6 10 12
13 14 11 15
*/
