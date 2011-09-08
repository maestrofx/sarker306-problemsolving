#include <stdio.h>

unsigned queue[1<<13], head, tail, min;
char color[1<<13];

int convert(char *str){
    unsigned x = 0, i;
    
    for ( i = 0 ; str[i] != 0 ; i++ )
        x = (x<<1) + ( str[i] == 'o' ? 1 : 0 );
    
    return x;
}

void printState(int x){
    int i = 1 << 11;
    
    while( i ){
        if( x & i ) putchar('1');
        else putchar('0');
        i >>= 1;
    }
}

int countOne(int x){
    int n = 0;
    
    while( x ) x &= x - 1, n++;
    return n;
}

void init(){
    int i, k = 1 << 12;
    for( i = 0 ; i < k ; i++ ) color[i] = 13;
    head = tail = 0;
    min = 13;
}

void doMove(int musk, int u){
    unsigned i, v, x = 7, y = (1 << 12) - 1; /* 111 */
    
    for ( i = 0; i < 10 ; i++ ){
       /* printState(u);
        putchar(' ');
        printState(x);
        putchar(' ');
        printState(u & x);
        putchar(' ');
        printState(musk);
        puts("");*/
        if( (u & x) == musk){
            v = u ^ x ;
            /*printState(u);
            printf(" ^ ");
            printState(musk);
            printf(" -> ");
            printState(v);
            puts("");*/
            if( color[v] == 13 ){
                color[v] = countOne(v), queue[tail++] = v;
               /* printf(" %d -> %d\n", u, v);*/
            }
        }
        
        musk = musk << 1;
        x = x << 1;
    }
}

void bfs(int start){
    int u, musk;
    
    queue[tail++] = start;
    color[start] = countOne(start);
    
    while( head != tail ){
        u = queue[head++];
        if( min > color[u] ) min = color[u];
        
        musk = 6; /* 110 */
       /* printState(musk);
        puts("");*/
        doMove(musk, u);
        musk = 3; /* 011 */
        doMove(musk, u);
    }
}

int main(){
    int test, x;
    char str[14];
    
    while(scanf("%d", &test) == 1){
        while(test--){
            scanf("%s", str);
            x = convert(str);
            init();
            bfs(x);
            printf("%d\n", min);
        }
    }
    
    return 0;
}
