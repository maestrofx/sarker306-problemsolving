#include<stdio.h>
#include<string.h>

int adj[28][28];
int color[28];
char list[30];
int InDictionary[30];
int listlen;

void reset(){
    int i, j;
    
    for(i=0;i<28;i++){
        for(j=0;j<28;j++){
            adj[i][j]=0;
        }
        color[i]=0;
        InDictionary[i]=0;
    }
    listlen=0;
}

void dfs(int u){
    int i;
    
    color[u]=1;
    for(i=1;i<28;i++){
        if(adj[u][i]){
            if(color[i]==0) dfs(i);
        }
    }
    color[u]=2;
    for(i=0;i<listlen;i++) if(list[i]==u+'A'-1) return;
    list[listlen++]=u+'A'-1;
}

int main(){
    char str1[25], str2[25], start;
    int i;
    
    strcpy(str2, "");
    while(scanf("%s", str1)!=EOF){
        if(str1[0]=='#'){
            for(i=1;i<27;i++) if(InDictionary[i]) dfs(i);
            list[listlen]=0;
            printf("%s\n", list);
            strcpy(str2, "");
            reset();
        }
        else{
            if(str2[0]){
                for(i=0; str1[i] && str2[i] && str1[i]==str2[i];i++);
                if(str1[i] && str2[i]){
                    adj[str1[i]-'A'+1][str2[i]-'A'+1]=1;
                    InDictionary[str1[i]-'A'+1]=1;
                }
            }
            else InDictionary[str1[0]-'A'+1]=1;
            
            strcpy(str2, str1);
        }
    }
    
    return 0;
}
