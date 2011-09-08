#include<cstdio>
#include<iostream>
#include<queue>
#include<map>
#include<list>
#include<string>
#include<cstring>
#define SIZE 4005
#define INF 1<<30

struct edge{
    int v, cost;
    char ch;
};

using namespace std;
int n, start, end;
int dist[SIZE][26];
list<edge>adj[SIZE];
map<string, int>lang;

int insert(string &str){
    map<string, int>::iterator ptr=lang.find(str);
    int x;

    if(ptr==lang.end()){
        lang.insert(pair<string, int>(str, n));
        x=n++;
    }
    else x=ptr->second;

    return x;
}

void init(){
    int i, j;

    for(i=0;i<SIZE;i++){
        adj[i].clear();
        for(j=0;j<26;j++) dist[i][j]=INF;
    }

    lang.clear();
    n=0;
}

void show(){
    map<string, int>::iterator ptr;
    list<edge>::iterator lptr;

    puts("");
    for(ptr=lang.begin();ptr!=lang.end();ptr++) cout<<ptr->first<<' '<<ptr->second<<'\n';
    puts("");
    for(int i=0;i<n;i++){
        printf("%d :", i);
        for(lptr=adj[i].begin();lptr!=adj[i].end();lptr++)
            cout<<" ("<<lptr->v<<' '<<lptr->ch<<' '<<lptr->cost<<')';
        puts("");
    }

    puts("");
}

struct pos{
    int node;
    char ch;
};

class cmp{
public:
    bool operator()(const pos &x, const pos &y){ return dist[x.node][x.ch-'a']>dist[y.node][y.ch-'a']; }
};

char relax(pos &from, pos &to, int cost){
    char flag=0;
    if(dist[from.node][from.ch-'a']+cost<dist[to.node][to.ch-'a'])
        dist[to.node][to.ch-'a']=dist[from.node][from.ch-'a']+cost, flag=1;
    return flag;
}

int dijkstra(){
    priority_queue<pos, vector<pos>, cmp>queue;
    list<edge>::iterator lptr;
    int result=-1;

    for(lptr=adj[start].begin();lptr!=adj[start].end();lptr++){
        pos start_pos;

        start_pos.ch=lptr->ch;
        start_pos.node=lptr->v;
        if(dist[start_pos.node][start_pos.ch-'a']>lptr->cost){
            dist[start_pos.node][start_pos.ch-'a']=lptr->cost;
            queue.push(start_pos);
           // cout<<"("<<start_pos.node<<','<<start_pos.ch<<','<<lptr->cost<<") ";
        }
    }

   // cout<<"inserted\n";

    while(queue.empty()==false){
        pos u=queue.top();

        //cout<<u.node<<','<<u.ch<<','<<dist[u.node][u.ch-'a']<<" :";
        if(u.node==end){
            result= dist[end][u.ch-'a'];
      //      puts("");
            break;
        }
        if(result==-1) for(lptr=adj[u.node].begin();lptr!=adj[u.node].end();lptr++){
            if(lptr->ch!=u.ch){
                pos v;
                v.ch=lptr->ch, v.node=lptr->v;

                if(relax(u, v,lptr->cost)){
                    queue.push(v);
                    //cout<<" ("<<v.node<<','<<v.ch<<','<<dist[v.node][v.ch-'a']<<')';
                }
            }
        }

        //puts("");
        queue.pop();
    }

    return result;
}

int main(){
    int m, u, v, result;
    char word[55];

    while(scanf("%d", &m)!=EOF && m>0){
        init();
        string s1, s2;
        cin>>s1>>s2;
        start=insert(s1);
        end=insert(s2);

        while(m--){
            string su, sv;
            cin>>su>>sv;
            u=insert(su), v=insert(sv);
            scanf("%s", word);
            edge tmp;
            tmp.ch=word[0], tmp.v=v, tmp.cost=strlen(word);
            adj[u].insert(adj[u].begin(), tmp);
            tmp.v=u;
            adj[v].insert(adj[v].begin(), tmp);
        }

        //show();
        result=dijkstra();
        if(result==-1) puts("impossivel");
        else printf("%d\n", result);
    }

    return 0;
}
