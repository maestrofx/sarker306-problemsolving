#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define RED 'r'
#define BLACK 'b'

#define MAXNODE 55
#define MAXQUEUE 100000
#define WHITE 0
#define GRAY 1

/* Red Black Tree formation  */

struct node{
    char key[10];
    int value;
    char color;
    struct node *left, *right, *parent;
};

struct node *nil, *root;
int count;

struct node *grandparent(struct node *n)
{
	if ((n != nil) && (n->parent != nil))
		return n->parent->parent;
	else
		return nil;
}

struct node *uncle(struct node *n)
{
	struct node *g = grandparent(n);
	if (g == nil)
		return nil; /* No grandparent means no uncle */
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

struct node *sibling(struct node *n)
{
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

struct node* rb_create(char *x, int ans)
{
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

int rb_insert(struct node *root, char *x, int val){
	int cond, ans=-1;
	struct node *pn=0;
	void insert_case1(struct node *);

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
	printf("%s - %d\n", x->key, x->value);
	rb_walk(x->right);
}

/********************************************************/

/* Graph traversal  */

char nodes[MAXNODE+3];
int dis[MAXNODE+3];
char adj[MAXNODE+3][MAXNODE+3];

int queue[MAXQUEUE+3];
int head, tail;

void enqueue(int x){
    queue[tail]=x;
    if(tail==MAXQUEUE) tail=0;
    else tail++;
}

int dequeue(void){
    int x=queue[head];
    if(head==MAXQUEUE) head=0;
    else head++;
    return x;
}

void initmatrix(void){
    int i, j;
    
    for(i=0;i<=count;i++){
        for(j=0;adj[i][j];j++){
            adj[i][j]=0;
        }
    }
}

void initbfs(void){
    int i, j;
    
    head=0, tail=0;
    for(i=0;i<=count;i++){
        dis[i]=9999;
        nodes[i]=WHITE;
    }
}

int bfs(int s, int maxstep){
    int i, unreach=0, u, v;
    
    if(s==-1) return count-1;
    initbfs();
    nodes[s]=GRAY;
    dis[s]=0;
    enqueue(s);
    
    while(head!=tail){
        u=dequeue();
        
        for(i=1;adj[u][i];i++){
            v=adj[u][i];
            if(nodes[v]==WHITE){
                nodes[v]=GRAY;
                dis[v]=dis[u]+1;
                enqueue(v);
            }
        }
        
        nodes[u]=BLACK;
        if(dis[u]==maxstep) break;
    }
    
    for(i=1;i<count;i++){
        if(dis[i]>maxstep) unreach++;
    }
    
    return unreach;
}

/********************************************************/

void zero_cancel(char *A)
{
	int zero=0, i, j;
	while(A[zero]=='0') zero++;
	if(zero)
	{
		for(i=zero,j=0;A[i-1]!='\0';i++, j++) A[j]=A[i];
	}
	return;
}

int main(){
	struct node *pn;
	long n, ans1, ans2, i, j, cases=0;
	int TTL;
	char node1[10], node2[10];

	nil=(struct node*)malloc(sizeof(struct node));
	nil->key[0]=0;
	nil->left=nil->right=0;
	nil->parent=0;

    while(scanf("%ld", &n)!=EOF){
        if(n==0) break;
        
    	root=nil;
        count=1;
        scanf("%s%s", node1,node2);
        zero_cancel(node1), zero_cancel(node2);
		if(root==nil){
			root=rb_create(node1, 1);
			ans1=1;
		}
		else ans1=rb_insert(root, node1, count);
		ans2=rb_insert(root, node2, count);
		if(ans1!=ans2){
            adj[ans1][adj[ans1][0]+1]=ans2;
            adj[ans1][0]++;
            adj[ans2][adj[ans2][0]+1]=ans1;
            adj[ans2][0]++;
        }
    	for(i=1;i<n;i++){
            scanf("%s%s", node1,node2);
            zero_cancel(node1), zero_cancel(node2);
            ans1=rb_insert(root, node1, count);
    		ans2=rb_insert(root, node2, count);
    		if(ans1!=ans2){
                adj[ans1][adj[ans1][0]+1]=ans2;
                adj[ans1][0]++;
                adj[ans2][adj[ans2][0]+1]=ans1;
                adj[ans2][0]++;
            }
    	}

        /*rb_walk(root);
        for(i=0;i<count;i++){
            for(j=0;adj[i][j];j++) printf("%3d", adj[i][j]);
            puts("");
        }*/
        
    	while(scanf("%s%d", node1, &TTL)!=EOF){
            ans1=-1;
            pn=0;
            zero_cancel(node1);
            if(node1[0]==0 && TTL==0) break;
            pn=rb_search(root, node1);
            if(pn && pn!=nil) ans1=pn->value;
            printf("Case %d: ", ++cases);
            printf("%d ",bfs(ans1, TTL));
            printf("nodes not reachable from node %s with TTL = %d.\n", node1, TTL);
        }

    	rb_clear(root);
        initmatrix();
    }

	free(nil);
	return 0;
}
