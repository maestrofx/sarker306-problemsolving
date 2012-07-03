#include <stdio.h>
#define MAXEDGE 10005
#define NOEDGE -10000
#define MAXVERTICES 102
#define INF (1 << 12)
int allEdges[MAXEDGE][2], edgeCount;
int rightSibling[MAXEDGE], leftChild[MAXVERTICES<<1];

void buildEdge(int left, int nodes, long *arr){
    int i, j;
    
    for ( i = 1 ; i <= left ; i++ )
        for ( j = left + 1 ; j <= nodes ; j++ )
            if ( ( arr[i] == arr[j] ) || ( arr[i] && arr[j] % arr[i] == 0 ) ){
                allEdges[edgeCount][0] = i, allEdges[edgeCount][1] = j;
                rightSibling[edgeCount] = leftChild[i];
                leftChild[i] = edgeCount++;
            }
}

int queue[MAXVERTICES + 1], head, tail;
int dist[MAXVERTICES], pair[MAXVERTICES<<1];

int bfsAugment(int left){
    int i, u, v;
    
    dist[0] = INF;
    head = tail = 0;
    for ( i = 1 ; i <= left ; i++ )
        if ( pair[i] == 0 ){
            dist[i] = 0;
            queue[tail++] = i;
        }
        else dist[i] = INF;

    while ( head != tail ){
        u = queue[head++];
        for ( i = leftChild[u] ; i != NOEDGE ; i = rightSibling[i] ){
            v = allEdges[i][1];
            if ( dist[pair[v]] == INF ){
                dist[pair[v]] = dist[u] + 1;
                queue[tail++] = pair[v];
            }
        }
    }
    
    return ( dist[0] != INF );
}

int dfsAugment(int u){
    int i, v;
    
    if ( u == 0 ) return 1;
    for ( i = leftChild[u] ; i != NOEDGE ; i = rightSibling[i] ){
        v = allEdges[i][1];
        if ( dist[pair[v]] == dist[u] + 1 ){
            if ( dfsAugment(pair[v]) ){
                pair[v] = u, pair[u] = v;
                return 1;
            }
        }
    }
    
    dist[u] = INF;
    return 0;
}

int minimumNumbersToRemove( int left ){
    int matching = 0, i;
    
    while ( bfsAugment(left) )
        for ( i = 1 ; i <= left ; i++ )
            if ( pair[i] == 0 && dfsAugment(i) ) matching++;

    return matching;
}

void initGraph(int nodes){
    int i;
    
    edgeCount = 0;
    for ( i = 0 ; i <= nodes ; i++ ){
        pair[i] = 0;
        leftChild[i] = NOEDGE;
    }
}

int main(){
    int m, n, test, kase, i, j;
    long arr[MAXVERTICES<<1];
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d", &m);
            for ( i = 1 ; i <= m ; i++ ) scanf("%ld", &arr[i]);
            scanf("%d", &n);
            n += m;
            initGraph(n);
            for ( j = i ; j <= n ; j++ ){
                scanf("%ld", &arr[j]);
                for ( i = 1 ; i <= m ; i++ )
                    if ( ( arr[i] == arr[j] ) || ( arr[i] && arr[j] % arr[i] == 0 ) ){
                        allEdges[edgeCount][0] = i, allEdges[edgeCount][1] = j;
                        rightSibling[edgeCount] = leftChild[i];
                        leftChild[i] = edgeCount++;
                    }
            }
            
            /*buildEdge(m, n, arr);*//* integrated to Main to get better runtime */
            printf("Case %d: %d\n", kase, minimumNumbersToRemove(m));
        }
    }
    
    return 0;
}
