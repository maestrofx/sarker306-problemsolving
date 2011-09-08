#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE 201

typedef struct{
    int x, y;
    long coeff[SIZE][SIZE];
}poly;

void init(poly *p, int n){
    int i, j;

    for ( i = 0 ; i <=n ; i++ )
        for ( j = 0 ; j <= n ; j++ )
            p->coeff[i][j] = 0;

    p->x = p->y = 0;
}

void parse(poly *p, char *prog){
    char *ptr, sign, tmp;
    long c, x, y;

    while( *prog ){
        c = x = y = 0;
        sign = 1;
        if(*prog == '+') prog++;
        else if(*prog == '-') sign = -1, prog++;
        for( ptr= prog ; *ptr && isdigit(*ptr) ; ptr++);
        tmp = *ptr;
        *ptr = 0;
        if(ptr != prog) c = atol(prog);
        else c = 1;
        *ptr = tmp;
        prog = ptr;
        if(*prog == 'x'){
            prog++;
            for( ptr= prog ; *ptr && isdigit(*ptr) ; ptr++);
            tmp = *ptr;
            *ptr = 0;
            if( ptr != prog) x = atol(prog);
            else x = 1;
            if( p->x < x ) p->x = x;
            *ptr = tmp;
            prog = ptr;
            if(*prog == 'y'){
                prog++;
                for( ptr= prog ; *ptr && isdigit(*ptr) ; ptr++);
                tmp = *ptr;
                *ptr = 0;
                if( ptr != prog) y = atol(prog);
                else y = 1;
                if( p->y < y ) p->y = y;
                *ptr = tmp;
                prog = ptr;
            }
        }
        else if( *prog == 'y') {
            prog++;
            for( ptr= prog ; *ptr && isdigit(*ptr) ; ptr++);
            tmp = *ptr;
            *ptr = 0;
            if( ptr != prog) y = atol(prog);
            else y = 1;
            if( p->y < y ) p->y = y;
            *ptr = tmp;
            prog = ptr;
            if(*prog == 'x'){
                prog++;
                for( ptr= prog ; *ptr && isdigit(*ptr) ; ptr++);
                tmp = *ptr;
                *ptr = 0;
                if( ptr != prog) x = atol(prog);
                else x = 1;
                if( p->x < x ) p->x = x;
                *ptr = tmp;
                prog = ptr;
            }
        }

        p->coeff[x][y] += c * sign;
    }
}

void raw_print(poly *p){
    int i, j, sign, flag = 0;
    long c;

    for( i = p->x ; i >= 0 ; i-- )
        for( j = 0 ; j <= p->y ; j++ ){
            if( p->coeff[i][j]){
                sign = '+', c = p->coeff[i][j];
                if( c < 0 ) sign = '-', c = -c;
                if( !flag && sign == '-') putchar(sign), flag = 1;
                else if(flag) printf(" %c ", sign);
                if(c > 1 || (i == 0 && j == 0) ) printf("%ld", c);
                if( i ){
                    if(i > 1) printf("x^%d", i);
                    else putchar('x');
                }
                if( j ){
                    if( j > 1) printf("y^%d", j);
                    else putchar('y');
                }
                flag = 1;
            }
        }

    if( !flag ) putchar('0');
    puts("");
}

void cute_print(poly *p){
    char arr[2][160];
    int len[2] = {0, 0};
    int i, j, k, sign, flag = 0;
    long c;

    arr[0][0] = arr[1][0] = 0;
    for( i = p->x ; i >= 0 ; i-- )
        for( j = 0 ; j <= p->y ; j++ ){
            if( p->coeff[i][j]){
                sign = '+', c = p->coeff[i][j];
                if( c < 0 ) sign = '-', c = -c;
                if( !flag && sign == '-') len[0] += sprintf(&arr[0][len[0]], "%c", sign);
                else if(flag) len[0] += sprintf(&arr[0][len[0]], " %c ", sign);
                if(c > 1 || (i == 0 && j == 0) )
                    len[0] += sprintf(&arr[0][len[0]], "%ld", c);
                if( i ){
                    len[0] += sprintf(&arr[0][len[0]], "x");
                    if(i > 1){
                        for( ; len[1] < len[0] ; len[1]++) arr[1][len[1]] = ' ';
                        len[1] += sprintf(&arr[1][len[1]], "%d", i);
                        for( ; len[0] < len[1] ; len[0]++) arr[0][len[0]] = ' ';
                        arr[0][len[0]] = 0;
                    }
                }
                if( j ){
                    len[0] += sprintf(&arr[0][len[0]], "y");
                    if(j > 1){
                        for( ; len[1] < len[0] ; len[1]++) arr[1][len[1]] = ' ';
                        len[1] += sprintf(&arr[1][len[1]], "%d", j);
                        for( ; len[0] < len[1] ; len[0]++) arr[0][len[0]] = ' ';
                        arr[0][len[0]] = 0;
                    }
                }
                flag = 1;
            }
        }

    for( ; len[1] < len[0] ; len[1]++) arr[1][len[1]] = ' ';
    arr[1][len[1]] = 0;

    if( !flag){
        sprintf(arr[0], "0");
        sprintf(arr[1], " ");
    }

    puts(arr[1]);
    puts(arr[0]);
}

void poly_multiply(poly *res, poly *fir, poly *sec){
    int i, j;
    long c1[SIZE*SIZE], c2[SIZE*SIZE];
    int x1[SIZE*SIZE], y1[SIZE*SIZE], x2[SIZE*SIZE], y2[SIZE*SIZE];
    int ind1 = 0, ind2 = 0;

    for( i = 0 ; i <= fir->x ; i++ )
        for( j = 0 ; j <= fir->y ; j++ )
            if( fir->coeff[i][j] ){
                c1[ind1] = fir->coeff[i][j], x1[ind1] = i, y1[ind1] = j;
                ind1++;
            }

    for( i = 0 ; i <= sec->x ; i++ )
        for( j = 0 ; j <= sec->y ; j++ )
            if( sec->coeff[i][j] ){
                c2[ind2] = sec->coeff[i][j], x2[ind2] = i, y2[ind2] = j;
                ind2++;
            }

    for( i = 0 ; i < ind1 ; i++ )
        for( j = 0 ; j < ind2 ; j++ )
            res->coeff[x1[i]+x2[j]][y1[i]+y2[j]] += c1[i] * c2[j];

    res->x = fir->x + sec->x , res->y = fir->y + sec->y;
}

int main(){
    char input[SIZE];
    poly fir, sec, res;

    while(gets(input)){
        if(input[0] == '#') break;
        init(&fir, 100);
        init(&sec, 100);
        init(&res, 200);
        parse(&fir, input);
        gets(input);
        parse(&sec, input);
        poly_multiply(&res, &fir, &sec);
        cute_print(&res);
    }

    return 0;
}
