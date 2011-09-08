#include<stdio.h>
#define MAXPOINT 27

int parent[MAXPOINT];
int rank[MAXPOINT];
int nodes;

void init(long N){
	long i;
	for(i=0;i<=N;i++) parent[i]=i, rank[i]=0;
}

int find(int x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

void link(int x,int y){
    if(rank[x]>rank[y]) parent[y]=x;
    else{
		if(rank[x]==rank[y]) rank[y]++;
		parent[x]=y;
    }
}

void input(void){
    char a[5];
    int x, y;
    
    scanf("%s", a);
    nodes=a[0]-'A'+1;
    getchar();
    init(nodes);
    while(gets(a)){
        if(a[0]==0) break;
        x=find(a[0]-'A'+1), y=find(a[1]-'A'+1);
        if(x!=y) link(x, y);
    }
}

void output(void){
    int counter=0, i;
    
    for(i=1;i<=nodes;i++) if (i==parent[i]) counter++;
    printf("%d\n", counter);
}

int main(){
    int test, i;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            input();
            output();
            if(test) puts("");
        }
    }
    
    return 0;
}
