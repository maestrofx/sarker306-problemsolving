#include<stdio.h>

char used[5][5], grid[5][5];
char word[20], cost[20];
char xdir[]={-1,-1,-1,0,0,1,1,1};
char ydir[]={-1,0,1,-1,1,-1,0,1};
int len;

long maximum(long a, long b){ return a>b? a: b; }

long backtrack(int r, int c){
    long i, x, y, max=0, tmp;
    if(word[len]==0) return cost[len];

    for(i=0;i<8;i++){
        x=r+xdir[i], y=c+ydir[i];
        if(x>=0 && x<4 && y>=0 && y<4 && used[x][y]==0 && grid[x][y]==word[len]){
            used[x][y]=1;
            len++;
            max=maximum(max, backtrack(x, y));
            used[x][y]=0;
            len--;
        }
    }

    return max;
}

void init_score_criteria(void){
    int i;

    cost[3]=cost[4]=1, cost[5]=2, cost[6]=3, cost[7]=5;
    for(i=8;i<20;i++) cost[i]=11;
}

long find_word(){
    long i, j, result;

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(word[0]==grid[i][j]){
                len=used[i][j]=1;
                result=backtrack(i, j);
                used[i][j]=0;
                if(result){
                   /* printf("\n%s %d\n", word, result);*/
                    return result;
                }
            }
        }
    }

    return 0;
}

int main(){
    long test, i, _case, num, score;

    init_score_criteria();
    while(scanf("%ld", &test)!=EOF){
        for(_case=1;_case<=test;_case++){
            for(i=0;i<4;i++) scanf("%s", grid[i]);
            for(scanf("%ld", &num), score=0 ;num--;){
                scanf("%s", word);
                score+=find_word();
            }

            printf("Score for Boggle game #%ld: %ld\n", _case, score);
        }
    }

    return 0;
}
