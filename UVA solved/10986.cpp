#include<cstdio>
#include<vector>
#include<queue>
#define SIZE 20005
#define INF 1<<30

using namespace std;

typedef struct{
    long v, w;
}pos;

vector< vector<pos> >array(SIZE);
vector< long> dis(SIZE);

class comp{
public:
    comp(){
    }
    bool operator()(long &x, long &y){
        return dis[x]>dis[y];
    }
    ~comp(){
    }
};

void print_array(long N){
    vector<pos>::iterator q;
    long i;
    
    for(i=0; i<N;i++){
        printf("%ld :", i);
        for(q=array[i].begin();q!=array[i].end();q++) printf(" %ld", q->v);
        printf("\n");
    }
}

void initialize(long N, long S){
    long i;
    
    for(i=0;i<N;i++) dis[i]=INF;
    dis[S]=0;
}   

int relax(long u, long v, long w){
    int flag=0;
    
    if(dis[v]>dis[u]+w) dis[v]=dis[u]+w, flag=1;
    return flag;
}

long dijkstra(long N, long S, long T){
    long u, v, i;
    priority_queue<long, vector<long>, comp>queue;
    
    queue.push(S);
    initialize(N, S);
    while(!queue.empty()){
        u=queue.top();
        //printf("     %ld - %ld\n", u, dis[u]);
        if(u==T) break;
        for(i=0; i<array[u].size();i++){
            if( relax(u, array[u][i].v, array[u][i].w)) queue.push(array[u][i].v);
        }
        queue.pop();
    }
    
    while(!queue.empty()) queue.pop();
    return dis[T];
}

int main(){
    long N, M, i, test, ii, u, v, w, S, T;
    pos hmm;
    vector<pos> temp;
    
    while(scanf("%ld", &test)!=EOF){
        for(ii=1;ii<=test;ii++){
            scanf("%ld%ld%ld%ld", &N, &M, &S, &T);
            
            for(i=0;i<N;i++)  array[i]=temp;
            for(i=0;i<M;i++){
                scanf("%ld%ld%ld", &u, &v, &w);
                hmm.v=v, hmm.w=w;
                array[u].push_back(hmm);
                hmm.v=u,hmm.w=w;
                array[v].push_back(hmm);
            }
            
            printf("Case #%ld: ", ii);
            //print_array(N);
            u=dijkstra(N, S, T);
            if(u==INF) printf("unreachable\n");
            else printf("%ld\n", u);
            for(i=0;i<N;i++) array[i].clear();
            //array.clear();
        }
    }
    
    return 0;
}
