#include <stdio.h>
#define SIZE 1000005
#define TREESZ 2700000
#define LONGLONGMAX ((~0LLU)>>1)
#define LONGLONGMIN (((~0LLU)>>1)+1)

long long minRng[TREESZ];
long long maxRng[TREESZ];
long long sumSqr[TREESZ];
long long sum[TREESZ];
char udType[TREESZ];
long long udVal[TREESZ];
long long array[SIZE + 2];

long long Mini( long long a, long long b ){
    return a > b ? b : a;
}

long long Maxi( long long a, long long b ){
    return a < b ? b : a;
}

void initTree( long index, long left, long right ){
    long lc = 1+(index<<1), rc = (1+index)<<1, mid = (left+right)>>1;
    
    udVal[index] = 0;
    udType[index] = 0;
    
    if ( left == right ){
        sum[index] = array[left];
        sumSqr[index] = array[left] * array[left];
        minRng[index] = maxRng[index] = array[left];
        /*printf("->(%ld, %ld)  %lld %lld\n", left, right, minRng[index], maxRng[index]);*/
        return;
    }
    
    initTree(lc, left, mid);
    initTree(rc, mid + 1, right);
    
    sum[index] = sum[lc] + sum[rc];
    sumSqr[index] = sumSqr[lc] + sumSqr[rc];
    minRng[index] = Mini ( minRng[lc], minRng[rc] );
    maxRng[index] = Maxi ( maxRng[lc], maxRng[rc] );
    /*printf("->(%ld, %ld)  %lld %lld\n", left, right, minRng[index], maxRng[index]);*/
}

long x, y;

void update( long index, long left, long right, char ud, long long val ){
    long lc = 1+(index<<1), rc = (1+index)<<1, mid = (left+right)>>1;
    
    if ( udType[index] ){
        /*printf("Pending update, %ld %ld, updateType %d\n", left, right, udType[index]);*/
        if ( udType[index] == 1 ){
            sum[index] = ( right - left + 1 ) * udVal[index];
            sumSqr[index] = sum[index] * udVal[index];
            minRng[index] = maxRng[index] = udVal[index];
            
            if ( left != right ){
                udType[lc] = udType[rc] = 1;
                udVal[lc] = udVal[rc] = udVal[index];
            }
        }
        else {
            sumSqr[index] += udVal[index] * ( 2 * sum[index] + udVal[index] * ( right - left + 1 ));
            sum[index] += (right - left + 1) * udVal[index];
            minRng[index] += udVal[index];
            maxRng[index] += udVal[index];
            
            if ( left != right ){
                if ( udType[lc] == 1 ){
                    /*printf("Left child of %d %d has pending update 1\n", left, right);*/
                    update(lc, left, mid, 0, 0);
                }
                
                udType[lc] = 2;
                udVal[lc] += udVal[index];
                if ( udType[rc] == 1 ){
                    /*printf("Right child of %d %d has pending update 1\n", left, right);*/
                    update(rc, mid + 1, right, 0, 0);
                }
                
                udType[rc] = 2;
                udVal[rc] += udVal[index];
            }
        }
        
        udType[index] = 0;
        udVal[index] = 0;
    }
    
    if ( left > y || right < x ) return ;
    
    if ( left >= x && right <= y ){
        if ( ud ){
            if ( ud == 1 ){
                sum[index] = ( right - left + 1 ) * val;
                sumSqr[index] = sum[index] * val;
                minRng[index] = val;
                maxRng[index] = val;
                
                if ( left != right ){
                    udType[lc] = udType[rc] = 1;
                    udVal[lc] = udVal[rc] = val;
                }
            }
            else {
                sumSqr[index] += val * ( 2 * sum[index] + val * ( right - left + 1 ));
                sum[index] += (right - left + 1) * val;
                minRng[index] += val;
                maxRng[index] += val;
                
                if ( left != right ){
                    if ( udType[lc] == 1 ){
                        update(lc, left, mid, 0, 0);
                    }
                    
                    udType[lc] = 2;
                    udVal[lc] += val;
                    if ( udType[rc] == 1 ){
                        update(rc, mid + 1, right, 0, 0);
                    }
                    
                    udType[rc] = 2;
                    udVal[rc] += val;
                }
            }
        }
        
        /*printf("->(%ld, %ld)  %lld %lld, updatetype %d\n", left, right, sumSqr[index], sum[index], ud);*/
        return;
    }
    
    update( lc, left, mid, ud, val );
    update( rc, mid + 1, right, ud, val );
    sum[index] = sum[lc] + sum[rc];
    sumSqr[index] = sumSqr[lc] + sumSqr[rc];
    minRng[index] = Mini(minRng[lc], minRng[rc]);
    maxRng[index] = Maxi(maxRng[lc], maxRng[rc]);
    /*printf("->(%ld, %ld)  %lld %lld\n", left, right, sumSqr[index], sum[index]);*/
}

void query( long index, long left, long right, long long *res ){
    long lc = 1+(index<<1), rc = (1+index)<<1, mid = (left+right)>>1;
    
    if ( udType[index] ){
        if ( udType[index] == 1 ){
            sum[index] = ( right - left + 1 ) * udVal[index];
            sumSqr[index] = sum[index] * udVal[index];
            minRng[index] = udVal[index];
            maxRng[index] = udVal[index];
            
            if ( left != right ){
                udType[lc] = udType[rc] = 1;
                udVal[lc] = udVal[rc] = udVal[index];
            }
        }
        else {
            sumSqr[index] += udVal[index] * ( 2 * sum[index] + udVal[index] * ( right - left + 1 ));
            sum[index] += (right - left + 1) * udVal[index];
            minRng[index] += udVal[index];
            maxRng[index] += udVal[index];
            
            if ( left != right ){
                if ( udType[lc] == 1 ){
                    update(lc, left, mid, 0, 0);
                }
                
                udType[lc] = 2;
                udVal[lc] += udVal[index];
                if ( udType[rc] == 1 ){
                    update(rc, mid + 1, right, 0, 0);
                }
                
                udType[rc] = 2;
                udVal[rc] += udVal[index];
            }
        }
        
        udType[index] = 0;
        udVal[index] = 0;
    }
    
    if ( left > y || right < x ) return ;
    if ( left >= x && right <= y ){
        res[0] += sum[index];
        res[1] += sumSqr[index];
        if ( res[2] > minRng[index] ) res[2] = minRng[index];
        if ( res[3] < maxRng[index] ) res[3] = maxRng[index];
        /*printf("->(%ld, %ld)  %lld %lld\n", left, right, res[0], res[1]);*/
        return;
    }
    
    query( lc, left, mid, res );
    query( rc, mid + 1, right, res );
    /*printf("->(%ld, %ld)  %lld %lld\n", left, right, res[0], res[1]);*/
}

void rawUpdate( int command , long long val ){
    long i;
    
    if ( command == 1 )
    for ( i = x ; i <= y; i++ ) array[i] = val;
    else
    for ( i = x ; i <= y ; i++ ) array[i] += val;
}

void rawQuery ( long long *res ) {
    long i;
    
    res[0] = res[1] = 0;
    res[2] = (~0LLU)>>1, res[3] = ((~0LLU)>>1)+1;
    
    for ( i = x ; i <= y ; i++ ){
        res[0] += array[i], res[1] += array[i]*array[i];
        if ( res[2] > array[i] ) res[2] = array[i];
        if ( res[3] < array[i] ) res[3] = array[i];
    }
}

long long gcd( long long m, long long n ){
    long long tmp;
        
    while ( n ){
        tmp = m;
        m = n;
        n = tmp%n;
    }
    
    return m;
}

int main(){
    int test, kase, command;
    long n, q, i;
    long long res[4];
    unsigned long long a, b;
    long long val;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%ld", &n, &q);
            
            for ( i = 1 ; i <= n ; i++ ){
                array[i] = i;
               /* scanf("%lld", &array[i]);*/
            }
            initTree( 0, 1, n );
            
            printf("Case %d:\n", kase);
            while ( q-- ){
                scanf("%d%ld%ld", &command, &x, &y);
                command++;
                
                if ( command == 3 ){
                    #ifndef ONLINE_JUDGE
                    rawQuery( res);
                    printf("From brute force : %lld %lld %lld %lld\n", res[1], res[0], res[2], res[3]);
                    #endif
                    res[0] = res[1] = 0;
                    res[2] = (~0LLU)>>1, res[3] = ((~0LLU)>>1)+1;
                    query( 0, 1, n, res);
                    y -= x - 1;
                    a = y * res[1] - res[0] * res[0];
                    b = y;
                    b *= y;
                    val = gcd(a, b);
                    #ifndef ONLINE_JUDGE
                    printf("From st, %lld %lld %lld %lld\n", res[1], res[0], res[2], res[3]);
                    #endif
                    printf("%llu/%llu %lld\n", a/val, b/val, res[3] - res[2]);
                }
                else{
                    scanf("%lld", &val);
                    update( 0, 1, n, command, val );
                    #ifndef ONLINE_JUDGE
                    rawUpdate( command, val );
                    #endif
                }
            }
        }
    }
    
    return 0;
}
