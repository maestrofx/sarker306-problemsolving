#include <stdio.h>

#define MAXVERTICES 1001

int leftChild[MAXVERTICES], rightSibling[MAXVERTICES<<2], parent[MAXVERTICES];
int edges[MAXVERTICES<<2][2], edgeCount;
int arr[MAXVERTICES][2];

void maximumIndependentSet(int u){
    int i, v;
    arr[u][0] = 0, arr[u][1] = 1;
    
    for ( i = leftChild[u] ; i != -1 ; i = rightSibling[i] ){
        v = edges[i][1];
        if ( parent[v] == -1 ){
            parent[v] = u;
            maximumIndependentSet(v);
            arr[u][1] += arr[v][0], arr[u][0] += (arr[v][1] > arr[v][0])?arr[v][1] : arr[v][0];
        }
    }
}

int main(){
    int n, m, v, i;
    
    while ( scanf("%d", &n) == 1 && n > 0 ){
        edgeCount = 0;
        for ( i = 1 ; i <= n ; i++ ){
            leftChild[i] = -1;
            parent[i] = -1;
            scanf("%d", &m);
            while ( m-- ){
                scanf("%d", &v);
                edges[edgeCount][0] = i, edges[edgeCount][1] = v;
                rightSibling[edgeCount] = leftChild[i];
                leftChild[i] = edgeCount++;
            }
        }
        
        parent[1] = 1;
        maximumIndependentSet(1);
        if ( n > 1 ) printf("%d\n", n - (arr[1][1] > arr[1][0] ? arr[1][1] : arr[1][0]) );
        else printf("%d\n", arr[1][1]);
    }
    
    return 0;
}
