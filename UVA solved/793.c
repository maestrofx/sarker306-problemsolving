#include<stdio.h>
#define MAXPOINT 1000000

long parent[MAXPOINT];
long rank[MAXPOINT];
long nodes;

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

int main(){
    long test, x, y, a, b, q_success=0, q_fail=0;
    char str[100], command[5];
    
    while(scanf("%ld", &test)!=EOF){
        while(test--){
            scanf("%ld", &nodes);
            gets(str);
            init(nodes);
            while(gets(str)){
                if(str[0]==0) break;
                sscanf(str, "%s%ld%ld", command, &x, &y);
                a=find(x), b=find(y);
                if(a!=b){
                    if(command[0]=='c') link(a, b);
                    else if(command[0]=='q') q_fail++;
                }
                else if(command[0]=='q') q_success++;
            }
            
            printf("%ld,%ld\n", q_success, q_fail);
            q_success=q_fail=0;
            if(test) puts("");
        }
    }
    
    return 0;
}
