#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define RED 'r'
#define BLACK 'b'

#define RADIUS 6378
#define PI 3.1415926535897932384626433832795

double degtorad(double degree);
double greatcircledistance(double lat1, double long1, double lat2, double long2);

/* Red Black Tree formation prototype  */

struct t_node{
    char key[50];
    double latitude, longitude;
    char color;
    struct t_node *left, *right, *parent;
};

typedef struct t_node node;
node *nil, *root;

void insert_case5(node *n);
void insert_case4(node *n);
void insert_case3(node *n);
void insert_case2(node *n);
void insert_case1(node *n);
node *grandparent(node *n);
node *uncle(node *n);
node *sibling(node *n);
void rotate_left(node *x);
void rotate_right(node *x);
node* rb_create(char *x, double latitude, double longitude);
node *rb_search(node *ptr, char *k);
void rb_insert(node *root, char *a, double latitude, double longitude);
void rb_clear(node *ptr);

int main(){
	char name[50], name1[5];
	long distance;
	double latitude, longitude;
	node *city1, *city2;
	
	nil=rb_create("", 0, 0);
	root=nil;
	while(scanf("%s", name)!=EOF){
		if(name[0]=='#' && name[1]==0) break;
		
		scanf("%lf%lf", &latitude, &longitude);
		if(root==nil) root=rb_create(name, latitude, longitude);
		else rb_insert(root, name, latitude, longitude);
	}
	
	while(scanf("%s%s", name, name1)!=EOF){
		if(name[0]=='#' && name[1]==0 && name1[0]=='#' && name1[1]==0) break;
		
		printf("%s - %s\n", name, name1);
		city1=rb_search(root, name);
		city2=rb_search(root, name1);
		if(city1==nil || city2==nil) printf("Unknown\n");
		else{
			distance=(long)(greatcircledistance(city1->latitude, city1->longitude, city2->latitude, city2->longitude)+0.5);
			printf("%ld km\n", distance);
		}
	}
	
	rb_clear(root);
	free(nil);
	return 0;
}

/* Great Circle Distance Functions */

double greatcircledistance(double lat1, double long1, double lat2, double long2){
	double dellat=lat2-lat1, dellong=long2-long1;
	double x=cos(lat2)*sin(dellong);
	double y=cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(dellong);
	double z=sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(dellong);
	
	x=x*x;
	y=y*y;
	return RADIUS*atan2(sqrt(x+y),z);
}

double degtorad(double degree){
	double rad=degree*PI/180;
	return rad;
}

/* Red Black Tree Functions */

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

node* rb_create(char *x, double latitude, double longitude){
    node *pn=(node*) malloc(sizeof(node));
    if(!pn) return 0;

    strcpy(pn->key,x);
    pn->color=BLACK;
    pn->latitude=degtorad(latitude);
    pn->longitude=degtorad(longitude);
    pn->left=pn->right=pn->parent=nil;
    return pn;
}

node *rb_search(node *ptr, char *k){
	node *x=ptr;
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

void rb_clear(node *ptr){
	node *x=ptr, *y;

	if(ptr==0 || ptr==nil) return;
	rb_clear(x->left);
	y=x;
	x=x->right;
	free(y);
	rb_clear(x);
}

void rb_insert(node *root, char *a, double latitude, double longitude){
    node *y=nil, *x=root, *z;
    int cond;
    void insert_case1(node *n);

    while(x!=nil){
        y=x;
        cond=strcmp(a, x->key);
        if(cond<0) x=x->left;
        else if(cond>0) x=x->right;
        else return;
    }

    z=rb_create(a, latitude, longitude);
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
	return;
}

void insert_case1(node *n){
	if (n->parent == nil)
		n->color = BLACK;
	else
		insert_case2(n);
}

void insert_case2(node *n){
	if (n->parent->color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(n);
}

void insert_case3(node *n){
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
