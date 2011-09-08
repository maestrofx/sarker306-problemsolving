#include<stdio.h>
#include<stdlib.h>
#define MAX 102
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct{
    int adj[MAX+2], count;
}adj;
typedef struct t_node{
    int value;
    struct t_node *next;
}node;

adj matrix[MAX+2];
char color[MAX+2];
node *head;

node *ll_new(int x){
    node *ptr=(node*)malloc(sizeof(node));
    
    if(!ptr) return 0;
    ptr->value=x;
	ptr->next=0;
    return ptr;
}

node *ll_push_front(node *pred, node *ptr) {
    if(pred==0 || ptr==0) return 0;
    
    ptr->next=pred->next;
    pred->next=ptr;
    return ptr;
}   

int ll_delete(node *ptr){
    if(!ptr) return 0;
    free(ptr);
    return 1 ;
}

node *init_list(int x){
	node *ptr=ll_new(x);
	if(ptr) return ptr;
	return 0;
}

void output_list(node *head){
	node *pn;
	if(head==0 || head->next==0) return;
	for(pn=head;pn->next!=0;){
		printf("%d ", pn->next->value);
		pn=pn->next;
	}
	printf("\n");
}

int clear_list(node *head){
	node *pn, *ptr;
	if(head==0) return 0;
    for(pn=head;pn!=0;){
        /*printf("%d ", pn->value);*/
        ptr=pn;
        pn=pn->next;
        if(ll_delete(ptr))/*printf("Freed!   ")*/;
		else return 0;
    }
	return 1;
}

void init(int n){
    int i;
    
    for(i=0;i<=n;i++) matrix[i].count=0, color[i]=WHITE;
}

void print_graph(int n){
    int i, j;
    
    for(i=1;i<=n;i++){
        printf("%4d :", i);
        for(j=0;j<matrix[i].count;j++) printf(" %4d", matrix[i].adj[j]);
        printf("\n\n");
    }
}

void dfsvisit(int u){
    int i, v;
    
    color[u]=GRAY;
    for(i=0;i<matrix[u].count;i++){
        v=matrix[u].adj[i];
        if(color[v]==WHITE) dfsvisit(v);
    }
    
    color[u]=BLACK;
    ll_push_front(head, ll_new(u));
}

int main(){
    int n, m;
    int i, x, y;
    
    while(scanf("%d%d", &n, &m)!=EOF){
        if(m==0 && n==0) break;
        init(n);
        head=init_list(n);
        for(i=0;i<m;i++){
            scanf("%d%d", &x, &y);
            matrix[x].adj[matrix[x].count++]=y;
        }
        
        /*print_graph(n);*/
        for(i=1;i<=n;i++) if(color[i]==WHITE) dfsvisit(i);
        output_list(head);
        clear_list(head);
    }
    
    return 0;
}
