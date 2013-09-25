#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 1e-9

typedef struct{
    double a, b, c;
}line;

typedef struct{
    double x, y;
}point;

typedef struct{
    double start, end;
}Interval;

int compareInterval(const void *a, const void *b){
    Interval *x = (Interval*)a, *y = (Interval*)b;
    
    if ( fabs(x->start - y->start) < EPS ){
        if ( x->end > y->end ) return -1;
        else return 1;
    }
    else if ( x->start < y->start ) return -1;
    else return 1;
}

Interval intervals[505];
point centers[505];
double radii[505];
point base;

void calculateFloorShadowInterval( int i ){
    double distance, angleSlopeOfBaseCenterLine;
    double delx, dely, theta, tanTheta;
    double m1;
    double startx, endx;
    
    delx = base.x - centers[i].x;
    dely = base.y - centers[i].y;
    distance = sqrt(delx * delx + dely * dely );
    
    tanTheta = radii[i]/sqrt(distance*distance - radii[i]*radii[i]);
    
    if ( fabs(delx + dely * tanTheta) > EPS ){
        m1 = (dely - delx * tanTheta)/(delx + dely * tanTheta);
        startx = base.x - base.y/m1;
    }
    else startx = base.x;
    
    if ( fabs(delx - dely * tanTheta) > EPS ){
        m1 = (dely + delx * tanTheta)/(delx - dely * tanTheta);
        endx = base.x - base.y/m1;
    }
    else endx = base.x;
    if ( startx > endx ){
        delx = startx;
        startx = endx;
        endx = delx;
    }
    
    intervals[i].start = startx, intervals[i].end = endx;
}

int main(){
    int n, i, flag;
    double s, e;
    
    while ( scanf("%d", &n) == 1 && n > 0 ){
        scanf("%lf%lf", &base.x, &base.y);
        for ( i = 0 ; i < n ; i++ ){
            scanf("%lf%lf%lf", &centers[i].x, &centers[i].y, &radii[i]);
            calculateFloorShadowInterval(i);
        }
        
        qsort( intervals, n, sizeof(Interval), compareInterval );
        s = intervals[0].start, e = intervals[0].end;
        for ( i = flag = 1 ; i < n ; i++ ){
            if ( e < intervals[i].start ){
                printf("%.2lf %.2lf\n", s - EPS, e - EPS);
                s = intervals[i].start;
                e = intervals[i].end;
            }
            
            else if ( e < intervals[i].end ) e = intervals[i].end;
        }
        
        printf("%.2lf %.2lf\n\n", s - EPS, e - EPS);
    }
    
    return 0;
}
