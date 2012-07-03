#include <cstdio>
#include <list>
#include <queue>
#include <iostream>
#define SIZE 205
#define INF 255
using namespace std;
//FOR UNDIRECTED GRAPH
class Graph{
protected:
    int node, adj[SIZE][SIZE];
public:
    virtual void addEdge(int u, int v) = 0;
};

class BreadthFirst : protected Graph{
private:
    queue<int> Queue;
protected:
    int level[SIZE];
public:
    void bfs(int start){
        int u, v;
        
        level[start] = 1;
        Queue.push(start);
        while ( Queue.empty() == false ){
            u = Queue.front();
            Queue.pop();
            
            for ( v = 0 ; v < node ; v++ ){
                if ( adj[u][v] == 1 && level[v] == INF ){
                    level[v] = level[u] + 1;
                    Queue.push(v);
                }
            }
        }
    }
};

class CheckEulerCircuit : protected BreadthFirst{
    int degree[SIZE];
public:
    int checkEulerCircuitPossibility();
    CheckEulerCircuit(int _node);
    void addEdge(int u, int v);
    ~CheckEulerCircuit();
};

CheckEulerCircuit::CheckEulerCircuit(int _node){
    int i, u;
    node = _node;
    
    for ( i = 0 ; i < node ; i++ ){
            level[i] = INF, degree[i] = 0;
            for ( u = 0 ; u < node ; u++ )
                adj[i][u] = 0;
        }
}

CheckEulerCircuit::~CheckEulerCircuit(){}

void CheckEulerCircuit::addEdge(int u, int v){
    adj[u][v] = adj[v][u] = 1, degree[v]++, degree[u]++;
}

int CheckEulerCircuit::checkEulerCircuitPossibility(){
    int i, possibleCircuit = 1;
    
    for ( i = 0 ; i < node ; i++ ){
        /*printf("indegree[%d] = %d, outdegree[%d] = %d\n", i, inDegree[i], i, outDegree[i]);*/
        if ( degree[i] == 0 || degree[i] & 1 ) possibleCircuit = 0;
    }
    
    if ( possibleCircuit != 0 ) {
        bfs(0);
        
        for ( i = 0 ; i < node && possibleCircuit ; i++ ) if ( level[i] == 0 ){
            possibleCircuit = 0;
            break;
        }
    }
    
    return possibleCircuit;
}

int main(){
    int node, road, i, u, v;
    
    while ( scanf("%d%d", &node, &road) == 2 ){
        CheckEulerCircuit checkEulerCircuit(node);
        
        for ( i = 0 ; i < road ; i++ ){
            scanf("%d%d", &u, &v);
            if ( u <node && v < node && u >= 0 && v >= 0 )
                checkEulerCircuit.addEdge(u, v);
        }
        
        printf("%s\n", checkEulerCircuit.checkEulerCircuitPossibility()?
            "Possible" : "Not Possible");
    }
    
    return 0;
}
/*
2 2
0 1
1 0
2 1
0 1
*/
