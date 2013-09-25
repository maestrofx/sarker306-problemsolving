#include <stdio.h>
#define SIZE 1024001

long val[(SIZE+2)<<2];
char update[(SIZE+2)<<2];
char array[SIZE];

void initTree( long index, long left, long right ){
    long mid = ( left + right )>>1;
    long lc = 1 + (index<<1), rc = (1 + index)<<1;
    
    update[index] = 0;
    if ( left == right ){
        if ( array[left] == 0 ) val[index] = 0;
        else val[index] = 1;
        return;
    }
    
    initTree( lc, left, mid );
    initTree( rc, mid + 1, right );
    val[index] = val[lc] + val[rc];
}

long x, y;

void Update( long index, long left, long right, char ud ){
    long mid = ( left + right )>>1;
    long lc = 1 + (index<<1), rc = (1 + index)<<1;
    
    if ( update[index] == 'F' ){
        val[index] = right - left + 1;
        
        if ( left != right )
            update[rc] = update[lc] = 'F';
    }
    else if ( update[index] == 'E' ){
        val[index] = 0;
        
        if ( left != right )
            update[rc] = update[lc] = 'E';
    }
    else if ( update[index] == 'I' ){
        val[index] = right - left + 1 - val[index];
        
        if ( left != right ){
            if ( update[rc] == 'F' ) update[rc] = 'E';
            else if ( update[rc] == 'E' ) update[rc] = 'F';
            else update[rc] ^= 'I';
            if ( update[lc] == 'F' ) update[lc] = 'E';
            else if ( update[lc] == 'E' ) update[lc] = 'F';
            else update[lc] ^= 'I';
        }
    }
    
    update[index] = 0;
    
    if ( left > y || right < x ) return;
    
    if ( left >= x && right <= y ){
        if ( ud == 'F' ){
            val[index] = right - left + 1;
            
            if ( left != right )
                update[rc] = update[lc] = 'F';
        }
        else if ( ud == 'E' ){
            val[index] = 0;
            
            if ( left != right )
                update[rc] = update[lc] = 'E';
        }
        else if ( ud == 'I' ){
            val[index] = right - left + 1 - val[index];
            
            if ( left != right ){
                if ( update[rc] == 'F' ) update[rc] = 'E';
                else if ( update[rc] == 'E' ) update[rc] = 'F';
                else update[rc] ^= 'I';
                if ( update[lc] == 'F' ) update[lc] = 'E';
                else if ( update[lc] == 'E' ) update[lc] = 'F';
                else update[lc] ^= 'I';
            }
        }
        
        return;
    }
    
    Update( lc, left, mid, ud );
    Update( rc, mid + 1, right, ud );
    val[index] = val[lc] + val[rc];
}

long Query( long index, long left, long right ){
    long mid = ( left + right )>>1;
    long lc = 1 + (index<<1), rc = (1 + index)<<1;
    
    if ( update[index] == 'F' ){
        val[index] = right - left + 1;
        
        if ( left != right )
            update[rc] = update[lc] = 'F';
    }
    else if ( update[index] == 'E' ){
        val[index] = 0;
        
        if ( left != right )
            update[rc] = update[lc] = 'E';
    }
    else if ( update[index] == 'I' ){
        val[index] = right - left + 1 - val[index];
        
        if ( left != right ){
            if ( update[rc] == 'F' ) update[rc] = 'E';
            else if ( update[rc] == 'E' ) update[rc] = 'F';
            else update[rc] ^= 'I';
            if ( update[lc] == 'F' ) update[lc] = 'E';
            else if ( update[lc] == 'E' ) update[lc] = 'F';
            else update[lc] ^= 'I';
        }
    }
    
    update[index] = 0;
    
    if ( left > y || right < x ) return 0;
    if ( left >= x && right <= y ) return val[index];
    
    return Query( lc, left, mid ) + Query( rc, mid + 1, right );
}

int main(){
    int test, kase, ptrns, num;
    char pattern[55], command[2];
    long n, queries, i;
    
    while ( scanf("%d", &test) != EOF ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            printf("Case %d:\n", kase);
            n = 0;
            scanf("%d", &ptrns);
            while ( ptrns-- ){
                scanf("%d", &num);
                scanf("%s", pattern);
                while ( num-- ){
                    for ( i = 0 ; pattern[i] ; i++, n++ )
                        array[n] = pattern[i] - '0';
                }
            }
            
            initTree( 0, 0, n - 1 );
            
            scanf("%ld", &queries);
            i = 1;
            while ( queries-- ){
                scanf("%s%ld%ld", command, &x, &y);
                if ( command[0] == 'S' ) printf("Q%d: %ld\n", i++, Query( 0, 0, n-1 ));
                else Update( 0, 0, n-1, command[0]);
            }
        }
    }
    
    return 0;
}
