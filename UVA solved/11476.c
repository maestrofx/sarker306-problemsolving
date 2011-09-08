/*program to determine the factors of a number. For bigger numbers.*/
#include<stdio.h>
#include<stdlib.h>

#define MAXSIEVE 1000000
#define MAXSQRT 1000 /* sqrt(Maxsieve) */

char prm[MAXSIEVE+2];
void sieve(){
    register long i, j;

    for(i=4;i<MAXSIEVE;i+=2) prm[i]=1;
    for(i=3;i<MAXSQRT;i+=2)
        if(prm[i]==0)
            for(j=i*i;j<MAXSIEVE;j+=i*2) prm[j]=1;
}

/* Red Black Structure for Factoring Handling */

#define RED 'r'
#define BLACK 'b'

struct node{
    long long key;
    int freq;
    char color;
    struct node *left, *right, *parent;
};

typedef struct node node;
typedef struct tree{
    node *root;
}tree;

char flag;
node *nil;
tree NumTree;

node *minimum(node *n){
	while(n->left!=nil) n=n->left;

	return n;
}

node *successor(node *n){
	node *y;

	if(n->right!=nil) return minimum(n->right);
	y=n->parent;
	while(y!=nil && n==y->right) n=y, y=y->parent;
	return y;
}

void rotate_left(tree *Tree, node *x){
    node *y=x->right;

    if(x==nil || y==nil) return;
    x->right=y->left;
    if(y->left!=nil) y->left->parent=x;
    y->parent=x->parent;
    if(x->parent==nil) Tree->root=y;
    else if(x==x->parent->left) x->parent->left=y;
    else x->parent->right=y;
    y->left=x;
    x->parent=y;
}

void rotate_right(tree *Tree, node *x){
    node *y=x->left;

    if(x==nil || y==nil) return;
    x->left=y->right;
    if(y->right!=nil) y->right->parent=x;
    y->parent=x->parent;
    if(x->parent==nil) Tree->root=y;
    else if(x==x->parent->right) x->parent->right=y;
    else x->parent->left=y;
    y->right=x;
    x->parent=y;
}

node* rb_create(long long x, int freq){
    node *pn=(node*) malloc(sizeof(node));
    if(!pn) return 0;

    pn->key=x;  /* initalize */
    pn->freq=freq;
    pn->color=BLACK;
    pn->left=pn->right=pn->parent=nil;
    return pn;
}

node *rb_search(node *ptr, long long k){
	node *x=ptr;

	if(x==nil) return nil;

	while(x!=nil && k!=x->key){
		if(k<x->key) x=x->left;  /* compare */
		else x=x->right;
	}

	return x;
}

void rb_clear(node *ptr){
	node *x=ptr, *y;

	if(ptr==nil) return;
	rb_clear(x->left);
	if(flag) printf(" * ");
	if(x->freq>1) printf("%lld^%d", x->key, x->freq);
	else printf("%lld", x->key);
	flag=1;
	y=x;
	x=x->right;
	free(y);
	rb_clear(x);
}

void rb_insert_fixup(tree *Tree, node *z){
    node *y, *x;

    while(z->parent->color==RED){
		if(z->parent==z->parent->parent->left){
			y=z->parent->parent->right;

			if(y->color==RED){
				z->parent->color=y->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
			}
			else{
				if(z==z->parent->right){
					z=z->parent;
					rotate_left(Tree, z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				rotate_right(Tree, z->parent->parent);
			}
		}
		else{
			y=z->parent->parent->left;

			if(y->color==RED){
				z->parent->color=y->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
			}
			else{
				if(z==z->parent->left){
					z=z->parent;
					rotate_right(Tree, z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				rotate_left(Tree, z->parent->parent);
			}
		}
    }

    Tree->root->color=BLACK;
}

node* rb_insert(tree *Tree, long long a, int freq){
    node *y=nil, *x=Tree->root, *z;

    while(x!=nil){
        y=x;
        if(a==x->key){
            x->freq+=freq;
            return x;    /* if already in tree ? */
        }
        if(a<x->key) x=x->left;   /* compare */
        else x=x->right;
    }

    z=rb_create(a, freq);
    z->parent=y;
    if(y==nil) Tree->root=z;
    else if(z->key<y->key) y->left=z;  /* compare */
    else y->right=z;

    z->right=z->left=nil;
    z->color=RED;

    rb_insert_fixup(Tree, z);
    nil->left=nil->right=nil->parent=0;
    return z;
}

#define PRIME 2
#define MAYBE_PRIME 1
#define NOTPRIME 0
#define LIMIT 4611686018427387904LL

int c;
long long mul_mod(long long x, long long y, unsigned long long mod){
    unsigned long long tmp;

    x%=mod, y%=mod;
    if(y==0) return 0;
    tmp=(LIMIT/y);
    if(x>tmp){
        for(tmp=0;y;y>>=1, x=(x<<1)%mod) if(y&1!=0) tmp=(tmp+x)%mod;
        return tmp;
    }
    else return (x*y)%mod;
}

long long modular_exp(long long b, long long p, long long x){
    long long tmp;

    if(p==0) return 1;
    if(p%2==0){
        tmp=modular_exp(b, p/2, x);
        tmp=mul_mod(tmp, tmp, x);
    }
    else tmp=mul_mod(modular_exp(b, p-1, x), b, x);
    return tmp;
}

int witness(long long a, long long n, long long t, long long u){
    register long long i, x, prevx;

    x=modular_exp(a, u, n);
    for(i=1;i<=t;i++){
        prevx=x;
        x=mul_mod(x, x, n);
        if(x==1 && prevx!=1 && prevx!=n-1) return 1;
    }

    if(x!=1) return 1;
    return 0;
}

int isPrime(long long n){
    long long array[]={1,2,3,5,7,11,13,17,23,31,61};
    register long long k, a, s, d, i;
    long long m, x, prevx;

    if(n<MAXSIEVE){
        if(prm[n]==0) return PRIME;
        else return NOTPRIME;
    }

    for(m=n-1, s=d=0;m%2==0; m/=2, s++);
    d=m;

    if(s==0) return NOTPRIME;
    for(k=1;k<10;k++){
        a=array[k];
        if(witness(a, n, s, d)) return NOTPRIME;
    }

    return MAYBE_PRIME;
}

long long f(long long x, long long n){
    long long tmp;

	tmp=(mul_mod(x, x, n)+c)%n;
	while(tmp<0) tmp+=n;

	return tmp;
}

long long gcd(long long m, long long n){
	 register long long temp;

	 while(n){
		temp=m;
		m=n;
		n=temp%n;
	 }

	 return m;
}

long long pollard(long long (*f) (long long, long long), long long n){  /* brent cycle */
    register long long x, y, d, abs_val=1;
    register long k=2, i=1;

	x=y=3;
	d=1;

	if((n&1)==0) d=2;
	else while(1){
        i++;
		x=f(x, n);
		abs_val=(x>y)? x-y : y-x;
		d=gcd(abs_val, n);
		if(d!=1) break;
		if(i==k) y=x, k<<=1;
	}

	if(d!=n) return d;
	else return 0;
}

void factorize(long long n){
    int array[]={ 3, 5, -1, 1, -3, -5};
    register int i, j;
    long long value;

    if(n==1 || isPrime(n)!=NOTPRIME){
        rb_insert(&NumTree, n, 1);
        return;
    }

    for(i=0;i<6;i++){
        c=array[i];

        value=pollard(f, n);
        if(value){
            if(isPrime(value)==NOTPRIME){
                factorize(value);
                factorize(n/value);
            }
            else{
                for(j=0; n%value==0; n/=value, j++);
                rb_insert(&NumTree, value, j);
                if(n!=1) factorize(n);
            }

            return;
        }
    }
}

int main(){
 	long long a, tmp, test;
 	register int i, j;

    sieve();
	nil=(node*)malloc(sizeof(node));
	nil->color=BLACK;
    /*freopen("D:\\Virtual_Desktop\\data2.txt", "r", stdin);
    freopen("D:\\Virtual_Desktop\\data2_ans.txt", "w", stdout);*/
	while(scanf("%lld", &test)==1){
        while(test--){
            NumTree.root=nil;
            scanf("%lld", &a);
     		printf("%lld = ", a);
            flag=0;
      		factorize(a);
      		rb_clear(NumTree.root);
      		puts("");
        }
  	}

    free(nil);
 	return 0;
}
