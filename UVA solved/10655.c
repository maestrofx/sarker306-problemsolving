#include<stdio.h>

/* x = a + b
   y = a * b
   a ^ n + b ^ n = ( a + b ) * ( a ^ (n-1) + b ^ (n-1) ) - a * b ( a ^ (n-2) + b ^ (n-2)
   [ F(n) ]   [ x  -y]  [F(n-1)]
            =
   [F(n-1)]   [ 1   0]   [F(n-2)]
*/
typedef struct{
    int r, c;
    long long array[3][3];
}array;

void print_array(array *x){
    int i, j;

    for(i=0;i<x->r;i++){
        for(j=0;j<x->c;j++) printf("%10lld", x->array[i][j]);
        puts("");
    }

    puts("");
}

void matrix_multiply(array *res, array *a, array *b){
    int i, j, k;

    for(i=0; i<a->r;i++){
        for(j=0;j<b->c;j++){
            res->array[i][j]=0;
            for(k=0;k<a->c;k++){
                res->array[i][j]=(res->array[i][j]+((a->array[i][k]))*((b->array[k][j])));
            }
        }
    }

    res->r=a->r, res->c=b->c;
}

void set_identity(array *x, int size){
    int i, j;

    x->r=x->c=size;
    for(i=0;i<x->r;i++){
        for(j=0;j<x->c;j++){
            x->array[i][j]=0;
        }
    }

    for(i=0;i<x->r;i++) x->array[i][i]=1;
}

void set_equal(array *to, array *from){
    int i, j;

    for(i=0;i<from->r;i++){
        for(j=0;j<from->c;j++){
            to->array[i][j]=from->array[i][j];
        }
    }

    to->r=from->r, to->c=from->c;
}

void array_init(array *arr){
    int i, j;

    for(i=0;i<arr->r;i++){
        for(j=0;j<arr->c;j++){
            arr->array[i][j]=0;
        }
    }
}

void big_matrix(array *res, array *base, long power){
    array temp;

    if(power<0) return;
    if(power==0){
        set_identity(res, base->r);
    }
    else if(power==1){
        set_equal(res, base);
    }
    else if(power%2){
        big_matrix(&temp, base, power-1);
        matrix_multiply(res, &temp, base);
    }
    else{
        big_matrix(&temp, base, power>>1);
        matrix_multiply(res, &temp, &temp);
    }
}

int main(){
    long long x, y, n;
    array res, base;

    base.r=base.c=res.r=res.c=2;
    base.array[1][0]=1, base.array[1][1]=0;
    while(scanf("%lld%lld%lld", &x, &y, &n)==3){
        base.array[0][0]=x, base.array[0][1]=-y;
        if(n){
            big_matrix(&res, &base, n-1);
            printf("%lld\n", res.array[0][0]*x+res.array[0][1]*2);
        }
        else puts("2");
        /*print_array(&res);*/
    }

    return 0;
}
