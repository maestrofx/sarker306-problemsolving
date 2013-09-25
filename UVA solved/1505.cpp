#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <set>
#include <string>
#include <deque>
#include <queue>
#include <map>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

using namespace std;

#define MAXROW 15
#define MAXREG MAXROW*MAXROW
#define MAXCOLR 6
#define MAXDBSZ 1000000

int coloredReg[MAXCOLR];
int regionMusk[MAXREG], regionCol[MAXREG], regCnt; /* in a 8 * 8 board, no more than 64 regions */
int grid[MAXROW][MAXROW], len;
int region[MAXROW][MAXROW], regSize[MAXROW][MAXROW];
long vis[MAXROW][MAXROW], Turn;
int minMove;
long stateVisited;
int dirX[] = { -1, 0, 0, 1 }, dirY[] = { 0, 1, -1, 0 };

void printGrid(int g[][MAXROW]){
	int i, j;

	for ( i = 0 ; i < len ; i++ ){
		for ( j = 0 ; j < len ; j++ ) printf("%3d", g[i][j]);
		puts("");
	}

	puts("");
}

int minMoveToColorAll(){
	int i, j;
	char used[MAXCOLR];
	
	memset(used, 0, sizeof(used));
	for ( i = 0 ; i < len ; i++ )
		for ( j = 0 ; j < len ; j++ )
			if ( used[grid[i][j]] == 0 ) used[grid[i][j]] = 1;

	for ( i = j = 0 ; i < MAXCOLR ; i++ ) if ( used[i] ) j++;
	return j;
}

int minMoveToReachFarthestCorner(){
	deque<int> q;
	int ux, uy, vx, vy, i;
	int dis[MAXROW][MAXROW], maxi = 0;
	
	memset(dis, 0, sizeof(dis));
	++Turn;
	vis[0][0] = Turn;
	q.push_back(0);
	q.push_back(0);
	
	while ( q.empty() == false ){
		ux = q.front();
		q.pop_front();
		uy = q.front();
		q.pop_front();
		
		for ( i = 0 ; i < 4 ; i++ ){
			vx = ux + dirX[i], vy = uy + dirY[i];
			
			if ( vx >= 0 && vx < len && vy >= 0 && vy < len ){
				if ( vis[vx][vy] == Turn ) continue;
				vis[vx][vy] = Turn;
				
				if ( grid[vx][vy] == grid[ux][uy] ){
					dis[vx][vy] = dis[ux][uy];
					q.push_front(vy);
					q.push_front(vx);
					continue;
				}
				dis[vx][vy] = dis[ux][uy] + 1;
				if ( maxi < dis[vx][vy] ) maxi = dis[vx][vy];
				q.push_back(vx);
				q.push_back(vy);
			}
		}
	}
	
	return maxi;
}

int heuristic(){
	int a = minMoveToColorAll(), b = minMoveToReachFarthestCorner();
	return a > b ? a : b;
}

int floodFill(int x, int y, int col, int g[][MAXROW]){
	int i, r, c, coloredSoFar = 1;

	for ( i = 0 ; i < 4 ; i++ ){
		r = x + dirX[i], c = y + dirY[i];
		if ( r >= 0 && r < len && c >= 0 && c < len ){
			if ( vis[r][c] != Turn && grid[r][c] == grid[x][y] ){
				vis[r][c] = Turn;
				coloredSoFar += floodFill(r, c, col, g);
			}
		}
	}

	g[x][y] = col;
	return coloredSoFar;
}

int findNewRegionSize(int x, int y){
	int size = 1, i, r, c;

	for ( i = 0 ; i < 4 ; i++ ){
		r = x + dirX[i], c = y + dirY[i];
		if ( r >= 0 && r < len && c >= 0 && c < len ){
			if ( vis[r][c] != Turn && grid[r][c] == grid[x][y] ){
				vis[r][c] = Turn;
				size += findNewRegionSize(r, c);
			}
		}
	}

	return size;
}

int touchBoundary(int x, int y, int* arr){
	int i, r, c;

	for ( i = 0 ; i < 4 ; i++ ){
		r = x + dirX[i], c = y + dirY[i];
		if ( r >= 0 && r < len && c >= 0 && c < len ){
			if ( grid[r][c] == grid[x][y] ){
				if ( vis[r][c] != Turn ){
					vis[r][c] = Turn;
					touchBoundary(r, c, arr);
				}
			}
			else if ( arr[region[r][c]] == 0 ) arr[region[r][c]] = 1;
		}
	}
}

int findMostPromisingColor(){
	int regTouched[MAXREG], coloredCell[MAXCOLR], i, max = INT_MIN, selectedCol;

	for ( i = 0 ; i < regCnt ; i++ ) regTouched[i] = 0;
	for ( i = 0 ; i < MAXCOLR ; i++ ) coloredCell[i] = 0;
	vis[0][0] = ++Turn;
	touchBoundary(0, 0, regTouched);
	for ( i = 0 ; i < regCnt ; i++ ){
		if ( regTouched[i] ) coloredCell[regionCol[i]] += regionMusk[i];
	}

	for ( i = 0 ; i < MAXCOLR ; i++ )
		if ( coloredCell[i] > max ) max = coloredCell[i], selectedCol = i;

	return selectedCol;
}

int findMoveIntelligent(){
	int i, j, col = grid[0][0], flag, move;
	int tempGrid[MAXROW][MAXROW];

	for ( i = 0 ; i < len ; i++ )
		for ( j = 0 ; j < len ; j++ )
			tempGrid[i][j] = grid[i][j];

	for ( move = 0 ; ; move++ ){
		flag = 1;
		for ( i = 0 ; i < len && flag ; i++ )
			for ( j = 0 ; j < len && flag ; j++ ){
				if ( grid[i][j] != grid[0][0] ) flag = 0;
			}

		if ( flag == 1 ){
			if ( minMove > move ) minMove = move;
			printf("Greedily Complete!!! with %d move\n", move);
			break;
		}

		col = findMostPromisingColor();
		vis[0][0] = ++Turn;
		floodFill(0, 0, col, grid);
		/*printf("Colored with %d\n", col);
		/*printGrid(grid);*/
	}

	for ( i = 0 ; i < len ; i++ )
		for ( j = 0 ; j < len ; j++ )
			grid[i][j] = tempGrid[i][j];

	return move;
}

typedef struct Pos{
	int color, boundary;
}Pos;

int Compare(const void *a, const void *b){
	Pos *x = (Pos*)a, *y = (Pos*)b;

	return y->boundary - x->boundary;
}

int findPerimeter(int x, int y, int g[][MAXROW]){
	int i, r, c, perimeter = 0;

	for ( i = 0 ; i < 4 ; i++ ){
		r = x + dirX[i], c = y + dirY[i];
		if ( r >= 0 && r < len && c >= 0 && c < len ){
			if ( vis[r][c] != Turn && g[r][c] == g[x][y] ){
				vis[r][c] = Turn;
				perimeter += findPerimeter(r, c, g);
			}
			else perimeter++;
		}
	}

	return perimeter;
}

set<string> visitedState;

void stateToString(char *to){
	int i, j;

	for ( i = 0 ; i < len ; i++ )
		for ( j = 0 ; j < len ; j++ )
			to[i*len + j] = grid[i][j] + '0';

	to[i*i] = 0;
}

void stringToState(char *from){
	int i, j;

	for ( i = 0 ; i < len ; i++ )
		for ( j = 0 ; j < len ; j++ )
			grid[i][j] = from[i*len + j] -'0';
}

void findMoveBackTrack(int move){
	int i, j, k, col = grid[0][0], improv = 0, flag = 1;
	int tempGrid[MAXROW][MAXROW];
	Pos currentStatus[MAXCOLR];
	int regTouched[MAXREG];
	char stateStr[MAXROW * MAXROW + 1];

	stateToString(stateStr);
	if ( visitedState.find(stateStr) != visitedState.end()) return;
	
	if ( stateVisited < MAXDBSZ ) visitedState.insert(stateStr);
	stateVisited++;
	
	for ( i = 0 ; i < len && flag ; i++ )
		for ( j = 0 ; j < len && flag ; j++ ){
			if ( grid[i][j] != grid[0][0] ) flag = 0;
		}

	if ( flag == 1 ){
		if ( minMove > move ) minMove = move;
		/*printf("Complete!!! with %d move\n", move);
		/*printGrid(grid);
		/*getchar();*/
		return;
	}

	for ( i = 0, flag = 0 ; i < MAXCOLR ; i++ )
		if ( coloredReg[i] ) flag++;

	if ( minMove - move < flag ) return;
	if ( minMove - move < minMoveToReachFarthestCorner() ) return;

	for ( j = 0 ; j < regCnt ; j++ ) regTouched[j] = 0;
	vis[0][0] = ++Turn;
	touchBoundary(0, 0, regTouched);

	for ( i = 0 ; i < MAXCOLR ; i++ ){
		currentStatus[i].boundary = 0;
		currentStatus[i].color = i;
		if ( grid[0][0] == i ) continue;
		if ( coloredReg[i] == 0 ) continue;

		for ( j = 0 ; j < len ; j++ )
			for ( k = 0 ; k < len ; k++ ) tempGrid[j][k] = grid[j][k];

		vis[0][0] = ++Turn;
		floodFill(0, 0, i, tempGrid);
		vis[0][0] = ++Turn;
		currentStatus[i].boundary = findPerimeter(0, 0, tempGrid);
	}

	qsort(currentStatus, MAXCOLR, sizeof(Pos), Compare);
	/*printf("In move %d\n", move);
	for ( i = 0 ; i < MAXCOLR ; i++ ) printf("color : %d, boundary : %d\n", currentStatus[i].color, currentStatus[i].boundary);
 	*/
	for ( i = 0 ; i < MAXCOLR ; i++ ){
		if ( currentStatus[i].boundary == 0 ) break;

		for ( j = 0 ; j < len ; j++ )
			for ( k = 0 ; k < len ; k++ ) tempGrid[j][k] = grid[j][k];

		vis[0][0] = ++Turn;
		floodFill(0, 0, currentStatus[i].color, grid);

		for ( j = 0 ; j < regCnt ; j++ ){
			if ( regTouched[j] && regionCol[j] == currentStatus[i].color)
				coloredReg[regionCol[j]] --;
		}

		/*printf("Move %d, colored by %d\n", move, currentStatus[i].color);
		printGrid(grid);*/
		findMoveBackTrack(move + 1);

		for ( j = 0 ; j < regCnt ; j++ ){
			if ( regTouched[j] && regionCol[j] == currentStatus[i].color)
				coloredReg[regionCol[j]]++;
		}

		for ( j = 0 ; j < len ; j++ )
			for ( k = 0 ; k < len ; k++ ) grid[j][k] = tempGrid[j][k];
	}
}

struct PQPos{
	char state[MAXROW * MAXROW + 1];
	int g, h;
};

int costFunc(const PQPos &a){
	return 2 * a.g + 5 * a.h;
	//return ( 3*minMove + a.g ) * a.g + ( 6*minMove - a.g ) * a.h;
}

struct Cmp{
public:
	bool operator()(const PQPos &a, const PQPos &b){
		return costFunc(a) > costFunc(b);
	}
};

map<string, int>stateDist;
priority_queue<PQPos, vector<PQPos>, Cmp > pq;

int findMoveAStar(){
	PQPos start;
	int i, j, k, tempVal;
	map<string, int>::iterator ptr;
	int tempGrid[MAXROW][MAXROW];
	Pos currentStatus[MAXCOLR];
	int regTouched[MAXREG];
	
	stateDist.clear();
	while (pq.empty() == false) pq.pop();

	stateVisited = 0;
	start.g = 0;
	start.h = heuristic();
	stateToString(start.state);
	pq.push(start);
	stateDist.insert(pair<string, int>(start.state, costFunc(start)));
	
	while ( pq.empty() == false ){
		stateVisited++;
		PQPos u = pq.top();
		pq.pop();

	//	printf("%s %d %d %d\n", u.state, u.g, u.h, costFunc(u));
		for ( i = 0 ; u.state[i] ; i++ ) if ( u.state[i] != u.state[0] ) break;
		if ( u.state[i] == 0 ){
			minMove = u.g;
			return u.g;
		}

		for ( i = 0 ; i < MAXCOLR ; i++ ){
			currentStatus[i].boundary = 0;
			currentStatus[i].color = i;
			if ( u.state[0] == i ) continue;
			
			for ( j = 0 ; u.state[j] != '0' + i && u.state[j] ; j++ );
			if ( u.state[j] == 0 ) continue;

		//	printf("Color %d can be applied...\n", i);
			for ( j = 0 ; j < len ; j++ )
				for ( k = 0 ; k < len ; k++ ) tempGrid[j][k] = u.state[j*len + k] - '0';

			vis[0][0] = ++Turn;
			floodFill(0, 0, i, tempGrid);
			vis[0][0] = ++Turn;
			currentStatus[i].boundary = findPerimeter(0, 0, tempGrid);
		}

		qsort(currentStatus, MAXCOLR, sizeof(Pos), Compare);

		for ( i = 0 ; i < MAXCOLR ; i++ ){
			if ( currentStatus[i].boundary == 0 ) break;

			if ( u.state[0] == currentStatus[i].color + '0' ) continue;
			stringToState(u.state);
			vis[0][0] = ++Turn;
			floodFill(0, 0, currentStatus[i].color, grid);
		//	printGrid(grid);

			PQPos v;
			stateToString(v.state);
			v.g = u.g + 1;
			v.h = heuristic();
			ptr = stateDist.find(v.state);
			tempVal = costFunc(v);

			ptr = stateDist.find(v.state);
			if ( ptr != stateDist.end() ){
				if ( ptr->second < tempVal ) continue;
				ptr->second = tempVal;
			}
			else stateDist.insert(pair<string, int>(v.state, tempVal));

			pq.push(v);
		}
	}
}

int findMinMove(){
	minMove = INT_MAX;
	/*findMoveIntelligent();

	if ( len <= 8 ){
		stateVisited = 0;
		findMoveBackTrack(0);

		printf("%ld states visited\n", stateVisited);
		printf("Backtracking MinMove = %d\n", minMove);
	}*/

	findMoveAStar();
	//printf("%ld states visited\n", stateVisited);
	//printf("A* MinMove = %d\n", minMove);
	
	return minMove;
}

void preprocessGrid(){
	int i, j, thisRegion;

	regCnt = 0;

	for ( i = 0 ; i < MAXCOLR ; i++ ) coloredReg[i] = 0;
	for ( i = 0 ; i < len ; i++ )
		for ( j = 0 ; j < len ; j++ )
			regSize[i][j] = -1;

	for ( i = 0 ; i < len ; i++ )
		for ( j = 0 ; j < len ; j++ )
			if ( regSize[i][j] == -1 ){
				vis[i][j] = ++Turn;
				thisRegion = findNewRegionSize(i, j);
				vis[i][j] = ++Turn;
				floodFill(i, j, thisRegion, regSize);
				vis[i][j] = ++Turn;
				floodFill(i, j, regCnt, region);

				coloredReg[grid[i][j]]++;
				regionCol[regCnt] = grid[i][j];
				regionMusk[regCnt++] = thisRegion;
			}

	/*printGrid(region);
	printGrid(regSize);*/
}

int main(){
	int i, j;
	char inp[20];

	while ( scanf("%d", &len) == 1 ){
		if ( len == 0 ) break;
		for ( i = 0 ; i < len ; i++ ){
			scanf("%s", inp);
			for ( j = 0 ; j < len ; j++ ) grid[i][j] = inp[j] - '0';
			//for ( j = 0 ; j < len ; j++ ) scanf("%d", &grid[i][j]);
		}

		preprocessGrid();
		printf("%d\n", findMinMove());
		visitedState.clear();
	}

	return 0;
}
/*
8
12045133
31322304
55555304
45120312
12345012
23450123
12312312
33333333
8
01234501
23450123
45012345
01234501
23450123
45012345
01234501
23450123
8
01234501
34501234
01234501
34501234
01234501
34501234
01234501
34501234
*/
