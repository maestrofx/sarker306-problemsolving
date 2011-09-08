#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define RED 'r'
#define BLACK 'b'


/* Red Black Tree formation  */

typedef struct _node{
    char key[25];
    long value;
    char color;
    struct _node *left, *right, *parent;
}node;

node *nil, *root;
long count;

node *grandparent(node *n){
	if ((n != nil) && (n->parent != nil))
		return n->parent->parent;
	else
		return nil;
}

node *uncle(node *n){
	node *g = grandparent(n);
	if (g == nil)
		return nil; /* No grandparent means no uncle */
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

node *sibling(node *n){
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

void rotate_left(node *x){
    node *y=x->right;

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

void rotate_right(node *x){
    node *y=x->left;

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

node* rb_create(char *x, long ans){
    node *pn=(node*) malloc(sizeof(node));
    if(!pn) return 0;

    strcpy(pn->key,x);
    pn->color=BLACK;
    pn->value=ans;
    pn->left=pn->right=pn->parent=nil;
    count++;
    return pn;
}

node *rb_search(node *ptr, char *k){
	node *x=ptr;
	long cond;

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

void rb_clear(node *ptr){
	node *x=ptr, *y;

	if(ptr==0 || ptr==nil) return;
	rb_clear(x->left);
	y=x;
	x=x->right;
	free(y);
	rb_clear(x);
}

long rb_insert(node *root, char *x, long val){
	long cond, ans=-1;
	node *pn=0;
	void insert_case1(node *);

	if(root==nil){
		root=rb_create(x, val);
		return val;
	}

	cond=strcmp(x,root->key);
	if(cond==0) return root->value;

	if(cond<0){
		if(root->left==nil){
			root->left=rb_create(x, val);
			pn=root->left;
			ans=val;
		}
		else ans=rb_insert(root->left, x, val);
	}
	if(cond>0){
		if(root->right==nil){
			root->right=rb_create(x, val);
			pn=root->right;
			ans=val;
		}
		else ans=rb_insert(root->right, x, val);
	}
	if(pn){
		pn->parent=root;
		pn->color=RED;
		insert_case1(pn);
	}
	return ans;
}

void insert_case1(node *n){
	void insert_case2(node *n);
	if (n->parent == nil)
		n->color = BLACK;
	else
		insert_case2(n);
}

void insert_case2(node *n){
    void insert_case3(node *n);
	if (n->parent->color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(n);
}

void insert_case3(node *n){
    void insert_case4(node *n);
	node *u = uncle(n), *g;

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

void insert_case4(node *n){
    void insert_case5(node *n);
	node *g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)) {
		rotate_left(n->parent);
		n = n->left;
	} else if ((n == n->parent->left) && (n->parent == g->right)) {
		rotate_right(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void insert_case5(node *n){
	node *g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;
	if ((n == n->parent->left) && (n->parent == g->left)) {
		rotate_right(g);
	} else { /* (n == n->parent->right) and (n->parent == g->right) */
		rotate_left(g);
	}
}

void rb_walk(node *x){
	if(x==nil ) return;

	rb_walk(x->left);
	printf("%s - %d\n", x->key, x->value);
	rb_walk(x->right);
}

/********************************************************/
/***************disjoint set ****************************/
long rank[200005];
long parent[200005];

void reset(){
	long i;
	for(i=1; parent[i] ;i++) parent[i]=0, rank[i]=0;
}

long find(long x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

void link ( long a, long b){
    if(rank[a]>rank[b]) rank[a]+=rank[b], parent[b]=a;
    else rank[b]+=rank[a], parent[a]=b;
}

/********************************************************/

long max(long a, long b){
    return (a>b)? a:b;
}

int main(){
    long test, edges, i;
    long x, y, a, b;
    char string1[25], string2[25];
    node *pn;
    
    nil=rb_create("", -1);
    while(scanf("%ld", &test)!=EOF){
        while(test--){
            reset();
            x=count=1;
            scanf("%ld", &edges);
            scanf("%s%s", string1, string2);
            root=rb_create(string1, count);
            y=rb_insert(root, string2, count);
            if(parent[x]==0) parent[x]=x, rank[x]=1;
            if(parent[y]==0) parent[y]=y, rank[y]=1;
            a=find(x), b=find(y);
            if(a!=b) link(a, b);
            printf("%ld\n", max(rank[a], rank[b]));
            for(i=1;i<edges;i++){
                scanf("%s%s", string1, string2);
                x=rb_insert(root, string1, count);
                y=rb_insert(root, string2, count);
                if(parent[x]==0) parent[x]=x, rank[x]=1;
                if(parent[y]==0) parent[y]=y, rank[y]=1;
                a=find(x), b=find(y);
                if(a!=b) link(a, b);
                printf("%ld\n", max(rank[a], rank[b]));
            }
            
            rb_clear(root);
        }
    }
    
    free(nil);
    return 0;
}
