#include<cstdio>
#include<vector>
#include<queue>
#include<list>
#define SIZE 505
#define INF 1<<30

using namespace std;

typedef struct{
    long v, w;
}pos;

vector< list<pos> >array(SIZE);
vector< list<pos> >arrayRev(SIZE);
vector< long> dis(SIZE), parent(SIZE);

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

void printArray(long N){
    list<pos>::iterator q;
    long i;
    
    puts("Original graph");
    for(i=0; i<N;i++){
        printf("%ld :", i);
        for(q=array[i].begin();q!=array[i].end();q++) printf(" %ld", q->v);
        printf("\n");
    }
    
    puts("Reverse graph");
    for(i=0; i<N;i++){
        printf("%ld :", i);
        for(q=arrayRev[i].begin();q!=arrayRev[i].end();q++) printf(" %ld", q->v);
        printf("\n");
    }
}

void initialize(long N, long S){
    long i;
    
    for(i=0;i<N;i++) dis[i]=INF, parent[i] = -INF;
    dis[S]=0;
}   

int relax(long u, long v, long w){
    int flag=0;
    
    if(dis[v]>dis[u]+w) dis[v]=dis[u]+w, flag=1;
    return flag;
}

void deleteEdge(long v){
    list<pos>::iterator q1, q2;
    long u, w;
    
    for ( q1 = arrayRev[v].begin() ; q1 != arrayRev[v].end() ; q1++ ){
        if ( dis[u=q1->v] + (w=q1->w) == dis[v] ){
            q1 = arrayRev[v].erase(q1);
            q1--;
            deleteEdge(u);
            for ( q2 = array[u].begin() ; q2 != array[u].end() ; q2++ ){
                if ( q2->v == v ){
                    q2 = array[u].erase(q2);
                    q2--;
                }
            }
        }
    }
}

void printPath(long v, long start){
    if ( v == start ) printf("%d\n", v);
    else if ( parent[v] == -INF ) printf("No path!\n");
    else{
        printf("%d <- ", v);
        printPath(parent[v], start);
    }
}

long dijkstra(long N, long S, long T){
    long u, v, i;
    priority_queue<long, vector<long>, comp>queue;
    list<pos>::iterator q;
    
    queue.push(S);
    initialize(N, S);
    while(!queue.empty()){
        u=queue.top();
        //printf("     %ld - %ld\n", u, dis[u]);
        queue.pop();
        for(q = array[u].begin(); q != array[u].end() ; q++ ){
            if( relax( u, q->v , q->w )){
                parent[q->v] = u;
                queue.push(q->v);
            }
        }
    }
    
    return dis[T];
}

int main(){
    long N, M, i, test, ii, u, v, w, S, T;
    
    while(scanf("%ld%ld", &N, &M)!=EOF){
        if ( N == 0 && M == 0 ) break;
        scanf("%ld%ld", &S, &T);
        for(i=0;i<N;i++){
            list<pos> temp;
            array[i]=temp;
            list<pos> temp1;
            arrayRev[i] = temp1;
        }
        
        for(i=0;i<M;i++){
            scanf("%ld%ld%ld", &u, &v, &w);
            pos hmm, hmm1;
            hmm.v=v, hmm.w=w;
            array[u].push_back(hmm);
            hmm1.v=u, hmm1.w=w;
            arrayRev[v].push_back(hmm1);
        }
        
        //printArray(N);
        u=dijkstra(N, S, T);
        deleteEdge(T);
        u=dijkstra(N, S, T);
        if(u==INF) printf("-1\n");
        else printf("%ld\n", u);
        for(i=0;i<N;i++) array[i].clear(), arrayRev[i].clear();
        //array.clear();
    }
    
    return 0;
}
