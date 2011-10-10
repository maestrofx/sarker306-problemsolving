#include <stdio.h>
#define SIZE 900005
#define SQRTSIZE 305

typedef struct eMod{
    long conVal, infoVal;
}eMod;

eMod queue[SIZE*2];
long head, tail, visited[SQRTSIZE][SQRTSIZE], dist[SQRTSIZE][SQRTSIZE];

long bfs(eMod *arr, long total, long des, long testCase){
    eMod u, v;
    long i;
    long x, y;
    
    head = tail = 0;
    visited[0][0] = testCase;
    u.conVal = 0, u.infoVal = 0;
    dist[0][0] = 0;
    queue[tail++] = u;
    while ( head != tail ){
        u = queue[head++];
        y = u.conVal * u.conVal + u.infoVal * u.infoVal;
        /*printf("%ld %ld %ld\n", u.conVal, u.infoVal, y);*/
        
        if ( y == des ) return dist[u.conVal][u.infoVal];
        for ( i = 0 ; i < total ; i++ ){
            v = u;
            v.conVal += arr[i].conVal;
            v.infoVal += arr[i].infoVal;
            x = v.conVal * v.conVal + v.infoVal * v.infoVal;
            if ( x <= des && visited[v.conVal][v.infoVal] != testCase ){
                dist[v.conVal][v.infoVal] = dist[u.conVal][u.infoVal] + 1;
                queue[tail++] = v;
                visited[v.conVal][v.infoVal] = testCase;
            }
        }
    }
    
    return -1;
}

int main(){
    eMod coins[50];
    long S, test, totlCoin, i, kase;
    
    while( scanf("%ld", &test) != EOF ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%ld", &totlCoin, &S);
            for ( i = 0 ; i < totlCoin ; i++ )
                scanf("%lld%ld", &coins[i].conVal, &coins[i].infoVal);
            
            i = bfs(coins, totlCoin, S*S, kase);
            ( i != -1 ) ? printf("%ld\n", i) : puts("not possible");
        }
        
        break;
    }
    
    return 0;
}
