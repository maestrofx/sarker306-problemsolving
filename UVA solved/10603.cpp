#include<cstdio>
#include<queue>
#include<vector>
#define SIZE 203
#define INF 1<<30

using namespace std;

long pos_dist[SIZE][SIZE][SIZE];
long dist[SIZE];
long final_total, final_d;

struct pos{
    short a, b, c;
};

bool operator<(const pos &a, const pos &b){
    return pos_dist[a.a][a.b][a.c]>pos_dist[b.a][b.b][b.c];
}

void init(int a, int b, int c){
    int i, j, k;
    
    for(i=0;i<=a;i++){
        for(j=0;j<=b;j++)
            for(k=0;k<=c;k++)
                pos_dist[i][j][k]=INF;
    }
    
    for ( i = 0; i< SIZE ; i++ ) dist[i] = INF;
    final_d = final_total = 0;
    pos_dist[0][0][c]=0;
    dist[0]=dist[c]=0;
}

int relax(pos &u, pos &v, int cost){
    int flag=0;
    
    if(pos_dist[u.a][u.b][u.c]+cost<pos_dist[v.a][v.b][v.c]){
        flag=1;
        pos_dist[v.a][v.b][v.c]=pos_dist[u.a][u.b][u.c]+cost;
        if(dist[v.a]>pos_dist[v.a][v.b][v.c]) dist[v.a]=pos_dist[v.a][v.b][v.c];
        if(dist[v.b]>pos_dist[v.a][v.b][v.c]) dist[v.b]=pos_dist[v.a][v.b][v.c];
        if(dist[v.c]>pos_dist[v.a][v.b][v.c]) dist[v.c]=pos_dist[v.a][v.b][v.c];
    }
    
    return flag;
}

void dijkstra(int a, int b, int c, int d){
    priority_queue< pos, vector<pos> >queue;
    pos u, v;
    short x, y, z;
    
    init(a, b, c);
    pos s;
    s.a=0, s.b=0, s.c=c;
    queue.push(s);
    
    while(queue.empty()==false){
        pos u=queue.top();
        queue.pop();
        //printf("u : %d %d %d\n", u.a, u.b, u.c);
        if(u.a==d || u.b==d || u.c==d){
            final_d=d, final_total=dist[d];
            return;
        }
        pos v1;  /* b ->a */
        if(u.a+u.b>a){
            v1.a=a, v1.b=u.a+u.b-a, v1.c=u.c;
            if(relax(u, v1, a-u.a)) queue.push(v1);
        }
        else{
            v1.a=u.a+u.b, v1.b=0, v1.c=u.c;
            if(relax(u, v1, u.b)) queue.push(v1);
        }
        
        pos v2;  /* c -> a */
        if(u.a+u.c>a){
            v2.a=a, v2.c=u.a+u.c-a, v2.b=u.b;
            if(relax(u, v2, a-u.a)) queue.push(v2);
        }
        else{
            v2.a=u.a+u.c, v2.c=0, v2.b=u.b;
            if(relax(u, v2, u.c)) queue.push(v2);
        }
        
        pos v3;  /* b ->c */
        if(u.c+u.b>c){
            v3.c=c, v3.b=u.c+u.b-c, v3.a=u.a;
            if(relax(u, v3, c-u.c)) queue.push(v3);
        }
        else{
            v3.c=u.c+u.b, v3.b=0, v3.a=u.a;
            if(relax(u, v3, u.b)) queue.push(v3);
        }
        
        pos v4;  /* c -> b */
        if(u.b+u.c>b){
            v4.b=b, v4.c=u.b+u.c-b, v4.a=u.a;
            if(relax(u, v4, b-u.b)) queue.push(v4);
        }
        else{
            v4.b=u.b+u.c, v4.c=0, v4.a=u.a;
            if(relax(u, v4, u.c)) queue.push(v4);
        }
        
        pos v5;  /* a -> b */
        if(u.b+u.a>b){
            v5.b=b, v5.a=u.a+u.b-b, v5.c=u.c;
            if(relax(u, v5, b-u.b)) queue.push(v5);
        }
        else{
            v5.b=u.b+u.a, v5.a=0, v5.c=u.c;
            if(relax(u, v5, u.a)) queue.push(v5);
        }
        
        pos v6;  /* a -> c */
        if(u.c+u.a>c){
            v6.c=c, v6.a=u.a+u.c-c, v6.b=u.b;
            if(relax(u, v6, c-u.c)) queue.push(v6);
        }
        else{
            v6.c=u.c+u.a, v6.a=0, v6.b=u.b;
            if(relax(u, v6, u.a)) queue.push(v6);
        }
    }
    
    if ( d > c && d > b && d > a ){
        d = a;
        if ( b > d ) d = b;
        if ( c > d ) d = c;
    }
    for(int i=d; i>=0;i--){
        if(dist[i]!=INF){
            final_d=i;
            final_total=dist[i];
            return;
        }
    }
}

int main(){
    int test, a, b, c, d, x;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            final_total=final_d=-1;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            
            dijkstra(a, b, c, d);
            printf("%ld %d\n", final_total, final_d);
        }
        
        break;
    }
    
    return 0;
}
/* 5
197 19 199 162
97 199 96 62
2 12 22 15
2 12 22 25
197 198 199 196
*/
