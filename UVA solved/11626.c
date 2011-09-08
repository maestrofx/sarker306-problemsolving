#include<stdio.h>
#include<stdlib.h>
#define MAXPOINT 100000
#define MAXCO 1000000000
#define LEFTTURN -1
#define RIGHTTURN 1
#define NOTURN 0
#define ERR 0.000000001

typedef struct{
    long long x, y;
}point;

point points[MAXPOINT+1], stack[MAXPOINT+1], p0;

long long distance( point a, point b ){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

int direction( point p0, point p1, point p2 ){
    long long d = ( p2.x - p0.x )*( p1.y - p0.y ) - ( p1.x - p0.x )*( p2.y - p0.y ) ;

    if(d==0) return NOTURN ;
    if(d>0) return RIGHTTURN ;
    if(d<0) return LEFTTURN ;
}

int sort_point_on_angle(const void *a, const void *b){
    point *p, *q ;
    int d;

    p=(point*)a ;
    q=(point*)b ;

    d=direction(p0, *p, *q) ;

    if(d==NOTURN){
        if( distance(p0, *p)>distance(p0,*q)) return -1 ;
        return 1 ;
    }

    if(d==RIGHTTURN ) return 1 ;
    return -1 ;
}

int main(){
    long test, n, i, j, k, top;
    long long x, y;
    char yes[3];
    point tmp;

    while(scanf("%ld", &test)!=EOF){
        while(test--){
            scanf("%ld", &n);
            for(i=j=0, x=y=MAXCO;i<n;i++){
                scanf("%lld%lld%s", &points[j].x, &points[j].y, yes);
                if(yes[0]=='Y'){
                    if(points[j].x<x || (points[j].x==x && points[j].y<y))
                        x=points[j].x, y=points[j].y, k=j;
                    j++;
                }
            }

            n=j;
            tmp=points[0];
            points[0]=points[k];
            points[k]=tmp;
            p0=points[0];
            qsort(&points[1], n-1, sizeof(point), sort_point_on_angle);
            /*printf("%lld %lld\n", p0.x, p0.y);
            printf("%d\n", n);
            for( i = 0 ; i < n ; i++ ) printf("%lld %lld\n", points[i].x, points[i].y);*/

            top = 0 ;

            stack[++top] = points[0] ;
            stack[++top] = points[1] ;
            stack[++top] = points[2] ;

            for( i = 3; i<n; i++ ){
                while( 1 ){
                    x=direction( stack[top-1], stack[top], points[i] ) ;

                    if(x==RIGHTTURN ) top-- ;
                    else break;
                }

                stack[++top] = points[i] ;
            }

            printf("%ld\n", top);
            for(i=1;i<=top;i++) printf("%lld %lld\n", stack[i].x, stack[i].y);
        }
    }

    return 0;
}
