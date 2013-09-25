#include<stdio.h>
#include<stdlib.h>

#define RED 'r'
#define BLACK 'b'

struct node{
    unsigned key, size;
    char color;
    struct node *left, *right, *parent;
};

typedef struct node node;
typedef struct tree{
    node *root;
}tree;

node *nil;
node *minimum(node *n){
	while ( n->left != nil) n = n->left;

	return n;
}

node *successor(node *n){
	node *y;

	if ( n->right != nil ) return minimum(n->right);
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

node* rb_create(unsigned x){
    node *pn=(node*) malloc(sizeof(node));
    if(!pn) return 0;

    pn->key=x;  /* initalize */
    pn->size = 1;
    pn->color=BLACK;
    pn->left=pn->right=pn->parent=nil;
    return pn;
}

node *rb_search(node *ptr, unsigned k){
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
    node *y;

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

node* rb_insert(tree *Tree, unsigned a){
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

void rb_delete_fixup(tree *Tree, node *x){
	node *w;
    
	while(x!=Tree->root && x->color==BLACK){
		if(x==x->parent->left){
			w=x->parent->right;
			if(w->color==RED){
				w->color=BLACK;
				x->parent->color=RED;
				rotate_left(Tree, x->parent);
				w=x->parent->right;
			}

			if(w->left->color==BLACK && w->right->color==BLACK) w->color=RED, x=x->parent;
			else{
				if(w->right->color==BLACK){
					w->left->color=BLACK;
					w->color=RED;
					rotate_right(Tree, w);
                    w=x->parent->right;
				}
				
				w->color = w->parent->color;
				x->parent->color=BLACK;
				w->right->color=BLACK;
				rotate_left(Tree, x->parent);
				x=Tree->root;
			}
		}
		else{
			w=x->parent->left;
			if(w->color==RED){
				w->color=BLACK;
				x->parent->color=RED;
				rotate_right(Tree, x->parent);
				w=x->parent->left;
			}

			if(w->right->color==BLACK && w->left->color==BLACK) w->color=RED, x=x->parent;
			else{
				if(w->left->color==BLACK){
					w->right->color=BLACK;
					w->color=RED;
					rotate_left(Tree, w);
					w=x->parent->left;
				}

				w->color=x->parent->color;
				x->parent->color=BLACK;
				w->left->color=BLACK;
				rotate_right(Tree, x->parent);
				x=Tree->root;
			}
		}
	}
    
	x->color=BLACK;
}

void *rb_delete(tree *Tree, unsigned a){
    node *x, *y, *z=rb_search(Tree->root, a);

    if(z==nil) return nil;
	if(z->left==nil || z->right==nil) y=z;
	else y=successor(z);

    for ( x = y ; x != nil ; x = x->parent )
        x->size--;

	if(y->left!=nil) x=y->left;
	else x=y->right;
	x->parent=y->parent;
	if(y->parent==nil) Tree->root=x;
	else if(y==y->parent->left) y->parent->left=x;
	else y->parent->right=x;

	if(y!=z) z->key=y->key;  /* initialize z */

	if(y->color==BLACK) rb_delete_fixup(Tree, x);
	free(y);
    nil->left=nil->right=nil->parent=0;
}

node *select(node *x, unsigned n){
    unsigned order = 1 + x->left->size;
    if ( order + x->right->size < n ) return nil;
    for ( ; order != n ; order = 1 + x->left->size ){
        if ( order > n ) x = x->left;
        else x = x->right, n = n - order;
    }
    
    return x;
}

int main(){
    unsigned test, kase, i;
    unsigned k, sk, val;
	tree newtree;

	nil=(node*)malloc(sizeof(node));
	nil->key=1<<30;
	nil->left=nil->right=0;
	nil->parent=0;
    nil->size = 0;
	nil->color=BLACK;

    while ( scanf("%u", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            newtree.root = nil;
            
            scanf("%u", &k);
            for ( i = 1 ; i <= k ; i++ ) rb_insert(&newtree, i);
            for ( i = 1 ; i <= k ; i++ ){
                scanf("%u", &sk);
                val = select(newtree.root, sk + 1)->key;
                printf("%s%u", ( i == 1 ) ? "" : " ", val);
                rb_delete(&newtree, val);
            }
            
            puts("");
            rb_clear(newtree.root);
        }
    }
    
    free(nil);
    return 0;
}
