#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXWORD 250000
#define HMM 15
#define WORDSIZE 17
#define SIZE 1<<HMM

#define RED 'r'
#define BLACK 'b'

struct node{
    char word[WORDSIZE];
    long index;
    char color;
    struct node *left, *right, *parent;
};

typedef struct node node;
typedef struct tree{
    node *root;
}tree;

node *nil;
tree array[WORDSIZE][SIZE+5];

long function(const char *a){
    unsigned long x=0;

    for(;*a++;){
        x=(x<<5)+x+*a;
    }

    x=((x>>HMM)^(x&(~(-1<<HMM))))& (~(-1<<HMM));

    return x;
}

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

node* rb_create(char *word, long index){
    node *pn=(node*) malloc(sizeof(node));
    if(!pn) return 0;

    strcpy(pn->word, word);  /* initalize */
    pn->color=BLACK;
    pn->index = index;
    pn->left=pn->right=pn->parent=nil;
    return pn;
}

long rb_search(node *ptr, char *word){
	node *x=ptr;
	char cond;

	if(x==nil) return -1;

	while(x!=nil){
	    cond=strcmp(word, x->word);
	    if(cond==0) break;
		if(cond<0) x=x->left;  /* compare */
		else x=x->right;
	}

	return x->index;
}

void rb_walk(node *x){
    int left_h, right_h;
	if(x==nil ) return;

	rb_walk(x->left);
	printf("%s - %ld - %c\n", x->word, x->index, x->color);
	rb_walk(x->right);
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

int rb_insert(tree *Tree, char *word, long index){
    node *y=nil, *x=Tree->root, *z;
    int cond;

    while(x!=nil){
        y=x;
        cond=strcmp(word, x->word);
        if(cond==0) return x->index;    /* if already in tree ? */
        if(cond<0) x=x->left;   /* compare */
        else x=x->right;
    }

    z=rb_create(word, index);
    z->parent=y;
    if(y==nil) Tree->root=z;
    else if(strcmp(z->word, y->word)<0) y->left=z;  /* compare */
    else y->right=z;

    z->right=z->left=nil;
    z->color=RED;

    rb_insert_fixup(Tree, z);
    nil->left=nil->right=nil->parent=0;

    return index;
}

void init_hash_table(void){
    int i, j;

    for(i=0;i<=SIZE;i++){
        for ( j = 0 ; j < WORDSIZE ; j++ )
        array[j][i].root=nil;
    }
}

void reset_hash_table(void){
    int i, j;

    for(i=0;i<=SIZE;i++){
        for ( j = 0 ; j < WORDSIZE ; j++ )
        rb_clear(array[j][i].root);
    }
}

long hash_insert(char *a, long index){
    long x;
    node *pn;

    if(a[0]==0) return -1;
    x=function(a);
    return rb_insert(&array[strlen(a)][x], a, index);
}

long hash_find(char *a){
    long x;

    x=function(a);
    return rb_search(array[strlen(a)][x].root, a);
}

void hash_walk(void){
    long int i, j;

    for(i=0;i<=SIZE;i++){
        for ( j = 0 ; j < WORDSIZE ; j++ ){
            if(array[j][i].root == nil) continue;
            printf("VALUE : %ld\n", i);
            rb_walk(array[j][i].root);
            printf("\n");
        }
    }
}

long wordCnt;
char words[MAXWORD][WORDSIZE];
long parent[MAXWORD];
long queueInd[MAXWORD];
long head, tail;

void printPath(long index){
    if ( parent[index] != index ) printPath(parent[index]);
    printf("%s\n", words[index]);
}

int bfs( char *from, char *to ){
    long i, targetInd, nowInd, v;
    char j;
    head = tail = 0;
    char tmpWord[WORDSIZE], tmpLetter;
    
    if ( strlen(from) != strlen(to) ) return 0;
    targetInd = hash_find(to);
    if ( targetInd == -1 ) return 0;
    
    nowInd = hash_find(from);
    if ( nowInd == -1 ) return 0;
    queueInd[tail++] = nowInd ;
    
    for ( i = 0 ; i < wordCnt ; i++ ) parent[i] = -1;
    parent[nowInd] = nowInd;
    
    while ( head != tail ){
        nowInd = queueInd[head++];
        strcpy(tmpWord, words[nowInd]);
        
        if ( nowInd == targetInd ){
            printPath(targetInd);
            return 1;
        }
        for ( i = 0 ; tmpWord[i] ; i++ ){
            tmpLetter = tmpWord[i];
            for ( j = 'a' ; j <= 'z' ; j++ ){
                if ( j == tmpLetter ) continue;
                tmpWord[i] = j;
                v = hash_find(tmpWord);
                if ( v != -1 && parent[v] == -1 ){
                    parent[v] = nowInd;
                    queueInd[tail++] = v;
                }   
            }
            
            tmpWord[i] = tmpLetter;
        }
    }
    
    return 0;
}

int main(){
    int kase = 0;
    char word[WORDSIZE], target[WORDSIZE];
    nil=rb_create("", -1);
    init_hash_table();
    
    while ( gets(words[wordCnt]) ){
        if ( words[wordCnt][0] == 0 ) break;
        if ( wordCnt == hash_insert(words[wordCnt], wordCnt)) wordCnt++;
    }
    
    while ( scanf("%s%s", word, target) != EOF ){
        if ( kase++ ) puts("");
        if ( bfs(word, target) == 0 ) puts("No solution.");
    }
    
    reset_hash_table();
    free(nil);
    return 0;
}
