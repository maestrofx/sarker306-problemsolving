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
int rowsize;

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
	    if(test++)printf("\n");
	    if(!check_validity()) printf("NO SOLUTION\n");
	    else{
    		precalc();
    	    nsol=0;
    		solve(0);
    		
    		switch (nsol) {
                case 0: printf("NO SOLUTION\n"); break;
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
    
    if(scanf("%d", &boxsize)==EOF) return 0;
    rowsize=boxsize*boxsize;
    for(i=0;i<rowsize;i++)
    for(j=0;j<rowsize;){
		if(scanf("%c",&ch)==EOF) return 0;
    	if (ch>='0'&&ch<=(rowsize+'0')||ch=='.'){
			if (ch=='.') ch='0';
			grid[i][j++]=ch;
		}
    }
    
    return 1;
}

int check_validity(){
    int i, j, k=0;
    
    for(i = 0; i < rowsize; i++ ){
        for( j = 0; j < rowsize; j++ ){
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
    for (r = 0; r < rowsize; r++){
		printf("     ");
		for (c = 0; c < rowsize; c++){
		    printf("%c", (grid[r][c]=='0')?'.':grid[r][c]);
		    if (c % boxsize == 2)
			printf("  ");
		}
		printf("\n");
		if (r % boxsize == boxsize-1) printf("\n");
    }
    
    return;
}

void print_solution(void){
    int r, c;
    
    nsol++;
    
    for (r = 0; r < rowsize; r++){
        printf("%c", grid[r][0]);
		for (c = 1; c < rowsize; c++){
		    printf(" %c", grid[r][c]);
		}
		printf("\n");
    }
    return;
}

void precalc(void){
    int i, j, k=0, n;
    
    for(i=0;i<9;i++){
        for(j=0;j<rowsize;j++){
            position[k].r=i, position[k].c=j, position[k].candi=0;
            for(n=1;n<=rowsize;n++){
                if(safe(i, j, n, 1)) position[k].number[position[k].candi++]=n;
            }
            k++;
        }
    }
    
    /*qsort(position, rowsize*rowsize, sizeof(pos), cmp);*/
}

int safe(int row, int col, int n, int solving){
    int r, c, d, br, bc;
    
    if (solving && grid[row][col] == n+'0') return 1;
    if (solving && grid[row][col] != '0') return 0;
    for (c = 0; c < rowsize; c++)
	if (c!=col && grid[row][c] == n+'0') return 0;
    for (r = 0; r < rowsize; r++)
	if (r!=row && grid[r][col] == n+'0') return 0;
    br = row / boxsize;
    bc = col / boxsize;
    for (r = br * boxsize; r < (br + 1) * boxsize; r++)
	for (c = bc * boxsize; c < (bc + 1) * boxsize; c++)
	    if (r!=row && c!=col && grid[r][c] == n+'0') return 0;
    return 1;
}

void solve(int index){
    int n, t, row, col;
    
    if (index==rowsize*rowsize)
	print_solution();
    else if(nsol<1){
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
