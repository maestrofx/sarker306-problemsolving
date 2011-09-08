#include<stdio.h>
#include<string.h>
#define SIZE 16

typedef struct{
    int r, c;
    long long array[SIZE][SIZE];
}array;

void print_array(array *x){
    int i, j;

    for(i=0;i<x->r;i++){
        for(j=0;j<x->c;j++) printf("%10lld", x->array[i][j]);
        puts("");
    }

    puts("");
}

void matrix_mod_multiply(array *res, array *a, array *b, long long mod){
    int i, j, k;

    for(i=0; i<a->r;i++){
        for(j=0;j<b->c;j++){
            res->array[i][j]=0;
            for(k=0;k<a->c;k++){
                res->array[i][j]=(res->array[i][j]+((a->array[i][k])%mod)*((b->array[k][j])%mod))%mod;
            }

            res->array[i][j]=(res->array[i][j]+mod)%mod;
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

void big_matrix_mod(array *res, array *base, long long power, long long mod){
    array temp;

    if(power<0) return;
    if(power==0){
        set_identity(res, base->r);
    }
    else if(power==1){
        set_equal(res, base);
    }
    else if(power%2){
        big_matrix_mod(&temp, base, power-1, mod);
        matrix_mod_multiply(res, &temp, base, mod);
    }
    else{
        big_matrix_mod(&temp, base, power>>1, mod);
        matrix_mod_multiply(res, &temp, &temp, mod);
    }
}

int main(){
    array base, res, term;
    long long d, n, m, i;

    while(scanf("%lld%lld%lld", &d, &n, &m)!=EOF){
        if(d==n && n==m && m==0) break;

        base.r=base.c=d;
        array_init(&base);
        for(i=0;i<d;i++){
            scanf("%lld", &base.array[0][i]);
            base.array[0][i]%=m;
        }

        for(i=1;i<d;i++) base.array[i][i-1]=1;

        term.r=d, term.c=1;
        for(i=d-1;i>=0;i--){
            scanf("%lld", &term.array[i][0]);
            term.array[i][0]%=m;
        }

        /*print_array(&base);*/
        /*print_array(&term);*/
        set_equal(&res, &base);

        if(n>=d){
            big_matrix_mod(&res, &base, n-d, m);
            matrix_mod_multiply(&base, &res, &term, m);

            printf("%lld\n", (base.array[0][0]+m)%m);
        }
        else printf("%lld\n", term.array[0][0]);
    }

    return 0;
}
