#include<stdio.h>
#define MAXPOINT 500001

long parent[MAXPOINT];
long rank[MAXPOINT];
long nodes, edges;

void init(long N){
	long i;
	for(i=0;i<=N;i++) parent[i]=i, rank[i]=0;
}

long find(long x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

void link(long x,long y){
    if(rank[x]>rank[y]) parent[y]=x;
    else{
		if(rank[x]==rank[y]) rank[y]++;
		parent[x]=y;
    }
}

int input(void){
    long x, y, i, a, b;
    
    if(scanf("%ld%ld", &nodes, &edges)==EOF) return 0;
    if(!nodes && !edges) return 0;
    init(nodes);
    for(i=0;i<edges;i++){
        scanf("%ld%ld", &x, &y);
        a=find(x), b=find(y);
        if(a!=b) link(a, b);
    }
    
    return 1;
}

void output(void){
    long counter=0, i;
    
    for(i=1;i<=nodes;i++) if (i==parent[i]) counter++;
    printf("%ld\n", counter);
}

int main(){
    int test=1, i;
    
    while(input()) {
        printf("Case %d: ", test++);
        output();
    }
    
    return 0;
}
