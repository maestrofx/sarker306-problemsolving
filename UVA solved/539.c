#include<stdio.h>

int edges[27][2];
int m, longestpath;

void backtrack(int *a, int index, int iamhere){
    int i, j=0, tobesearched[27], temp;
    
    for(i=0;i<m;i++) tobesearched[i]=1;
    for(i=0;i<index;i++) tobesearched[a[i]]=0;
    for(i=0;i<m;i++){
        if(tobesearched[i]){
            if(edges[i][0]==iamhere || edges[i][1]==iamhere){
                a[index]=i;
                j=1;
                temp=edges[i][1]+edges[i][0]-iamhere;
                backtrack(a, index+1, temp);
            }
        }
    }
    
    if(j==0){
        /*for(i=0;i<index;i++) printf("   (%d -> %d)\n", edges[a[i]][0], edges[a[i]][1]);
        puts("");*/
        longestpath=(longestpath>index)? longestpath:index;
    }
}

void find_the_longest_path(void){
    int available[27], i;
    
    for(i=0, longestpath=0;i<m;i++){
        available[0]=i;
        backtrack(available, 1, edges[i][1]);
        backtrack(available, 1, edges[i][0]);
    }
}

int main(){
    int n, i;
    
    while(scanf("%d%d", &n, &m)!=EOF){
        if(n==0 && m==0) break;
        
        for(i=0;i<m;i++) scanf("%d%d", &edges[i][0], &edges[i][1]);
        find_the_longest_path();
        printf("%d\n", longestpath);
    }
    
    return 0;
}
