#include<stdio.h>
#include<stdlib.h>
#define MAX 1000010
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct t_node{
    long value;
    struct t_node *next;
}node;
typedef struct{
    node* adj;
}adj;

adj matrix[MAX+2];
char color[MAX+2], flag;
node *head;

node *ll_new(long x){
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

node *init_list(long x){
	node *ptr=ll_new(x);
	if(ptr) return ptr;
	return 0;
}

void output_list(node *head){
	node *pn;
	if(head==0 || head->next==0) return;
	for(pn=head;pn->next!=0;){
		printf("%ld\n", pn->next->value);
		pn=pn->next;
	}
}

int clear_list(node *head){
	node *pn, *ptr;
	if(head==0) return 0;
    for(pn=head;pn!=0;){
        ptr=pn;
        pn=pn->next;
        ll_delete(ptr);
    }
	return 1;
}

void init(long n){
    long i;
    
    for(i=1;i<=n;i++) matrix[i].adj=ll_new(0), color[i]=WHITE;
}

void dfsvisit(long u){
    long i, v;
    node *pn;
    
    color[u]=GRAY;
    for(pn=matrix[u].adj->next;pn!=0;pn=pn->next){
        v=pn->value;
        if(color[v]==WHITE) dfsvisit(v);
        else if(color[v]==GRAY){
            flag=0;
            return;
        }
    }
    
    color[u]=BLACK;
    ll_push_front(head, ll_new(u));
}

int main(){
    long n, m;
    long i, x, y;
    
    while(scanf("%ld%ld", &n, &m)!=EOF){
        if(m==0 && n==0) break;
        init(n);
        head=init_list(n);
        for(i=0;i<m;i++){
            scanf("%ld%ld", &x, &y);
            ll_push_front(matrix[x].adj, ll_new(y));
        }
        
        flag=1;
        for(i=1;i<=n;i++) if(color[i]==WHITE) dfsvisit(i);
        if(flag) output_list(head);
        else printf("IMPOSSIBLE\n");
        clear_list(head);
        for(i=1;i<=n;i++) clear_list(matrix[i].adj);
    }
    
    return 0;
}
