#include <stdio.h>
#include <math.h>
#include <float.h>
#define SIZE 105
#define EPS 1e-9
#define INF 1<<14

double gopherPos[SIZE][2], holePos[SIZE][2];
int adj[SIZE << 1][SIZE << 1];
int degree[SIZE << 1], pair[SIZE << 1];
int NIL;

double distance(int gopherIndex, int holeIndex){
    double delx = gopherPos[gopherIndex][0] - holePos[holeIndex][0];
    double dely = gopherPos[gopherIndex][1] - holePos[holeIndex][1];
    return sqrt(delx*delx + dely*dely);
}

int Queue[SIZE << 1], head, tail;
int dist[SIZE << 1];
int bfsAugment(int n){
    int i, u, v;
    
    head = tail = 0;
    for ( i = 0 ; i < n ; i++ )
        if ( pair[i] == NIL ){
            dist[i] = 0;
            Queue[tail++] = i;
        }
        else dist[i] = INF;
        
    dist[NIL] = INF;
    
    while ( head != tail ){
        u = Queue[head++];
        for ( i = 0 ; i < degree[u] ; i++ ){
            v = adj[u][i];
            if ( dist[pair[v]] == INF ){
                dist[pair[v]] = dist[u] + 1;
                Queue[tail++] = pair[v];
            }
        }
    }
    
    return (dist[NIL] != INF);
}

int dfsMatch(int u){
    int i, v;
    
    if ( u != NIL ){
        for ( i = 0 ; i < degree[u] ; i++ ){
            v = adj[u][i];
            if ( dist[pair[v]] == dist[u] + 1 ){
                if ( dfsMatch(pair[v]) ){
                    pair[u] = v;
                    pair[v] = u;
                    return 1;
                }
            }
        }
        
        dist[u] = INF;
        return 0;
    }
    return 1;
}

int bipartiteMatch(int n, int m){
    int matching = 0, i;
    
    NIL = n + m;
    for ( i = 0 ; i <= NIL ; i++ ) pair[i] = NIL;
    
    while ( bfsAugment(n) ){
        for ( i = 0 ; i < n ; i++ ){
            if ( pair[i] == NIL && dfsMatch(i) )
                matching++;
        }
    }
    
    return matching;
} 

int main(){
    int n, m, s, v, i, j;
    double temp;
    
    while ( scanf("%d%d%d%d", &n, &m, &s, &v) == 4 ) {
        for ( i = 0 ; i < n ; i++ )
            scanf ( "%lf%lf", &gopherPos[i][0], &gopherPos[i][1]);
        for ( i = 0 ; i < m ; i++ )
            scanf ( "%lf%lf", &holePos[i][0], &holePos[i][1]);
        
        for ( i = 0 ; i < n ; i++ )
            for ( degree[i] = j = 0 ; j < m ; j++ ){
                temp = distance(i, j) - s * v;
                if ( fabs(temp) < EPS || temp < 0 ){
                    adj[i][degree[i]++] = n + j;
                }
            }
            
        printf("%d\n", n - bipartiteMatch(n, m));
    }
    
    return 0;
}
