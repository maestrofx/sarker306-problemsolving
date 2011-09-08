#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define LEFTTURN -1
#define RIGHTTURN 1
#define NOTURN 0
#define ERR 0.000000001

typedef struct point{
    double x, y;
}point;

point p0;
point p[10000], stack[10000];

double distance( point a, point b ){
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

int direction( point p0, point p1, point p2 ){
    double d = ( p2.x - p0.x )*( p1.y - p0.y ) - ( p1.x - p0.x )*( p2.y - p0.y ) ;

    if( fabs( d ) < ERR ) return NOTURN ;
    if( d > 0 ) return RIGHTTURN ;
    if( d < 0 ) return LEFTTURN ;
}

int sort_point_on_angle(const void *a, const void *b){
    point *p, *q ;

    p = ( point* ) a ;
    q = ( point* ) b ;

    int d = direction( p0, *p, *q ) ;

    if( d == NOTURN ){
        if( distance( p0, *p ) > distance( p0, *q )) return -1 ;
        return 1 ;
    }
    
    if( d == RIGHTTURN ) return 1 ;
    return -1 ;
}

int Graham_scan( point p[], int N, point stack[] ){ /* Q: input points, stack: convex-hull points*/
    int i, min, top, d ;
    point temp ;

	if( N == 1 ){
		stack[1] = stack[2] = p[0] ; return 2 ;
	}
	
    for( i = 1, min = 0; i < N; i++ ){
        if( fabs( p[i].y - p[min].y ) <= ERR ){
            if( p[i].x < p[min].x) min = i;
        }
        else{
            if( p[i].y < p[min].y) min = i;
        }
    }
    temp = p[0] ; p[0] = p[min] ; p[min] = temp ;
    p0 = p[0];

    qsort( &p[1], N - 1, sizeof(point), sort_point_on_angle );

	p[N] = p0 ;
    top = 0 ;

    stack[++top] = p[0] ;
    stack[++top] = p[1] ;
    stack[++top] = p[2] ;

    for( i = 3; i <= N; i++ ){
        while( 1 ){
            d = direction( stack[top-1], stack[top], p[i] ) ;

            if( d == RIGHTTURN ) top-- ;
            else break ;
        }

        stack[++top] = p[i] ;
    }
    return top ;
}

int main (){
    int i, N, H, kase ;
	double length ;

	/*freopen( "218.in", "r", stdin ) ;*/

	kase = 1 ;

	while( scanf( "%d", &N ) == 1 && N ){
		if( kase != 1 ) printf( "\n" ) ;

		for( i = 0; i < N; i++ ){
			scanf( "%lf%lf", &p[i].x, &p[i].y ) ;
		}

		H = Graham_scan( p, N, stack ) ;

		printf( "Region #%d:\n", kase++ ) ;

		length = 0.0 ;

		for( i = H; i > 1; i-- ){
			printf( "(%.1lf,%.1lf)-", stack[i].x, stack[i].y ) ;

			length += distance( stack[i], stack[i-1] ) ;
		}
		printf( "(%.1lf,%.1lf)\n", stack[1].x, stack[1].y ) ;

		printf( "Perimeter length = %.2lf\n", length ) ;
	}
	
	return 0 ;
}
