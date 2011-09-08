#include<stdio.h>
#include<string.h>

#define tolower(x) ((x) >= 'A' && (x) <= 'Z') ? (x)+32 : (x)
#define alpha(x) (((x)>='A' && (x) <='Z') || ((x)>='a' && (x) <='z')) ? 1 : 0

typedef struct t_node{
	char key[205];
    struct t_node *parent;
	struct t_node *left;
   	struct t_node *right;
}node;

node *root;

node *bst_create(char *x){
	node *pn=(node*)malloc(sizeof(node));
	if(!pn) return 0;

	pn->left=pn->right=0;
	strcpy(pn->key,x);

	return pn;
}

void bst_insert(node *root, node *z){
	node *y, *x=root;

	if(root==0 || z==0) return;

	while(x){
		y=x;
		if(strcmp(z->key,x->key)<0)
			x=x->left;
		else
			x=x->right;
	}

	z->parent=y;
	if(!y)
		root=z;						/*tree root was empty*/
	else if(strcmp(z->key,y->key)<0)
		y->left=z;
	else
		y->right=z;
}

node *bst_search(node *ptr, char *k){
	node *x=ptr;

	while(x && strcmp(k,x->key)){
		if(strcmp(k,x->key)<0)
			x=x->left;
		else x=x->right;
	}

	return x;
}

void bst_walk(node *x){
	if(x==0) return;

	bst_walk(x->left);
	printf("%s\n", x->key);
	bst_walk(x->right);
}

void bst_clear(node *ptr){
	node *x=ptr, *y;

	if(ptr==0) return;
	bst_clear(x->left);
	y=x;
	x=x->right;
	free(y);
	bst_clear(x);
}

int main()
{
    char array[205];
    char now, prev=0;
    int i=0;
    node *pn;
    
    /*while((now=getchar())!=EOF){
        now=tolower(now);
        if(alpha(now)){
            if(prev=='-')array[i++]=prev;
            array[i++]=now;
        }
        else if(now!='-' && prev!='-'){
            array[i]=0;
            if(i){
                if(!root){
                    root=bst_create(array);
                }
                else{
                    pn=bst_search(root, array);
                    if(!pn) bst_insert(root, bst_create(array));
                }
            }
            i=0;
        }

        prev=now;
    }*//*for 11062 */
    /*for 10815 */
    while((now=getchar())!=EOF){
        now=tolower(now);
        if(alpha(now)){
            array[i++]=now;
        }
        else{
            array[i]=0;
            if(i){
                if(!root){
                    root=bst_create(array);
                }
                else{
                    pn=bst_search(root, array);
                    if(!pn) bst_insert(root, bst_create(array));
                }
            }
            i=0;
        }
    }  
    
    bst_walk(root);
    bst_clear(root);
    
    while(getchar()!='q');
    return 0;
}
