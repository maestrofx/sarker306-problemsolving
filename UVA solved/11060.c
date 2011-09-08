#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<cstring>

std :: map<std::string,int>M;
std :: vector<std::string>V;
int deg[105],mat[105][105],vis[105];

int main(void){
    char str[130],str1[130];
    int cas,n,n1;
    register int t,t1,i;
    for(cas=1;scanf("%d",&n)==1;cas++){
        V.clear();
        M.clear();
        for(i^=i;i<n;i++){
            scanf("%s",str);
            V.push_back(str);
            M[str]=i;
        }
        memset(mat,0,sizeof(mat));
        memset(vis,0,sizeof(vis));
        memset(deg,0,sizeof(deg));
        for( i^=i , scanf("%d",&n1) ; i<n1 && scanf("%s%s",str,str1)==2 ; i++){
            t=M[str];
            t1=M[str1];
            if( (t^t1) && !mat[t][t1] )
            mat[t][t1]=1,deg[t1]++;
        }
        printf("Case #%d: Dilbert should drink beverages in this order:",cas);
        while(1){
            for(i^=i;i<n;i++) if(vis[i]==0 && deg[i]==0) break;
            if(i>=n) break;
            printf(" %s",V[i].c_str());
            vis[i]=1;
            for(t^=t;t<n;t++) if(mat[i][t]==1) mat[i][t]=0,deg[t]--;
        }
        printf(".\n\n");
    }
    return 0;
}
