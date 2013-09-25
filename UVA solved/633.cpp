#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
int n, sx, sy, dx, dy;
char visited[45][45][4];
int dist[45][45][4];

void initGraph(){
	for ( int i = 0 ; i < n ; i++ )
		for ( int j = 0 ; j < n ; j++ )
			for ( int k = 0 ; k < 4 ; k++ )
			visited[i][j][k] = 0, dist[i][j][k] = INT_MAX;

	dist[sx][sy][0] = 0;
	visited[sx][sy][0] = 1;
}

int bfs(){
	int ux, uy, um, vx, vy, vm;
	queue<int>xs, ys, mvs;
	int xdir[] = {1, 1, 2, 2, -1, -1, -2, -2, 2, 2, -2, -2};
	int ydir[] = {2, -2, 1, -1, -2, 2, 1, -1, 2, -2, 2, -2};
	
	xs.push(sx);
	ys.push(sy);
	mvs.push(0);
	
	while ( xs.empty() == false ){
		ux = xs.front();
		uy = ys.front();
		um = mvs.front();
		
		//cout<<endl<<ux<<' '<<uy<<' '<<um;
		if ( ux == dx && uy == dy ) return dist[ux][uy][um];
		
		xs.pop();
		ys.pop();
		mvs.pop();
		if ( um != 1 ){
			for ( int i = 0 ; i < 8 ; i++ ){
				vx = ux + xdir[i];
				vy = uy + ydir[i];
				vm = 1;
				if ( vx < 0 || vx >= n || vy < 0 || vy >= n ) continue;
				if ( visited[vx][vy][vm] ) continue;
				//cout<<" ("<<vx<<','<<vy<<','<<vm<<")";
				visited[vx][vy][vm] = 1;
				dist[vx][vy][vm] = dist[ux][uy][um] + 1;
				xs.push(vx);
				ys.push(vy);
				mvs.push(vm);
			}
		}
		
		if ( um != 2 ){
			for ( int i = 8 ; i < 12 ; i++ ){
				vx = ux + xdir[i];
				vy = uy + ydir[i];
				vm = 2;
				if ( vx < 0 || vx >= n || vy < 0 || vy >= n ) continue;
				if ( visited[vx][vy][vm] ) continue;
				//cout<<" ("<<vx<<','<<vy<<','<<vm<<")";
				visited[vx][vy][vm] = 1;
				dist[vx][vy][vm] = dist[ux][uy][um] + 1;
				xs.push(vx);
				ys.push(vy);
				mvs.push(vm);
			}
		}
		
		if ( um != 3 ){
			vx = n - ux - 1;
			vy = uy, vm = 3;
			if ( vx >= 0 && vx < n && vy >= 0 && vy < n && visited[vx][vy][vm] == 0 ) {
				//cout<<" ("<<vx<<','<<vy<<','<<vm<<")";
				visited[vx][vy][vm] = 1;
				dist[vx][vy][vm] = dist[ux][uy][um] + 1;
				xs.push(vx);
				ys.push(vy);
				mvs.push(vm);
			}
			
			vy = n - uy - 1;
			vx = ux, vm = 3;
			if ( vx >= 0 && vx < n && vy >= 0 && vy < n && visited[vx][vy][vm] == 0 ) {
				//cout<<" ("<<vx<<','<<vy<<','<<vm<<")";
				visited[vx][vy][vm] = 1;
				dist[vx][vy][vm] = dist[ux][uy][um] + 1;
				xs.push(vx);
				ys.push(vy);
				mvs.push(vm);
			}
		}
	}
	
	return INT_MAX;
}

int main(){
	int u, v;
	
	while ( cin>>n ){
		if ( n == 0 ) break;
		n = (n<<1);
		cin>>sx>>sy>>dx>>dy;
		sx--, sy--, dx--, dy--;
		initGraph();
		while ( cin>>u>>v ){
			if ( u == 0 && v == 0 ) break;
			u--, v--;
			for ( int i = 0 ; i < 4 ; i++ )
				visited[u][v][i] = 1;
		}
		
		v = bfs();
		if ( v == INT_MAX ) cout<<"Solution doesn't exist"<<endl;
		else cout<<"Result : "<<v<<endl;
	}
	
	return 0;
}

