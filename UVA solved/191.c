#include <stdio.h>
#include <math.h>
#define EPS 1e-8
enum {LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, START, DESTINATION};

typedef struct point{
    double x, y;
}point;

typedef struct line{
    double a, b, c;
}line;

void minus(point *p2, point *p0, point *p1){
    p2->x = p0->x - p1->x;
    p2->y = p0->y - p1->y;
}

int classify_edge(point *p2, point *p0, point *p1){
    point a, b;
    double det;

    minus(&a, p1, p0);
    minus(&b, p2, p0);

    det = a.x * b.y - b.x * a.y;
    if( fabs(det) < EPS ){
        if( fabs( p2->x - p0->x ) < EPS && fabs( p2->y - p0->y ) < EPS ) return START;
        else if( fabs( p2->x - p1->x ) < EPS && fabs( p2->y - p1->y ) < EPS ) return DESTINATION;
        else if( a.x * b.x < 0 || a.y * b.y < 0 ) return BEHIND;
        if( sqrt( a.x * a.x + a.y * a.y ) < sqrt( b.x * b.x + b.y * b.y ) ) return BEYOND;
        return BETWEEN;
    }
    else if( det > 0 ) return LEFT;
    else return RIGHT;
}

void line_make( line *l, point *p0, point *p1 ){
    l->a = p0->y - p1->y;
    l->b = p1->x - p0->x;
    l->c = p0->x * p1->y - p1->x * p0->y;
}

int intersection( point *p0, point *p1, point *p2, point *p3, point *a){
    line one, two;
    double det, detx, dety;

    line_make( &one, p0, p1 );
    line_make( &two, p2, p3 );

    if( fabs( det = one.a * two.b - one.b * two.a ) < EPS ) return 0;
    detx = one.c * two.b - one.b * two.c ;
    dety = one.a * two.c - one.c * two.a ;
    a->x = -detx / det, a->y = -dety / det;
    return 1;
}

int within_rectangle( point *p0, point *lefttop, point *rightbottom ){
    if( p0->x < lefttop->x && fabs( p0->x - lefttop->x ) > EPS ) return 0;
    if( p0->x > rightbottom->x && fabs( p0->x - rightbottom->x ) > EPS ) return 0;
    if( p0->y > lefttop->y && fabs( p0->y - lefttop->y ) > EPS ) return 0;
    if( p0->y < rightbottom->y && fabs( p0->y - rightbottom->y ) > EPS ) return 0;
    return 1;
}

int main(){
    point a, c, one, two, tmp, x;
    double tmp1;
    int test, flag;

    while(scanf("%d", &test) != EOF){
        while(test--){
            flag = 0;
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &one.x, &one.y, &two.x, &two.y,
                &a.x, &a.y, &c.x, &c.y);

            if( a.x > c.x ) { tmp1 = c.x ; c.x = a.x; a.x = tmp1; }
            if( a.y < c.y ) { tmp1 = c.y ; c.y = a.y; a.y = tmp1; }

            if( within_rectangle( &one, &a, &c) || within_rectangle( &two, &a, &c) ) puts("T");
            else{
                flag = 0;
                tmp.x = a.x, tmp.y = c.y;
                if( intersection( &one, &two, &a, &tmp, &x) && classify_edge( &x, &one, &two) >=4 && within_rectangle( &x, &a, &c) ) flag = 1;

                if( intersection( &one, &two, &c, &tmp, &x) && classify_edge( &x, &one, &two) >=4 && within_rectangle( &x, &a, &c) ) flag = 1;

                tmp.y = a.y, tmp.x = c.x;
                if( intersection( &one, &two, &a, &tmp, &x) &&  classify_edge( &x, &one, &two) >=4 && within_rectangle( &x, &a, &c) ) flag = 1;

                if( intersection( &one, &two, &c, &tmp, &x) &&  classify_edge( &x, &one, &two) >=4 && within_rectangle( &x, &a, &c) ) flag = 1;

                flag ? puts("T") : puts("F");
            }
        }
    }

    return 0;
}
