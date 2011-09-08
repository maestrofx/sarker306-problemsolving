#include<stdio.h>
#define WHITE 3
#define GRAY 1
#define BLACK 2

long times[27], total_times[27];
typedef struct{
    int n;
    char adj[50];
}adjacency;

adjacency adj[27];
char top_sorted[30], color[27];
int top_sort_index;

void init(){
    int i;

    for(i=0;i<=26;i++) total_times[i]=times[i]=0, adj[i].n=0, color[i]=WHITE;
    top_sorted[0]=0;
    top_sort_index=0;
}

void add_edge(char u, char v){
    adj[u].adj[adj[u].n++]=v;
}

void parse_input(char *input){
    char v[50], u[50];
    long time;
    int i;

    u[0]=0;
    sscanf(input, "%s%ld%s", v, &time, u);

    for(i=0;u[i];i++){
        add_edge(u[i]-'A'+1, v[0]-'A'+1);
    }

    if(i==0) add_edge(0, v[0]-'A'+1);
    times[v[0]-'A'+1]=time;
}

void topological(char u){
    char v, i;

    color[u]=GRAY;

    for(i=0;i<adj[u].n;i++){
        v=adj[u].adj[i];

        if(color[v]==WHITE) topological(v);
    }

    color[u]=GRAY;
    top_sorted[top_sort_index++]=u;
}

long time_count(){
    int i, j, u, v;
    long max=0;

    topological(0);
    for(i=top_sort_index-1;i>=0;i--){
        u=top_sorted[i];
        for(j=0;j<adj[u].n;j++){
            v=adj[u].adj[j];
            if(total_times[v]<total_times[u]+times[v])
                total_times[v]=total_times[u]+times[v];
        }
    }

    for(i=0;i<=26;i++) if(max<total_times[i]) max=total_times[i];
    return max;
}

int main(){
    char input[100];
    int test;

    while(scanf("%d", &test)!=EOF){
        getchar();
        getchar();
        while(test--){
            init();

            while(gets(input)){
                if(input[0]==0) break;
                parse_input(input);
            }

            printf("%ld\n", time_count());
            if(test) puts("");
        }
    }

    return 0;
}
