#include<stdio.h>
#include<stdlib.h>

#define MAXEDGE 79805
#define MAXPOINT 405
#define WORDSIZE 15

#define SIZE 128

typedef struct{
    long u, v, cost;
}edge;

edge edges[MAXEDGE];
long rank[MAXPOINT];
long parent[MAXPOINT];

void init(long N){
	long i;
	for(i=0;i<=N;i++) parent[i]=i, rank[i]=0;
}

int cmp(const void *x,const void *y){
    edge *a=(edge *)x;
    edge *b=(edge *)y;
    if(a->cost-b->cost) return (a->cost>b->cost)?1:-1;
	return 0;
}

long find(long x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

void link(long x,long y){
    if(rank[x]>rank[y]) parent[y]=x;
    else{
		if(rank[x]==rank[y]) rank[y]++;
		parent[x]=y;
    }
}

long mst(long N, long M){
    long i, j, x, y, edge_tree=0, cost_tree=0;
    
    qsort(edges, M, sizeof(edge), cmp);
	for(i=0;i<M;i++){
        if(edge_tree==N-1) break;
        x=find(edges[i].u), y=find(edges[i].v);
        if(x!=y){
            link(x,y);
            edge_tree++, cost_tree+=edges[i].cost;
        }
    }
	
	if(edge_tree==N-1) printf("%ld\n", cost_tree);
	else puts("Impossible");
	return cost_tree;
}

typedef struct t_node{
    char word[WORDSIZE];
    long key;
    struct t_node *next, *prev;
}node;

node *array[SIZE+5];

long function(char *a){
    unsigned long x=0;
    
    for(;*a++;){
        x=(x<<5)+x+*a;
    }
    
    x=((x>>20)^(x&(~(-1<<20))))& (~(-1<<20));
    
    return x%SIZE;
}

node *ll_new(char *a, long x){
    node *ptr=(node*)malloc(sizeof(node));
    
    if(!ptr) return 0;
    
    strcpy(ptr->word, a);
    ptr->key=x;
	ptr->next=0;
	ptr->prev=0;
    return ptr;
}

node *ll_push(node *pred, node *ptr){
    if(pred==0 || ptr==0) return 0;
    
    ptr->next=pred->next;
    ptr->prev=pred;
    pred->next=ptr;
	if(ptr->next)ptr->next->prev=ptr;
    
    return ptr;
} 

int ll_delete(node *ptr){
    if(!ptr) return 0;
    
    free(ptr);
    return 1 ;
}

void ll_clear(node *head){ 
	node *pn, *ptr;

	if(head==0) return ;

    for(pn=head;pn!=0;){
        ptr=pn;
        pn=pn->next;
        if(!ll_delete(ptr)) return ;
    }

	return ;
}

node *ll_vfind(node *pred, char *a){
    node *pn;
    
    if(pred==0||pred->next==0) return 0;
    
    for(pn=pred;pn->next;pn=pn->next){
        if(strcmp(pn->next->word, a)==0) return pn;
    }
    
    return 0;
}

void init_hash_table(void){
    int i;
    
    for(i=0;i<=SIZE;i++){
        array[i]=ll_new("", -1);
    }
}

void reset_hash_table(void){
    int i;
    
    for(i=0;i<=SIZE;i++){
        ll_clear(array[i]);
    }
}

long hash_insert(char *a, long value){
    long x;
    node *pn;
    
    if(a[0]==0) return -1;
    x=function(a);
    pn=ll_push(array[x], ll_new(a, value));
    if(!pn)return 0;
    else return 1;
}

long hash_find(char *a){
    long x;
    node *pn;
    
    x=function(a);
    pn=ll_vfind(array[x], a);
    if(pn) return pn->next->key;
}

void ll_walk(node *head)
{
	node *pn;

	if(head==0 || head->next==0) return;
	for(pn=head;pn->next!=0;)
	{
		printf(" (%s, %d)", pn->next->word, pn->next->key);
		pn=pn->next;
	}
	printf("\n");
}

void hash_walk(void){
    long int i;
    
    for(i=0;i<=SIZE;i++){
        if(array[i]->next==0) continue;
        printf("VALUE : %ld\n", i);
        ll_walk(array[i]);
        printf("\n");
    }
}

int main(){
    long n, m, i, u, v, w;
    char city[WORDSIZE];
    
    while(scanf("%ld%ld", &n, &m)!=EOF){
        if(n==0 && m==0) break;
        init(n);
        init_hash_table();
        for(i=0;i<n;i++){
            scanf("%s", city);
            hash_insert(city, i);
        }
        
        for(i=0;i<m;i++){
            scanf("%s", city);
            u=hash_find(city);
            scanf("%s", city);
            v=hash_find(city);
            scanf("%ld", &w);
            edges[i].cost=w, edges[i].u=u, edges[i].v=v;  
        }
        
        scanf("%s", city);
        mst(n, m);
        reset_hash_table();
    }
    
    return 0;
}
