/*
  Name: Sudoku solver
  Copyright: None
  Author: WIKIPEDIA
  Date: 17/08/09 18:32
  Description: Solves sudoku using brute force.
*/
#include <stdio.h>
#include<stdlib.h>

typedef struct{
    int r, c, candi, number[10];
}pos;
pos position[82];
char grid[9][9];
int boxsize;

char variant='C';
int nsol;
void print_solution(void);
int safe(int row, int col, int n, int solving);
void solve(int index);
int input(void);
int check_validity(void);
void precalc(void);
int cmp(const void* a, const void *b);

int main(){
	char ch;
	int i, j, test=0;
	
	while(1){
	    if(!input()) break;
	    printf("Case %d: ", ++test);
	    if(!check_validity()) printf("Illegal.\n");
	    else{
    		precalc();
    	    nsol=0;
    		solve(0);
    		
    		switch (nsol) {
                case 0: printf("Impossible.\n"); break;
                case 1: printf("Unique.\n"); break;
                case 2: printf("Ambiguous.\n"); break;
            }
        }
	}
    return 0;
}

int cmp(const void *a, const void *b){
    return ((pos*)a)->candi-((pos*)b)->candi;
}

int input(){
    int i, j;
    char ch;
    
    for(i=0;i<9;i++)
    for(j=0;j<9;){
		if(scanf("%c",&ch)==EOF) return 0;
    	if ((ch>='0'&&ch<='9')||ch=='.'){
			if (ch=='.') ch='0';
			grid[i][j++]=ch;
		}
    }
    
    return 1;
}

int check_validity(){
    int i, j, k=0;
    
    for(i = 0; i < 9; i++ ){
        for( j = 0; j < 9; j++ ){
            if(grid[i][j] != '0')
            if(!safe( i, j, grid[i][j] - '0', 0)){
                return 0;
            }
        }
    }
    
    return 1;
}

void print_state(void){
    int r, c;

    printf("\n\n-----   state    -----\n");
    for (r = 0; r < 9; r++){
		printf("     ");
		for (c = 0; c < 9; c++){
		    printf("%c", (grid[r][c]=='0')?'.':grid[r][c]);
		    if (c % 3 == 2)
			printf("  ");
		}
		printf("\n");
		if (r % 3 == 2) printf("\n");
    }
    
    return;
}

void print_solution(void){
    int r, c;
    
    nsol++;
    return;
}

void precalc(void){
    int i, j, k=0, n;
    
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            position[k].r=i, position[k].c=j, position[k].candi=0;
            for(n=1;n<=9;n++){
                if(safe(i, j, n, 1)) position[k].number[position[k].candi++]=n;
            }
            k++;
        }
    }
    
    qsort(position, 81, sizeof(pos), cmp);
}

int safe(int row, int col, int n, int solving){
    int r, c, d, br, bc;
    
    if (solving && grid[row][col] == n+'0') return 1;
    if (solving && grid[row][col] != '0') return 0;
    for (c = 0; c < 9; c++)
	if (c!=col && grid[row][c] == n+'0') return 0;
    for (r = 0; r < 9; r++)
	if (r!=row && grid[r][col] == n+'0') return 0;
    br = row / 3;
    bc = col / 3;
    for (r = br * 3; r < (br + 1) * 3; r++)
	for (c = bc * 3; c < (bc + 1) * 3; c++)
	    if (r!=row && c!=col && grid[r][c] == n+'0') return 0;
    return 1;
}

void solve(int index){
    int n, t, row, col;
    
    if (index==81)
	print_solution();
    else if(nsol<2){
        row=position[index].r, col=position[index].c;
    	for (n = 0; n < position[index].candi; n++)
    	    if (safe(row, col, position[index].number[n], 1)){
    			t = grid[row][col];
    			grid[row][col] = position[index].number[n]+'0';
    			solve(index+1);
    			grid[row][col] = t;
    	    }
    }
	return;
}
