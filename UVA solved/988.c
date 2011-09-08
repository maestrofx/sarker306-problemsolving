#include<stdio.h>

#define WHITE 'w'
#define GRAY 'g'
#define BLACK 'b'
#define MAXNODE 15002

int edges[MAXNODE][MAXNODE];
long ways[MAXNODE];
char color[MAXNODE], flag;
int degree[MAXNODE];
int node, blacked, whited, max;

int make_paths(){
    int i, v, j, num=0;
    
    for(i=0, ways[0]=1;i<node;i++){
        for(j=0;j<degree[i];j++){
            v=edges[i][j];
            
            ways[v]+=ways[i];
        }
        
        if(degree[i]==0) num+=ways[i];
    }
    
    return num;
}

int main(){
    int edge_num, x, y, i, j, k, test=0;
    
    while(scanf("%d", &node)!=EOF){
        for(i=0;i<=node;i++){
            color[i]=WHITE;
            degree[i]=0;
            ways[i]=0;
        }
        
        for(x=0;x<node;x++){
            scanf("%d", &edge_num);
            for(;edge_num;edge_num--){
                scanf("%d", &y);
                if(y>node || y<=0) continue;
                edges[x][degree[x]++]=y;
            }
        }
        
        if(test) printf("\n");
        test++;
        printf("%ld\n", make_paths());
    }
    
    return 0;
}
