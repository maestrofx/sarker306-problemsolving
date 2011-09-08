#include<stdio.h>
#include<queue>
#include<list>
#define ELEVATOR 6
#define FLOOR 101
#define INF 1<<29

using namespace std;

int totaltime[ELEVATOR][FLOOR];
int interval[ELEVATOR];
int floors[ELEVATOR][FLOOR];

struct pos{
    int elev, u, cost;
};
list<pos>adj[ELEVATOR][FLOOR];

struct cmp{
    bool operator()(const pos &a, const pos &b){
        return totaltime[a.elev][a.u]>totaltime[b.elev][b.u];
    }
};

void init(int n, int k){
    int i, j;

    for(i=0;i<n;i++){
        interval[i]=INF;
        for(j=0;j<FLOOR;j++) totaltime[i][j]=INF, floors[i][j]=0;
    }
}

int relax(int el1, int fl1, int el2, int fl2, int w){
    if(totaltime[el2][fl2]>totaltime[el1][fl1]+w){
        totaltime[el2][fl2]=totaltime[el1][fl1]+w;
        return 1;
    }

    return 0;
}

int dijkstra(int n, int k){
    pos u;
    int i;
    priority_queue<pos, vector<pos>, cmp>queue;
    list<pos>::iterator next;

    for(i=0;i<n;i++){
        if(floors[i][0]==1){
            pos start;
            start.elev=i, start.u=0;
            totaltime[i][0]=0;
            queue.push(start);
        }
    }

    while(queue.empty()==false){
        u=queue.top();

       // printf("Elevator %d, Floor %d, Cost %d :", u.elev, u.u, totaltime[u.elev][u.u]);
        if(u.u==k) return totaltime[u.elev][u.u];
        for(next=adj[u.elev][u.u].begin();next!=adj[u.elev][u.u].end();next++){
            if(relax(u.elev, u.u, next->elev, next->u, next->cost)){
                pos v;
                v.elev=next->elev, v.u=next->u, v.cost=next->cost;
               // printf("   %d,%d,%d", v.elev, v.u, v.cost);
                queue.push(v);
            }
        }

       // puts("");
        queue.pop();
    }

    return -1;
}

int main(){
    int n, k, i, j, a;

    while(scanf("%d%d", &n, &k)!=EOF){
        init(n, k);

        for(i=0;i<n;i++) scanf("%d", &interval[i]);
        for(i=0;i<n;i++){
            do{
                scanf("%d", &a);
                floors[i][a]=1;
            }while(getchar()!='\n');
        }

        for(i=0;i<n;i++){
            for(j=0, a=-1;j<FLOOR;j++){
                if(floors[i][j]==0) continue;
                if(a!=-1){
                    pos hmm;
                    hmm.elev=i, hmm.u=a, hmm.cost=(j-a)*interval[i];
                    adj[i][j].push_back(hmm);
                    //printf("Floor %d -> Elevator %d, Floor %d\n", j,i,a);
                    pos hmm1;
                    hmm1.elev=i, hmm1.u=j, hmm1.cost=(j-a)*interval[i];
                    adj[i][a].push_back(hmm1);
                   // printf("Floor %d -> Elevator %d, Floor %d\n", a, i, j);
                }

                a=j;
            }
        }

        for(j=0;j<FLOOR;j++){
            for(i=0;i<n;i++){
                if(floors[i][j]==0) continue;
                for(a=0;a<n;a++){
                    if(floors[a][j]==0 || a==i) continue;
                    pos hmm;
                    hmm.elev=a, hmm.u=j, hmm.cost=60;
                    adj[i][j].push_back(hmm);
                    //printf("Elevator %d, Floor %d -> Elevator %d\n", i, j, a);
                    pos hmm1;
                    hmm1.elev=i, hmm1.u=j, hmm1.cost=60;
                    adj[a][j].push_back(hmm1);
                }

                a=i;
            }
        }

        k=dijkstra(n, k);

        if(k==-1) puts("IMPOSSIBLE");
        else printf("%d\n", k);
        for(i=0;i<FLOOR;i++)
            for(j=0;j<n;j++) adj[j][i].clear();
    }

    return 0;
}
