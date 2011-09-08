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

long dijkstra(long N, long S){
    long u, v, i;
    priority_queue<long, vector<long>, comp>queue;
    
    queue.push(S);
    initialize(N, S);
    while(!queue.empty()){
        u=queue.top();
        //printf("     %ld - %ld\n", u, dis[u]);
        for(i=0; i<array[u].size();i++){
            if( relax(u, array[u][i].v, array[u][i].w)) queue.push(array[u][i].v);
        }
        queue.pop();
    }
    
    while(!queue.empty()) queue.pop();
    for(i=1, v=0;i<N;i++) v=(v>dis[i])? v:dis[i];
    
    return v;
}

int main(){
    long N, M, i, test, ii, u, v, w, S;
    pos hmm;
    vector<pos> temp;
    char str[30];
    
    while(scanf("%ld", &N)!=EOF){
        for(i=0;i<N;i++)  array[i]=temp;
        for(i=1;i<N;i++){
            for(ii=0;ii<i;ii++){
                scanf("%s", str);
                if(str[0]=='x') continue;
                sscanf(str, "%ld", &S);
                hmm.v=ii, hmm.w=S;
                array[i].push_back(hmm);
                hmm.v=i, hmm.w=S;
                array[ii].push_back(hmm);
            }
        }
        
        //print_array(N);
        u=dijkstra(N, 0);
        printf("%ld\n", u);
        for(i=0;i<N;i++) array[i].clear();
        //array.clear();
    }
    
    return 0;
}
