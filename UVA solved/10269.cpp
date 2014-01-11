#include<cstdio>
#include<vector>
#include<list>
#include<queue>
#define MAX 105
#define MAXBOOTUSE 11
#define MAXKMUSE 503
#define INF 1<<14

using namespace std;
typedef struct{
    int v, w;
}pos;

typedef struct State{
    int v, BootUsed, BootKm, BootWeared;
	State(int _v = 0, int _bU = 0, int _bK = 0, int _bW = 0) : v(_v), BootUsed(_bU), BootKm(_bK), BootWeared(_bW){}
}state;

vector< list<pos> >array(MAX);
int dis[MAX+2][MAXBOOTUSE+2][MAXKMUSE + 2][2];
State par[MAX + 2][MAXBOOTUSE + 2][MAXKMUSE + 2][2];
int L, K, A, B;

class Comp{
public:
    bool operator()(const state &x, const state &y){
        return dis[x.v][x.BootUsed][x.BootKm][x.BootWeared]>dis[y.v][y.BootUsed][y.BootKm][y.BootWeared];
    }
};

void initialize(void){
    int i, j, k, l, N=A+B;

    for(i=1;i<=N;i++)
        for(j=0;j<=K;j++)
            for(k=0;k<=L;k++)
				for(l=0;l<2;l++)
                	dis[i][j][k][l] =INF, par[i][j][k][l] = State(-1,-1,-1,-1);
    dis[N][0][0][0]=0;
}

int dijk(int N){
    priority_queue<State, vector<State>, Comp>queue;
    list< pos >::iterator pp;
    int minDist = INF;
    
    initialize();
    queue.push(state(N, 0, 0, 0));
    
    while ( queue.empty() == false ){
    	State u = queue.top();
    	State prev = par[u.v][u.BootUsed][u.BootKm][u.BootWeared];
    	queue.pop();
    	
    	//printf("%d %d %d %d -> %d ... par -> %d %d %d %d\n", u.v, u.BootUsed, u.BootKm, u.BootWeared, dis[u.v][u.BootUsed][u.BootKm][u.BootWeared],
		//	prev.v, prev.BootUsed, prev.BootKm, prev.BootWeared);
    	if ( u.v == 1 ){
			minDist = min( minDist, dis[u.v][u.BootUsed][u.BootKm][u.BootWeared]);
		}
    	
    	if ( u.BootUsed < K && u.BootWeared == 0 && u.BootKm == 0 ){ // at one Boot run from u to v
    		if (dis[u.v][u.BootUsed + 1][u.BootKm + L][0] > dis[u.v][u.BootUsed][u.BootKm][0]){
	    		dis[u.v][u.BootUsed + 1][u.BootKm + L][0] = dis[u.v][u.BootUsed][u.BootKm][0];
	    		par[u.v][u.BootUsed + 1][u.BootKm + L][0] = u;
	    		queue.push(State(u.v, u.BootUsed + 1, u.BootKm + L, 0));
	    	}
    	}
    	
    	if ( u.BootWeared == 1 && dis[u.v][u.BootUsed][0][0] > dis[u.v][u.BootUsed][u.BootKm][u.BootWeared]){
    		dis[u.v][u.BootUsed][0][0] = dis[u.v][u.BootUsed][u.BootKm][u.BootWeared];
    		par[u.v][u.BootUsed][0][0] = u;
    		queue.push(State(u.v, u.BootUsed, 0, 0));
    	}
    	
    	for ( pp = array[u.v].begin() ; pp != array[u.v].end() ; pp++ ){
			int v = pp->v, w = pp->w;
			
			if ( dis[v][u.BootUsed][0][0] > dis[u.v][u.BootUsed][u.BootKm][u.BootWeared] + w ){
				dis[v][u.BootUsed][0][0] = dis[u.v][u.BootUsed][u.BootKm][u.BootWeared] + w;
				par[v][u.BootUsed][0][0] = u;
				queue.push(State(v, u.BootUsed, 0, 0));
			}
			
			if ( u.BootWeared == 0 && w <= u.BootKm ){ // cannot stop superrun midway
				int remBootKm = ( u.BootKm >= w ) ?(u.BootKm - w) : 0;
				int stillWearing = remBootKm ? 1 : 0;
				
				if ( dis[v][u.BootUsed][remBootKm][stillWearing] > dis[u.v][u.BootUsed][u.BootKm][0] ){
					dis[v][u.BootUsed][remBootKm][stillWearing] = dis[u.v][u.BootUsed][u.BootKm][0];
					par[v][u.BootUsed][remBootKm][stillWearing] = u;
					queue.push(State(v, u.BootUsed, remBootKm, stillWearing));
				}
			}
			else{
				if ( u.v <= A && w <= u.BootKm){ // running THROUGH a village, cannot stop superrun midway
					int remBootKm = ( u.BootKm >= w ) ?(u.BootKm - w) : 0;
					int stillWearing = remBootKm ? 1 : 0;

					if ( dis[v][u.BootUsed][remBootKm][stillWearing] > dis[u.v][u.BootUsed][u.BootKm][1] ){
						dis[v][u.BootUsed][remBootKm][stillWearing] = dis[u.v][u.BootUsed][u.BootKm][1];
						par[v][u.BootUsed][remBootKm][stillWearing] = u;
						queue.push(State(v, u.BootUsed, remBootKm, stillWearing));
					}
				}
			}
		}
	}
	
	return minDist;
}

int main(){
    int test;
    int u, v, w, M, i;
    pos hmm;

    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d%d%d%d%d", &A, &B, &M, &L, &K);
            for(i=0;i<=A+B;i++)  array[i].clear();
            
            while(M--){
                scanf("%d%d%d", &u, &v, &w);
                hmm.v=v, hmm.w=w;
                array[u].push_back(hmm);
                hmm.v=u,hmm.w=w;
                array[v].push_back(hmm);
            }

            printf("%d\n", dijk(A+B));
        }
    }

    return 0;
}
