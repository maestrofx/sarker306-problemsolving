#include<stdio.h>
#include<stdlib.h>

#define RED 1
#define BLACK 2

/* Red Black Tree formation  */

struct node{
    char key[45];
    int value;
    char color;
    struct node *left, *right, *parent;
};

struct node *nil, *root;
long count, total=0;

struct node *grandparent(struct node *n){
	if ((n != nil) && (n->parent != nil))
		return n->parent->parent;
	else
		return nil;
}

struct node *uncle(struct node *n){
	struct node *g = grandparent(n);
	if (g == nil)
		return nil; /* No grandparent means no uncle */
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

struct node *sibling(struct node *n){
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

void rotate_left(struct node *x){
    struct node *y=x->right;

    if(y==0 || y==nil) return;
    x->right=y->left;
    y->left->parent=x;
    y->parent=x->parent;
    if(x->parent==nil){
        root=y;
    }
    else if(x==x->parent->left){
        x->parent->left=y;
    }
    else{
        x->parent->right=y;
    }
    y->left=x;
    x->parent=y;
}

void rotate_right(struct node *x){
    struct node *y=x->left;

    if(y==0 || y==nil) return;
    x->left=y->right;
    y->right->parent=x;
    y->parent=x->parent;
    if(x->parent==nil){
        root=y;
    }
    else if(x==x->parent->right){
        x->parent->right=y;
    }
    else{
        x->parent->left=y;
    }
    y->right=x;
    x->parent=y;
}

struct node* rb_create(char *x, int ans){
    struct node *pn=(struct node*) malloc(sizeof(struct node));
    if(!pn) return 0;

    strcpy(pn->key,x);
    pn->color=BLACK;
    pn->value=ans;
    pn->left=pn->right=pn->parent=nil;
    count++;
    return pn;
}

struct node *rb_search(struct node *ptr, char *k){
	struct node *x=ptr;
	int cond;

	if(x==nil) return nil;

	while(x!=nil){
        cond=strcmp(k, x->key);
        if(cond==0) break;
		if(cond<0)
			x=x->left;
		else x=x->right;
	}

	return x;
}

void rb_clear(struct node *ptr){
	struct node *x=ptr, *y;

	if(ptr==0 || ptr==nil) return;
	rb_clear(x->left);
	y=x;
	x=x->right;
	free(y);
	rb_clear(x);
}

int rb_insert(struct node *root, char *a, int val){
    struct node *y=nil, *x=root, *z;
    int cond;
    void insert_case1(struct node *n);

    while(x!=nil){
        y=x;
        cond=strcmp(a, x->key);
        if(cond<0) x=x->left;
        else if(cond>0) x=x->right;
        else{
			x->value++;
			return x->value;
		}
    }

    z=rb_create(a, val);
    z->parent=y;
    if(y==nil){
        root=z;
    }
    else if(strcmp(z->key,y->key)<0){
        y->left=z;
    }
    else y->right=z;

    z->right=z->left=nil;
    z->color=RED;

	insert_case1(z);
	return val;
}

void insert_case1(struct node *n)
{
	void insert_case2(struct node *n);
	if (n->parent == nil)
		n->color = BLACK;
	else
		insert_case2(n);
}

void insert_case2(struct node *n)
{
    void insert_case3(struct node *n);
	if (n->parent->color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(n);
}

void insert_case3(struct node *n)
{
    void insert_case4(struct node *n);
	struct node *u = uncle(n), *g;

	if ((u != nil) && (u->color == RED)) {
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert_case1(g);
	} else {
		insert_case4(n);
	}
}

void insert_case4(struct node *n)
{
    void insert_case5(struct node *n);
	struct node *g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)) {
		rotate_left(n->parent);
		n = n->left;
	} else if ((n == n->parent->left) && (n->parent == g->right)) {
		rotate_right(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void insert_case5(struct node *n)
{
	struct node *g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;
	if ((n == n->parent->left) && (n->parent == g->left)) {
		rotate_right(g);
	} else { /* (n == n->parent->right) and (n->parent == g->right) */
		rotate_left(g);
	}
}

void rb_walk(struct node *x){
	if(x==nil ) return;

	rb_walk(x->left);
	printf("%s %.4lf\n", x->key, x->value*100.0/total);
	rb_walk(x->right);
}

int main(){
	long test;
	char name[50];
	
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	nil=rb_create("",0);
	root=nil;
	scanf("%d", &test);
	getchar();
	gets(name);
	while(gets(name)){
		if(name[0]==0){
			test--;
			rb_walk(root);
			total=0;
			rb_clear(root);
			root=nil;
			if(test) printf("\n");
			else break;
		}
		else{
			total++;
			if(root!=nil) rb_insert(root, name, 1);
			else root=rb_create(name, 1);
		}
	}
	
	if(total){
		rb_walk(root);
		total=0;
		rb_clear(root);
	}
	
	free(nil);
	return 0;
}
