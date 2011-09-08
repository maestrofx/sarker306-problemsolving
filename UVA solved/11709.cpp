#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<stack>

#define WHITE 'w'
#define GRAY 'g'
#define BLACK 'b'
#define SIZE 1005

using namespace std;
map<string, int>names;
vector< list<int> >adj(SIZE);
stack<int>mystack;
int n;
int start[SIZE], low[SIZE], SCC[SIZE];
char color[SIZE], in_stack[SIZE];
int dfs_time, components;

void dfs(int u){
    int v;
    list<int>::iterator plist;
    
    low[u]=start[u]=++dfs_time;
    color[u]=GRAY;
    
    mystack.push(u);
    in_stack[u]=1;
    
    for(plist=adj[u].begin();plist!=adj[u].end();plist++){
        v=*plist;
        
        if(color[v]==WHITE){
            dfs(v);
            
            if(low[u]>low[v]) low[u]=low[v];
        }
        else if(in_stack[v]) if(low[u]>low[v]) low[u]=low[v];
    }
    
    if(low[u]==start[u]){
        components++;
        do{
            v=mystack.top();
            SCC[v]=components;
            
            mystack.pop();
            in_stack[v]=0;
        }while(v!=u);
    }
}

void dfs_visit(){
    int i;
    
    while(mystack.empty()==false) mystack.pop();
    for(i=0;i<n;i++) color[i]=WHITE, in_stack[i]=0, SCC[i]=-1;
    
    dfs_time = 0, components=-1;
    for(i=0;i<n;i++){
        if(color[i]==WHITE){
            dfs(i);
        }
    }
}

int main(){
    int m;
    int i;
    
    while(scanf("%d%d", &n, &m)!=EOF && (n || m)){
        getchar();
        for(i=0;i<n;i++){
            string str;
            getline(cin, str, '\n');
            names.insert(pair<string, int>(str, i));
            adj[i].clear();
        }
        
        string str1, str2;
        map<string, int>::iterator pmap1, pmap2;
        
        for(i=0;i<m;i++){
            getline(cin, str1, '\n');
            getline(cin, str2, '\n');
            
            pmap1=names.find(str1);
            pmap2=names.find(str2);
            
            if(pmap1!=names.end() && pmap2!=names.end()){
                adj[pmap1->second].push_back(pmap2->second);
            }
        }
        
        dfs_visit();
        
        printf("%d\n", components+1);
        
        names.clear();
    }
    
    return 0;
}
