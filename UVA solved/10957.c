/*
  Name: Sudoku solver
  Copyright: None
  Author: WIKIPEDIA
  Date: 17/08/09 18:32
  Description: Solves sudoku using brute force.
*/
#include <stdio.h>

int hintsinregion[6];
int hints;
char grid[9][9];
char changelog[10][5];
int changecount;

int nsol;
int input();
void print_solution(void);
void print_state(void);
int safe(int row, int col, int n, int solving);
void solve(int row, int col);
void row_col_interchange(void);
int region_check(int n);
void region_swap(int a, int b);
int check_validity(void);
void change(void);
void scramble(int n);

int main(){
	char ch;
	int i, j, test=1;
	
	while(1){
	    if(!input()) break;
	    printf("Case %d: ", test++);
	    if(!check_validity()) printf("Illegal.\n");
	    else{
    	    nsol=0;
    	    if(hints<24) change();
    		solve(0,0);
    		
    		switch (nsol) {
                case 0: printf("Impossible.\n"); break;
                case 1: printf("Unique.\n"); break;
                case 2: printf("Ambiguous.\n"); break;
            }
        }
	}
    return 0;
}

void change(void){
    int i, j, j1, max=-99, min=99;
    
    for(i=0, j=0;i<6;i++) if(max<hintsinregion[i]) max=hintsinregion[i], j=i;
    if(j>=3){
        row_col_interchange();
        for(i=0;i<3; i++) hintsinregion[i]^=hintsinregion[i+3]^=hintsinregion[i]^=hintsinregion[i+3];
    }
    
    for(i=0, j=0, j1=0, max=-1; i<3;i++){
        if(max<hintsinregion[i]) max=hintsinregion[i], j=i;
        if(min>hintsinregion[i]) min=hintsinregion[i], j1=i;
    }
    
    if(j1==0){
        region_swap(j+1, j1+1);
    }
}

void row_col_interchange(void){
    int temp,i,j;
    
    for (i=0; i<9; i++){
        for (j=0; j<i; j++){
            temp=grid[i][j];
            grid[i][j]=grid[j][i];
            grid[j][i]=temp;
        }
    }
}

int region_check(int n){
    if (n==1) return 0;
    if (n==2) return 3;
    if (n==3) return 6;
} 

void region_swap(int a, int b){
    int i,j, temp;
    a=region_check(a);
    b=region_check(b);
    
    for (i=0;i<3;i++){
        for (j=0;j<9;j++){
            temp=grid[a][j];
            grid[a][j]=grid[b][j];
            grid[b][j]=temp;
        }
        a++;
        b++;
    }
}

int input(){
    int i, j;
    char ch;
    
    for(i=0;i<6;i++) hintsinregion[i]=0;
    for(i=0, hints=0, changecount=0;i<9;i++)
    for(j=0;j<9;){
		if(scanf("%c",&ch)==EOF) return 0;
    	if ((ch>='0'&&ch<='9')||ch=='.'){
			if (ch=='.') ch='0';
			else hints++, hintsinregion[i/3]++, hintsinregion[j/3+3]++;
			grid[i][j++]=ch;
		}
    }
    
    return 1;
}

void print_solution(void){
    int r, c;
    
    return;
    printf("\n\n----- solution #%d -----\n", nsol);
    for (r = 0; r < 9; r++){
		printf("     ");
		for (c = 0; c < 9; c++){
		    printf("%c", grid[r][c]);
		    if (c % 3 == 2)
			printf("  ");
		}
		printf("\n");
		if (r % 3 == 2) printf("\n");
    }
    return;
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

int check_validity(){
    int i, j;
    
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

void solve(int row, int col){
    int n, t;
    if (row == 9){
    	nsol++;
        print_solution();
    }
    else if(nsol<2)
	for (n = 1; n <= 9; n++)
	    if (safe(row, col, n, 1)){
			t = grid[row][col];
			grid[row][col] = n+'0';
			if (col == 8) solve(row + 1, 0);
			else solve(row, col + 1);
			grid[row][col] = t;
	    }
	return;
}
