#include<stdio.h>
#include<stdlib.h>

#define RED 'r'
#define BLACK 'b'

struct node{
    long key;
    int size;
    char color;
    struct node *left, *right, *parent;
};

typedef struct node node;
typedef struct tree{
    node *root;
}tree;

node *nil;
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
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
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
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

node* rb_create(int x){
    node *pn=(node*) malloc(sizeof(node));
    if(!pn) return 0;

    pn->key=x;  /* initalize */
    pn->size = 1;
    pn->color=BLACK;
    pn->left=pn->right=pn->parent=nil;
    return pn;
}

node *rb_search(node *ptr, long k){
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

node* rb_insert(tree *Tree, long a){
    node *y=nil, *x=Tree->root, *z;

    while(x!=nil){
        y=x;
        x->size++;
        if(a<x->key) x=x->left;   /* compare */
        else x=x->right;
    }

    z=rb_create(a);
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

node *select(node *x, int n){
    int order = 1 + x->left->size;
    
    for ( ; order != n ; order = 1 + x->left->size ){
        if ( order > n ) x = x->left;
        else x = x->right, n = n - order;
    }
    
    return x;
}

long insertions[30005];

int main(){
    int m, n, test, kase, k, i, x;
	tree newtree;

	nil=(node*)malloc(sizeof(node));
	nil->key=1<<30;
	nil->left=nil->right=0;
	nil->parent=0;
    nil->size = 0;
	nil->color=BLACK;

    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            if ( kase > 1 ) puts("");
            k = 1;
            newtree.root = nil;
            scanf("%d%d", &m, &n);
            for ( i = 0 ; i < m ; i++ )
                scanf("%ld", insertions + i);
            
            i = 0;
            while ( n-- ){
                scanf("%d", &x);
                x--;
                while ( i <= x ){
                    rb_insert( &newtree, insertions[i] );
                    i++;
                }
                
                printf("%ld\n", select(newtree.root, k++)->key);
            }
            
            rb_clear(newtree.root);
        }
    }
    
    free(nil);
    return 0;
}
