#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 18
#define RED 'r'
#define BLACK 'b'

typedef struct llnode{
    char word[LENGTH];
    struct llnode *next;
}llnode;

typedef struct trnode{
    char proto[LENGTH], color;
    llnode *head;
    struct trnode *left, *right, *parent;
}trnode;

typedef struct tree{
    trnode *root;
}tree;

trnode *nil;

llnode *ll_new(char *x){
    llnode *ptr = (llnode*)malloc(sizeof(llnode));

    if(!ptr) return 0;

    strcpy(ptr->word, x);
	ptr->next = 0;
    return ptr;
}

llnode *ll_push_front(llnode *pred, llnode *ptr){
    if(pred == 0 || ptr == 0) return 0;

    ptr->next = pred->next;
    pred->next = ptr;

    return ptr;
}

int ll_delete(llnode *ptr){
    if(!ptr) return 0;

    free(ptr);
    return 1 ;
}

void ll_clear(llnode *head){
	llnode *pn, *ptr;

	if(head == 0) return ;

    for( pn = head ; pn != 0 ; ){
        ptr = pn;
        pn = pn->next;
        if(!ll_delete(ptr)) return ;
    }
}

void ll_walk(llnode *head){
    for( head = head->next ;  head ; head = head->next) printf(" %s", head->word);
    puts("");
}

trnode *minimum(trnode *n){
	while(n->left != nil) n = n->left;

	return n;
}

trnode *successor(trnode *n){
	trnode *y;

	if(n->right != nil) return minimum(n->right);
	y = n->parent;
	while(y != nil && n == y->right) n = y, y = y->parent;
	return y;
}

void rotate_left(tree *Tree, trnode *x){
    trnode *y = x->right;

    if(x == nil || y == nil) return;
    x->right = y->left;
    if(y->left != nil) y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == nil) Tree->root = y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotate_right(tree *Tree, trnode *x){
    trnode *y = x->left;

    if(x == nil || y == nil) return;
    x->left = y->right;
    if(y->right != nil) y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == nil) Tree->root = y;
    else if(x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

trnode* rb_create(char *x){
    trnode *pn=(trnode*) malloc(sizeof(trnode));
    if(!pn) return 0;

    strcpy(pn->proto, x);
    pn->head = ll_new("");
    pn->color = BLACK;
    pn->left = pn->right = pn->parent = nil;
    return pn;
}

trnode *rb_search(trnode *ptr, char *k){
	trnode *x = ptr;
	int res;

	if(x == nil) return nil;

	while(x != nil){
	    res = strcmp(k, x->proto);
		if(res < 0) x = x->left;  /* compare */
		else if( res == 0 ) break;
		else x = x->right;
	}

	return x;
}

void rb_walk(trnode *x){
	if(x == nil ) return;

	rb_walk(x->left);
	printf("%s ->", x->proto);
	ll_walk(x->head);
	rb_walk(x->right);
}

void rb_clear(trnode *ptr){
	trnode *x = ptr, *y;

	if(ptr == nil) return;
	rb_clear(x->left);
	y = x;
	x = x->right;
	ll_clear(y->head);
	free(y);
	rb_clear(x);
}

void rb_insert_fixup(tree *Tree, trnode *z){
    trnode *y, *x;

    while(z->parent->color == RED){
		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right;

			if(y->color == RED){
				z->parent->color = y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else{
				if(z == z->parent->right){
					z = z->parent;
					rotate_left(Tree, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rotate_right(Tree, z->parent->parent);
			}
		}
		else{
			y = z->parent->parent->left;

			if(y->color == RED){
				z->parent->color = y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else{
				if(z == z->parent->left){
					z = z->parent;
					rotate_right(Tree, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rotate_left(Tree, z->parent->parent);
			}
		}
    }

    Tree->root->color = BLACK;
}

trnode* rb_insert(tree *Tree, char *proto, char *word){
    trnode *y = nil, *x = Tree->root, *z;
    int res;

    while(x != nil){
        y = x;
        res = strcmp(proto, x->proto);
        if(res == 0){
            ll_push_front(x->head, ll_new(word));
            return x;
        }
        if(res < 0) x = x->left;   /* compare */
        else x = x->right;
    }

    z = rb_create(proto);
    z->parent = y;
    if(y == nil) Tree->root = z;
    else if(strcmp(z->proto, y->proto) < 0) y->left = z;  /* compare */
    else y->right = z;

    z->right = z->left = nil;
    z->color = RED;
    ll_push_front(z->head, ll_new(word));

    rb_insert_fixup(Tree, z);
    nil->left = nil->right = nil->parent = 0;
    return z;
}

tree dictionary[LENGTH+1][28];

void dictionary_init(){
    int i, j;

    for( i = 0 ; i < LENGTH ; i++ )
        for( j = 0 ; j <= 26 ; j++ )
            dictionary[i][j].root = nil;
}

void dictionary_walk(){
    int i, j;

    for( i = 0 ; i < LENGTH ; i++ )
        for( j = 0 ; j <= 26 ; j++ )
            if( dictionary[i][j].root != nil){
                rb_walk(dictionary[i][j].root);
            }
}

void dictionary_clear(){
    int i, j;

    for( i = 0 ; i < LENGTH ; i++ )
        for( j = 0 ; j <= 26 ; j++ )
            if( dictionary[i][j].root != nil){
                rb_clear(dictionary[i][j].root);
                dictionary[i][j].root = nil;
            }
}

char *prototype(char *to, char *from){
    char val[26], *ptr = to, x, y = 'a';

    for( x = 0 ; x < 26 ; x++ ) val[x] = 0;
    while( *from ){
        x = *from++ - 'a';
        if( val[x] == 0 )  val[x] = y++;
        *to++ = val[x];
    }

    *to = 0;
    return ptr;
}

char diff_chars(char *str){
    char val[26], i, count = 0;

    for(i = 0 ; i < 26 ; i++) val[i] = 0;
    while( *str ){
        i = *str++ - 'a';
        if(val[i] == 0) val[i] = ++count;
    }

    return count;
}

typedef struct{
    char word[LENGTH], key, length;
}pos;

char protos[80][LENGTH];

int pos_cmp(const void *one, const void *two){
    return (*(pos**)two)->key - (*(pos**)one)->key;
}

void parse(pos *arr, pos **ptr2arr, char *sntnc, int *n){
    int i = 0, flag = 0;

    for( ; ; sntnc++ ){
        if( isalpha(*sntnc) ) arr[*n].word[i++] = *sntnc, flag = 1;
        else{
            if( flag ){
                flag = 0;
                arr[*n].word[i] = 0;
                arr[*n].key = diff_chars(arr[*n].word);
                arr[*n].length = i;
                ptr2arr[*n] = &arr[*n];
                *n = *n + 1;
                i = 0;
            }
        }

        if( *sntnc == 0 ) break;
    }

    qsort( ptr2arr, *n, sizeof(pos*), pos_cmp);
    for( i = 0 ; i < *n ; i++ ){
        prototype(protos[i], ptr2arr[i]->word);
        /*printf(" # %s , %d, %s\n", ptr2arr[i]->word, ptr2arr[i]->key, protos[i]);*/
    }
}

int found_sol;

void backtrack(pos **ptr2ew, char *used, char *val, char *final, int index, int n){
    trnode *ptr;
    llnode *ptr2word;
    int i;
    char tmp[27], tmpused[27], x;

    if( index == n ){
        found_sol = 1;
        for( i = 0 ; i < 26 ; i++ )final[i] = val[i];
        return;
    }

    if( found_sol ) return;

    /*rb_walk(dictionary[ptr2ew[index]->length][ptr2ew[index]->key].root);*/
    ptr = rb_search(dictionary[ptr2ew[index]->length][ptr2ew[index]->key].root, protos[index]);
    if( ptr == nil ){
        /*printf(" %s with proto %s, key %d, length %d not found!\n",
            ptr2ew[index]->word, protos[index], ptr2ew[index]->key, ptr2ew[index]->length);*/
        found_sol = -1;
        return;
    }

    for( ptr2word = ptr->head->next ; ptr2word && found_sol == 0; ptr2word = ptr2word->next ){
        for( i = 0 ; i < 27 ; i++ ) tmp[i] = val[i], tmpused[i] = used[i];
        for( i = 0 ; ptr2ew[index]->word[i] ; i++ ){
            x = ptr2ew[index]->word[i] - 'a';
            if( val[x] != 0 ){
                if( val[x] != ptr2word->word[i] ) break;
            }
            else if( used[ptr2word->word[i] - 'a'] ) break;
            else val[x] = ptr2word->word[i], used[ptr2word->word[i] - 'a'] = 1;
        }

        if( ptr2ew[index]->word[i] == 0 ){
            /*printf("In searching for %s : %s\n", ptr2ew[index]->word, ptr2word->word);*/
            backtrack(ptr2ew, used, val, final, index + 1, n);
        }

        for( i = 0 ; i < 27 ; i++ ) val[i] = tmp[i], used[i] = tmpused[i];
    }
}

void decode(char *a, pos *encoded, pos **ptr2ew, int n){
    int i;
    char val[27], final[27], used[27];

    n = found_sol = 0;
    for( i = 0 ; i < 27 ; i++ ) val[i] = used[i] = 0;
    parse(encoded, ptr2ew, a, &n);

    backtrack(ptr2ew, used, val, final, 0, n);
    if(found_sol < 1){
        for( i = 0 ; a[i] ; i++ ) putchar( isalpha(a[i]) ? '*' : a[i]);
    }
    else {
        for( i = 0 ; a[i] ; i++ ) putchar( isalpha(a[i]) ? final[a[i] - 'a'] : a[i]);
    }

    puts("");
}

int main(){
    char a[100], b[100];
    int num_words;
    pos encoded_words[80], *ptr2ew[80];

    nil = (trnode*)malloc(sizeof(trnode));
    nil->left = nil->right = nil->parent = 0;

    while(scanf("%d", &num_words) != EOF){
        dictionary_init();
        while(num_words--){
            scanf("%s", a);
            rb_insert(&dictionary[strlen(a)][diff_chars(a)], prototype(b, a), a);
        }
        /*dictionary_walk();*/
        getchar();

        while(gets(a)) decode(a, encoded_words, ptr2ew, num_words);
        dictionary_clear();
    }

    free(nil);
    return 0;
}
