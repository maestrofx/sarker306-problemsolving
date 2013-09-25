#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define ROW 76

long array[ROW][ROW];
long max[ROW][ROW][3][6];
int vis[ROW][ROW][3][6], Turn = 1;
int n, p;

long rec(int row, int col, int dir, int rem){
	long res = INT_MIN, temp;
	int nrem;

	/*if ( row == n && col == n - 1 && dir == 0 && rem >= 0 ){
		printf("Found -> %d %d %d %d %d\n", row, col, dir, rem, 0);
		return 0;
	}*/
	if ( row >= n || col < 0 || col >= n ) return INT_MIN;
	if ( vis[row][col][dir][rem] == Turn ) return max[row][col][dir][rem];
	
	nrem = ( array[row][col] < 0 ) ? rem - 1 : rem;
	if ( nrem < 0 ) return INT_MIN;
	
	vis[row][col][dir][rem] = Turn;
	
	if ( row == n - 1 && col == n - 1 ) res = 0;
	else if ( dir == 0 ){
		temp = rec(row, col + 1, 2, nrem);
		if ( res < temp ) res = temp;
		temp = rec(row + 1, col, 0, nrem);
		if ( res < temp ) res = temp;
		temp = rec(row, col - 1, 1, nrem);
		if ( res < temp ) res = temp;
	}
	else if ( dir == 1 ){
		temp = rec(row + 1, col, 0, nrem);
		if ( res < temp ) res = temp;
		temp = rec(row, col - 1, 1, nrem);
		if ( res < temp ) res = temp;
	}
	else{
		temp = rec(row, col + 1, 2, nrem);
		if ( res < temp ) res = temp;
		temp = rec(row + 1, col, 0, nrem);
		if ( res < temp ) res = temp;
	}
	
	if ( res != INT_MIN ) res += array[row][col];
	/*else printf("%d %d %d %d uhu\n", row, col, rem, dir);
	printf("%d %d %d %d %d\n", row, col, dir, rem, res);*/
	return max[row][col][dir][rem] = res;
}

int main(){
    int i, j, kase = 1;
    long maxx;
    
    while ( scanf("%d%d", &n, &p) == 2 && (n || p) ){
        for ( i = 0 ; i < n ; i++ )
            for ( j = 0 ; j < n ; j++ )
                scanf("%ld", &array[i][j]);
        
        maxx = rec(0,0,0,p);
        
        printf("Case %d: ", kase++);
        if ( maxx != INT_MIN ) printf("%ld\n", maxx);
        else puts("impossible");
        Turn++;
    }
    
    return 0;
}
