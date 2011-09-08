#include<stdio.h>
#include<stdlib.h>

#define RED 'r'
#define BLACK 'b'

/* Red Black Tree formation  */

struct node{
    char key[50];
    char value[50];
    char color;
    struct node *left, *right, *parent;
};

struct node *nil, *root;
int count;

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

struct node* rb_create(char *x, char *val){
    struct node *pn=(struct node*) malloc(sizeof(struct node));
    if(!pn) return 0;

    strcpy(pn->key,x);
    pn->color=BLACK;
    strcpy(pn->value, val);
    pn->left=pn->right=pn->parent=nil;
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

char* rb_insert(struct node *root, char *a, char *val){
    struct node *y=nil, *x=root, *z;
    int cond;
    void insert_case1(struct node *n);

    while(x!=nil){
        y=x;
        cond=strcmp(a, x->key);
        if(cond<0) x=x->left;
        else if(cond>0) x=x->right;
        else return x->value;
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

void insert_case1(struct node *n){
	void insert_case2(struct node *n);
	if (n->parent == nil)
		n->color = BLACK;
	else
		insert_case2(n);
}

void insert_case2(struct node *n){
    void insert_case3(struct node *n);
	if (n->parent->color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(n);
}

void insert_case3(struct node *n){
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

void insert_case4(struct node *n){
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

void insert_case5(struct node *n){
	struct node *g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;
	if ((n == n->parent->left) && (n->parent == g->left)) {
		rotate_right(g);
	} else { /* (n == n->parent->right) and (n->parent == g->right) */
		rotate_left(g);
	}
}

void reverse(char *des, char *source){
	char *p;
	for(p=source;*p;p++);
	for(--p; ;p--, des++){
		*des=*p;
		if(p==source) break;
	}
	*(++des)=0;
}

int IsVowel(char a){
	if(a=='a' || a=='e' || a=='i' || a=='o' || a=='u') return 1;
	return 0;
}

int main(){
	int irr, n, i;
	char a[50], b[50];
	struct node *pn;
	
	nil=rb_create("","");
	
	while(scanf("%d%d", &irr, &n)!=EOF){
		root=nil;
		if(irr) scanf("%s%s", a, b);
		root=rb_create(a, b);
		for(i=1;i<irr;i++){
			scanf("%s%s", a, b);
			rb_insert(root, a, b);
		}
		
		for(i=0;i<n;i++){
			scanf("%s", a);
			pn=rb_search(root, a);
			if(pn!=nil){
				printf("%s\n", pn->value);
			}
			else{
				reverse(b, a);
				if(b[0]=='y' && !IsVowel(b[1])){
					b[0]='i';
					reverse(a, b);
					printf("%ses\n", a);
				}
				else if(b[0]=='x' || b[0]=='o' || b[0]=='s' || (b[0]=='h' && (b[1]=='c' || b[1]=='s'))){
					printf("%ses\n", a);
				}
				else printf("%ss\n", a);
			}
		}
		
		rb_clear(root);
	}
	
	free(nil);
	return 0;
}
