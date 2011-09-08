#include <stdio.h>
#include <math.h>

/*long arr[10001][5];

int main(){
    long i, j, x, y;
    char k;
    
    for ( i = 1 ; i <= 100 ; i++ ){
        arr[ y = i * i ][1]++;
        for ( j = 1 ;  ; j++ ){
            x = j + y ;
            if ( x >= 10001 ) break;
            for ( k = 0 ; k < 4 ; k++ )
                arr[x][k + 1] += arr[j][k];
        }
    }
    
    while( scanf("%ld", &y) != EOF ){
        while(y--){
            scanf("%d", &x);
            for( k = 0 ;  arr[x][k] == 0 && k < 5 ; k++ ) ;
            printf("%ld\n", k);
        }
    }
    
    return 0;
}
*/

int arr[10001];

int main(){
    int i, j, x;
    
    for( i = 1 ; i < 100 ; i++ )
        for( j = i, x = i * i ; x + j*j < 10001 ; j++ )
            arr[x + j*j] = 2;
    
    for( i = 1 ; i < 10001 ; i++ )
        for( j = 1 ; i + j*j < 10001 ; j++)
            if(arr[i] == 2 && arr[i+j*j] == 0) arr[i+j*j]=3;
            
    while(scanf("%d", &j)!=EOF){
        while(j--){
            scanf("%d", &x);
            i = sqrt(x) + 0.5;
            if( i * i == x ) puts("1");
            else if(arr[x] == 2) puts("2");
            else{
               /* while(x&3 == 0) x>>=2;
                if(x&7 == 7) puts("4");
                else puts("3");*/
                if(arr[x]==3) puts("3");
                else puts("4");
            }
        }
    }
    
    return 0;
}
