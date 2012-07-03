#include <stdio.h>
#include <math.h>
#include <float.h>
#define SIZE 105
#define EPS 1e-9
#define INF 1<<14

int dogPos[SIZE][2], placePos[SIZE][2];
int adj[SIZE << 1][SIZE << 1];
int degree[SIZE << 1], pair[SIZE << 1];
int NIL;

double distance(int dogIndex, int placeIndex){
    double delx = dogPos[dogIndex][0] - placePos[placeIndex][0];
    double dely = dogPos[dogIndex][1] - placePos[placeIndex][1];
    return sqrt(delx*delx + dely*dely);
}

double distanceBetweenDogPos(int dogIndex){
    double delx = dogPos[dogIndex][0] - dogPos[dogIndex+1][0];
    double dely = dogPos[dogIndex][1] - dogPos[dogIndex+1][1];
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
    
    for ( i = 0 ; i <= NIL ; i++ ) pair[i] = NIL;
    
    while ( bfsAugment(n) ){
        for ( i = 0 ; i < n ; i++ ){
            if ( pair[i] == NIL && dfsMatch(i) )
                matching++;
        }
    }
    
    return matching;
} 

void initGraph(int n, int m){
    int i;
    
    NIL = n + m;
    for ( i = 0 ; i <= NIL ; i++ ) degree[i] = 0;
}

int main(){
    int n, m, i, j, test;
    double temp;
    
    scanf("%d", &test);
    while ( test-- ) {
        scanf("%d%d", &n, &m);
        initGraph(n - 1, m);
        
        for ( i = 0 ; i < n ; i++ )
            scanf ( "%d%d", &dogPos[i][0], &dogPos[i][1]);
        for ( i = 0 ; i < m ; i++ )
            scanf ( "%d%d", &placePos[i][0], &placePos[i][1]);
        
        n--;
        for ( i = 0 ; i < n ; i++ )
            for ( j = 0 ; j < m ; j++ ){
                temp = distance(i, j) + distance(i + 1, j) - 2 * distanceBetweenDogPos(i);
                if ( fabs(temp) < EPS || temp < 0 ){
                    adj[i][degree[i]++] = n + j;
                }
            }
            
        printf("%d\n", 1 + n + bipartiteMatch(n, m));
        for ( i = 0 ; i < n ; i++ ){
            printf("%d %d ", dogPos[i][0], dogPos[i][1]);
            if ( NIL != pair[i] ){
                j = pair[i] - n;
                printf("%d %d ", placePos[j][0], placePos[j][1]);
            }
        }
        printf("%d %d\n", dogPos[i][0], dogPos[i][1]);
        if ( test ) puts("");
    }
    
    return 0;
}
