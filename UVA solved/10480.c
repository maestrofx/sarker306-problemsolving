#include <stdio.h>
#define MAXEDGE 1003
#define MAXVERTICES 52
#define NOEDGE -10000
#define INF ~0

unsigned long edgeCapacity[MAXEDGE], residualCapacity[MAXEDGE];
int unreachableEdges[MAXEDGE], unreachableInd;
int edges[MAXEDGE][2], rightSibling[MAXEDGE];
int parentEdge[MAXVERTICES], leftChild[MAXVERTICES];
unsigned long inFlow[MAXVERTICES];

int queue[MAXVERTICES], head, tail;

unsigned long bfsAugment(int n){
    int i, u, v;
    static int source = 1, sink = 2;
    
    head = tail = 0;
    queue[tail++] = source;
    inFlow[source] = INF;
    
    unreachableInd = 0;
    for ( i = 2 ; i <= n ; i++ ) inFlow[i] = 0;
    
    while ( head != tail ){
        u = queue[head++];
        if ( u == sink ) break;
        
        /*printf("%d ->", u);*/
        for ( i = leftChild[u] ; i != NOEDGE ; i = rightSibling[i] ){
            v = edges[i][1];
            /*printf(" %d(%lu)", v, residualCapacity[i]);*/
            if ( residualCapacity[i] > 0 && inFlow[v] == 0 ){
                inFlow[v] = inFlow[u];
                if ( residualCapacity[i] < inFlow[v] )
                    inFlow[v] = residualCapacity[i];
                
                queue[tail++] = v;
                parentEdge[v] = i;
            }
            else if ( residualCapacity[i] == 0 )
                unreachableEdges[unreachableInd++] = i;
        }
        
        /*puts("");*/
    }
    
    return inFlow[sink];
}

void minimumCut(int n){
    static int source = 1, sink = 2;
    int v, i;
    unsigned long maxFlow = 0, currFlow;
    
    while ( currFlow = bfsAugment(n) ){
        maxFlow += currFlow;
        for( v = sink ; v != source ; v = edges[i][0] ){
            /*printf("<> %d(%lu)", v, inFlow[v]);*/
            i = parentEdge[v];
            residualCapacity[i] -= currFlow;
            residualCapacity[i^1] += currFlow;
            /*printf("-> (%d %d %lu),", edges[i][0], edges[i][1], residualCapacity[i]);
            printf(" (%d %d %lu)\n", edges[i^1][0], edges[i^1][1], residualCapacity[i^1]);*/
        }
    }
    
    /*printf("#%lu\n", maxFlow);*/
    for ( i = 0 ; i < unreachableInd ; i++ )
        if ( inFlow[edges[unreachableEdges[i]][1]] == 0 )
        printf("%d %d\n", edges[unreachableEdges[i]][0], edges[unreachableEdges[i]][1]);
    puts("");
}

int main(){
    int n, m, i, u;
    
    /*printf("%lu\n", INF);*/
    while ( scanf("%d%d", &n, &m) != EOF ){
        if ( n == 0 && m == 0 ) break;
        for ( i = 0 ; i <= n ; i++ ){
            leftChild[i] = NOEDGE;
        }
        
        for ( i = 0, m <<= 1 ; i < m ; i += 2 ){
            scanf("%d%d%lu", &edges[i][0], &edges[i][1], &edgeCapacity[i]);
            u  = edges[i][0];
            rightSibling[i] = leftChild[u];
            leftChild[u] = i;
            
            edges[i^1][0] = edges[i][1], edges[i^1][1] = u;
            edgeCapacity[i^1] = edgeCapacity[i];
            rightSibling[i^1] = leftChild[edges[i^1][0]];
            leftChild[edges[i^1][0]] = i^1;
            
            residualCapacity[i] = residualCapacity[i^1] = edgeCapacity[i];
        }
        
        /*for ( i = 0 ; i < m ; i++ )
            printf("# %d %d %lu\n", edges[i][0], edges[i][1], edgeCapacity[i]);*/
        minimumCut(n);
    }
    
    return 0;
}
/*
7 8
1 3 10
3 4 3
3 5 3
3 6 3
4 2 4
5 7 4
6 7 4
7 2 4
*/
