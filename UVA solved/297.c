#include <stdio.h>

char grid[33][33], *prog;

void init(){
    int i, j;

    for( i = 0 ; i < 32 ; i++ )
        for ( j = 0 ; j < 32 ; j++ )
            grid[i][j] = 'W';
}

int count_black(){
    int i, j, count = 0;

    for( i = 0 ; i < 32 ; i++ )
        for ( j = 0 ; j < 32 ; j++ )
            if( grid[i][j] == 'R') count++;

    return count;
}

void recurse(int startx, int starty, int side_len){
    char ch = *prog++;
    int i, j;

    if(ch == 0){
        prog--;
        return;
    }

    if(ch == 'p'){
        side_len>>=1;
        recurse(startx, starty + side_len, side_len);
        recurse(startx, starty, side_len);
        recurse(startx + side_len, starty, side_len);
        recurse(startx + side_len, starty + side_len, side_len);
    }
    else if(ch == 'f' && side_len > 0){
        for( i = 0 ; i < side_len ; i++ )
            for( j = 0 ; j < side_len ; j++ )
                if( grid[startx + i][starty + j] == 'W')
                    grid[startx + i][starty + j] = 'R';
    }
}

int main(){
    char input[5000];
    int test;

    while(scanf("%d", &test) != EOF){
        getchar();
        while(test--){
            init();
            gets(input);
            prog = input;
            recurse(0, 0, 32);
            gets(input);
            prog = input;
            recurse(0, 0, 32);
            printf("There are %d black pixels.\n", count_black());
        }
    }

    return 0;
}
