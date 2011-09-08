#include<stdio.h>
#include<stdlib.h>
#define Xd "%I64d"

typedef long long llong;

typedef struct t_node{
	llong key;
    struct t_node *parent;
	struct t_node *left;
   	struct t_node *right;
}node;
node *root;

node *bst_create(llong x){
	node *pn=(node*)malloc(sizeof(node));
	if(!pn) return 0;

	pn->left=pn->right=0;
	pn->key=x;

	return pn;
}

node *bst_minimum(node *ptr){
	node *x=ptr;

    if(!x) return 0;

	while(x->left) x=x->left;
	return x;
}

node *bst_successor(node *ptr){
	node *x=ptr, *y;

	if(x->right)
	   return bst_minimum(x->right);
	y=x->parent;
	while(y && x==y->right){
        x=y;
        y=y->parent;
    }

    return y;
}

int bst_insert(node *root, llong key){
	node *y, *x=root, *z;

	if(root==0 ) return;

	while(x){
		y=x;
		if(key==x->key) return 1;
		else if(key<x->key) x=x->left;
		else x=x->right;
	}
	z=bst_create(key);
	z->parent=y;
	if(!y) root=z;						/*tree root was empty*/
	else if(z->key<y->key) y->left=z;
	else y->right=z;
	
	return 0;
}

node *bst_remove(node *root, node *z){
	node *y, *x;

	if(z->left==0 && z->right==0)  y=z; /*z has no children*/
	else y=bst_successor(z);

	if(y->left) x=y->left;
	else x=y->right;

	if(x) x->parent=y->parent;
	if(y->parent==0) root=x;
	else if(y==y->parent->left) y->parent->left=x;
	else y->parent->right=x;

	if(y!=z) z->key=y->key;	/*not deleting z, but copying the keys of y into z*/

	return 0;
}

node *bst_search(node *ptr, llong k){
	node *x=ptr;

	while(x && k!=x->key){
		if(k<x->key) x=x->left;
		else x=x->right;
	}

	return x;
}

void bst_walk(node *x){
	if(x==0) return;

	bst_walk(x->left);
	printf("%d ", x->key);
	bst_walk(x->right);
}

void bst_clear(node *ptr){
	node *x=ptr, *y;

	if(ptr==0) return;
	bst_clear(x->left);
	y=x;
	x=x->right;
	/*printf("%d deleted!\n", y->key);*/
	free(y);
	bst_clear(x);
}

int IsHappy(llong n){
	llong sum, digit;
	
	while(1){
		sum=0;
		while(n){
			digit=n%10;
			sum+=digit*digit;
			n/=10;
		}
		/*printf(Xd, sum), putchar(' ');*/
		if(sum==1){
			bst_clear(root);
			return 1;
		}
		else if(bst_insert(root, sum)){
			bst_clear(root);
			return 0;
		}
		n=sum;
	}
}

int main(){
	llong x;
	int test, i;
	
	scanf("%d", &test);
	for(i=1;i<=test;i++){
		scanf(Xd, &x);
		printf("Case #%d: ", i);
		root=bst_create(x);
		printf(Xd, x);
		printf(" is %sappy number.\n", (IsHappy(x))? "a H":"an Unh");
	}
	
	return 0;
}
