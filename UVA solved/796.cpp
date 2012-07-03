#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#define INF 1<<30
enum { WHITE, GRAY, BLACK };
using namespace std;

class Bridge{
public:
    int u, v;
    Bridge(int x, int y) { u = x, v = y; if ( u > v ) u ^= v ^= u ^= v; }
    bool operator<(const Bridge &b) const{
        return ( u == b.u ) ? (v < b.v) : (u < b.u) ;
    }
};

vector< Bridge >bridges;
vector< list<int> > adj(10004);
int par[10004], startTime[10004], L[10004];
char color[10004];
int n, GLTIME;

void intGraph(){
    for ( int i = 0 ; i <= n ; i++ ) par[i] = -1, L[i] = startTime[i] = 0, color[i] = WHITE;
    GLTIME = 0;
}

void dfs(int u){
    int v;
    list<int>::iterator ptr;

    //printf("%d about to be visited\n", u);
    color[u] = GRAY;
    L[u] = startTime[u] = ++GLTIME;
    for ( ptr = adj[u].begin(); ptr!=adj[u].end();ptr++){
        v = *ptr;
        /*if ( v != par[u] && startTime[v] < startTime[u] ){
            stack1[tail] = u;
            stack2[tail++] = v;
            //printf("%d -> %d added\n", u, v);
        }*/

        if ( startTime[v] == 0 ){
            par[v] = u;
            dfs(v);
            if ( L[v] == startTime[v] ){
                //printf("bridges : %d -> %d\n", u, v);
                Bridge tmp(u,v);
                bridges.push_back(tmp);
                /*do{
                    tail--;
                  //  printf("%d -> %d\n", stack1[tail], stack2[tail]);
                }while(!((stack1[tail]==u && stack2[tail]==v) || (stack2[tail]==u && stack1[tail]==v)));
                //printf("Ok\n");*/
            }
            
            if (L[u] > L[v]) L[u] = L[v];
        }
        else if ( par[u] != v && L[u] > startTime[v] ) L[u] = startTime[v];
    }

    color[u] = BLACK;
}

void preprocess(){
    int i,j;

    intGraph();
    
    for ( i = 0 ; i < n ; i++ ){
        if ( color[i] == WHITE ) dfs(i);
    }
}

int main(){
    int r, q, u, v, i;

    while(scanf("%d", &n)!=EOF){
        for ( i = 0 ; i <= n ; i++ ){
            list<int> temp;
            adj[i] = temp;
        }

        for( i = 0 ; i < n ; i++) {
            scanf("%d ( %d )", &u, &r);
            while(r--){
                scanf("%d", &v);
                if ( u == v ) continue;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        preprocess();
        
        sort(bridges.begin(), bridges.end());
        printf("%d critical links\n", q = bridges.size());
        for ( i = 0 ; i < q ; i++ ) printf("%d - %d\n", bridges[i].u, bridges[i].v);
        puts("");
        
        bridges.clear();

        for ( i = 0 ; i <= n ; i++ ) adj[i].clear();
    }

    return 0;
}
