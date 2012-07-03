#include <stdio.h>
#include <string.h>
#define SIZE 52
using namespace std;
int adj[SIZE][SIZE];
int degree[SIZE], list[15000], indx;

void call_euler(int u, int n){
    int i;

    for( i = 1 ; i <= n ; i++ ){
        if( adj[u][i]){
            adj[u][i]--;
            adj[i][u]--;
            call_euler(i, n);
            list[indx++] = u;
        }
    }
}

void print_order(int n, int m){
    int i;

    indx = 0;
    for ( i = 0 ; i < SIZE ; i++ ) if ( degree[i] ) break;
    call_euler(i, n);

    if ( indx != m ){
        puts("some beads may be lost");
        return;
    }
    list[indx] = list[0];
    for( i = 0 ; i < indx ; i++ ) printf("%d %d\n", list[i],list[i+1]);
}

int main(){
    int test, kase, n, u, v, m, i;
#ifndef ONLINE_JUDGE
    char name[] = __FILE__;
    strcat(name, ".out");
    freopen(name, "w", stdout);
#endif
    while(scanf("%d", &test)!=EOF){
        for( kase = 1 ; kase <= test; kase++){
            if(kase > 1) puts("");
            for( scanf("%d", &m), i = n = 0 ; i < m ; i++ ){
                scanf("%d%d", &u, &v);
                if(u > n) n = u;
                if(v > n) n = v;
                adj[u][v]++, adj[v][u]++;
                degree[u]++, degree[v]++;
            }

            for( i = 1 ; i <= n ; i++ ){
                if( degree[i] & 1 ) break;
            }
            printf("Case #%d\n", kase);
            if( i <= n ) puts("some beads may be lost");
            else print_order(n, m);
            memset(adj, 0, sizeof(adj));
            memset(degree, 0, sizeof(degree));
        }
    }

    return 0;
}
/*
8
5
1 2
2 3
3 4
4 5
5 6
5
2 1
2 2
3 4
3 1
2 4
5
1 2
2 3
3 4
4 5
5 6
5
2 1
2 2
3 4
3 1
2 4
5
1 2
2 3
3 4
4 5
5 6
5
2 1
2 2
3 4
3 1
2 4
4
1 2
2 1
3 4
3 4
5
2 2
2 2
2 2
2 2
2 2
*/
