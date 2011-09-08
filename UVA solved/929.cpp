#include<cstdio>
#include<queue>
#include<vector>

#define INF 2147483647
#define MAX 1002

using namespace std;
long grid[MAX][MAX];
long dis[MAX][MAX];
typedef struct{
    int i, j;
}pos;

int xdir[]={1,0,0,-1};
int ydir[]={0,1,-1,0};

class comp{
public:
    comp(){
    }
    bool operator()(pos &x, pos &y){
        return dis[x.i][x.j]>dis[y.i][y.j];
    }
    ~comp(){
    }
};

void initialize(int N, int M){
    int i, j;
    
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            dis[i][j]=INF;

    dis[0][0]=grid[0][0];
}   

int relax(int a, int b, int c, int d){
    int flag=0;
    
    if(dis[c][d]>dis[a][b]+grid[c][d]) dis[c][d]=dis[a][b]+grid[c][d], flag=1;
    return flag;
}

long dijkstra(int N, int M){
    int i;
    pos hmm, u, v;
    priority_queue<pos, vector<pos>, comp>queue;
    
    hmm.i=0, hmm.j=0;
    queue.push(hmm);
    initialize(N, M);
    while(!queue.empty()){
        u=queue.top();
        if(u.i==N-1 && u.j==M-1) break;
        for(i=0; i<4;i++){
            v.i=u.i+xdir[i], v.j=u.j+ydir[i];
            if(v.i>=0 && v.i<N && v.j>=0 && v.j<M){
                if(relax(u.i, u.j, v.i, v.j)) queue.push(v);
            }
        }
        queue.pop();
    }
    
    while(!queue.empty()) queue.pop();
    return dis[N-1][M-1];
}

int main(){
    long N, M, i, j, test, ii, u, v, w, S, T;
    
    while(scanf("%ld", &test)!=EOF){
        while(test--){
            scanf("%ld%ld", &N, &M);
            
            for(i=0;i<N;i++){
                for(j=0;j<M;j++){
                    scanf("%ld", &grid[i][j]);
                }
            }
            
            u=dijkstra(N, M);
            printf("%ld\n", u);
        }
    }
    
    return 0;
}
