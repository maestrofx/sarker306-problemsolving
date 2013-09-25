#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

int LIMIT = 1001;
int quuX[1002001], quuY[1002001];
int dist[1001][1001];
long head, tail;
int dirx[] = {-1, -2, 1, 2, -1, -2, 1, 2}, diry[] = {-2, -1, -2, -1, 2, 1, 2, 1};
int intCells[17][2], n;

void bfs(){
	int ux, uy, vx, vy, i;
	long maxD = 0;
	
	head = tail = 0;
	dist[0][0] = 1;
	quuX[tail] = quuY[tail] = 0;
	tail++;
	
	while ( head != tail ){
		ux = quuX[head], uy = quuY[head];
		if ( dist[ux][uy] > maxD ) maxD = dist[ux][uy];
		head++;
		
		for ( i = 0 ; i < 8 ; i++ ){
			vx = ux + dirx[i], vy = uy + diry[i];
			if ( vx >= 0 && vx < LIMIT && vy >= 0 && vy < LIMIT && dist[vx][vy] == 0 ){
				dist[vx][vy] = dist[ux][uy] + 1;
				quuX[tail] = vx;
				quuY[tail] = vy;
				tail++;
			}
		}
	}
}

int inCorner(int ux, int uy){
	if ( ( ux == 0 || ux + 1 == LIMIT ) && ( uy == 0 || uy + 1 == LIMIT ) ) return 1;
	return 0;
}

int f(int x1, int y1, int x2, int y2){
  int dx=abs(x2-x1);
  int dy=abs(y2-y1);
  int lb=(dx+1)/2;
  int tmp;
  
  tmp = (dy+1)/2;
  if ( lb < tmp ) lb = tmp;
  tmp = (dx+dy+2)/3;
  if ( lb < tmp ) lb = tmp;
  
  while ((lb%2)!=(dx+dy)%2) lb++;
  if (abs(dx)==1 && dy==0) return 3;
  if (abs(dy)==1 && dx==0) return 3;
  if (abs(dx)==2 && abs(dy)==2) return 4;
  return lb;
}

int getDist(int ux, int uy, int vx, int vy){
	int ax = vx - ux, ay = vy - uy;
	
	if ( ax < 0 ) ax = -ax;
	if ( ay < 0 ) ay = -ay;
	
	if ( ax == 1 && ay == 1 ){
		if (inCorner(ux, uy) || inCorner(vx, vy)) return 4;
		else return 2;
	}
	
	return dist[ax][ay] - 1;
}

int rawDist[1001][1001];
int visBfs[1001][1001], visTurn;

int getRawDist(int stx, int sty, int enx,  int eny){
	int ux, uy, vx, vy, i;
	
	visTurn++;
	head = tail = 0;
	rawDist[stx][sty] = 0;
	visBfs[stx][sty] = visTurn;
	quuX[tail] = stx, quuY[tail] = sty;
	tail++;

	while ( head != tail ){
		ux = quuX[head], uy = quuY[head];
		if ( ux == enx && uy == eny ) return rawDist[ux][uy];
		head++;

		for ( i = 0 ; i < 8 ; i++ ){
			vx = ux + dirx[i], vy = uy + diry[i];
			if ( vx >= 0 && vx < LIMIT && vy >= 0 && vy < LIMIT && visBfs[vx][vy] != visTurn ){
				rawDist[vx][vy] = rawDist[ux][uy] + 1;
				visBfs[vx][vy] = visTurn;
				quuX[tail] = vx;
				quuY[tail] = vy;
				tail++;
			}
		}
	}
}

int matrix[17][17];
int Turn = 0;
int vis[17][1<<16];
int dp[17][1<<16];

void printMat(){
	int i, j;

	for ( i = 0 ; i < n ; i++ ){
		for ( j = 0 ; j < n ; j++ ) printf("%3d", matrix[i][j]);
		puts("");
	}
}

int rec(int pos, unsigned mask){
	int i;
	int res = INT_MAX, temp;
	
	if ( pos == 0 && mask == ~(~0<<n) ) return 0;
	if ( vis[pos][mask] == Turn ) return dp[pos][mask];
	
	vis[pos][mask] = Turn;
	for ( i = 0 ; i < n ; i++ ){
		if ( i == pos ) continue;
		if ( mask & (1<<i) ) continue;
		if ( i == 0 && ( mask | 1 ) != ~(~0<<n) ) continue;
		temp = rec(i, mask | (1<<i)) + matrix[pos][i];
		if ( temp < res ) res = temp;
	}
	
	return dp[pos][mask] = res;
}

int manHattan(int ux, int uy, int vx, int vy){
	ux -= vx, uy -= vy;
	if ( ux < 0 ) ux = -ux;
	if ( uy < 0 ) uy = -uy;
	return ux + uy;
}

int findMinDist(){
	int i, j;
	
	Turn++;
	for ( i = 0 ; i < n ; i++ ){
		matrix[i][i] = 0;
		for ( j = i + 1 ; j < n ; j++ )
			if ( manHattan(intCells[i][0], intCells[i][1], intCells[j][0], intCells[j][1]) <= 5 )
				matrix[i][j] = matrix[j][i] = getRawDist(intCells[i][0], intCells[i][1], intCells[j][0], intCells[j][1]);
			else matrix[i][j] = matrix[j][i] = getDist(intCells[i][0], intCells[i][1], intCells[j][0], intCells[j][1]);
	}
	
	/*printMat();*/
	return rec(0, 0);
}

int main(){
	int test, ks, i;

	bfs();
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &LIMIT, &n);
			for ( i = 0 ; i < n ; i++ ){
				scanf("%d%d", &intCells[i][0], &intCells[i][1]);
				intCells[i][0]--, intCells[i][1]--;
			}

			printf("Case %d: %d\n", ks, n > 1 ? findMinDist() : 0);
		}
		
		break;
	}
	
	return 0;
}

