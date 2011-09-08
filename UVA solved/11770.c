#include<stdio.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX 100005

typedef struct t_node{
    long value;
    struct t_node *next;
}node;
typedef struct{
    node* adj;
}adj;

adj matrix[MAX+2];
char color[MAX+2], dfscolor[MAX+2];
long queue[MAX*2+2], head, tail;
node *head1;

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

void initgraph(long n){
    long i;

    for(i=1;i<=n;i++) matrix[i].adj=ll_new(0), color[i]=dfscolor[i]=WHITE;
}

long pop(void){
    long x=queue[head];
    if(head==MAX*2) head=0;
    else head++;
    return x;
}

void push(long x){
    queue[tail]=x;
    if(tail==MAX*2) tail=0;
    else tail++;
}

void bfs(long source){
    long i, v, u;
    node *pn;

    head=tail=0;
    push(source);
    color[source]=GRAY;
    while(head!=tail){
        u=pop();
        for(pn=matrix[u].adj->next;pn;pn=pn->next){
            v=pn->value;
            if(color[v]==WHITE)  push(v), color[v]=GRAY;
        }

        color[u]=BLACK;
    }
}

void dfsvisit(long u){
    long i, v;
    node *pn;

    dfscolor[u]=GRAY;
    for(pn=matrix[u].adj->next;pn!=0;pn=pn->next){
        v=pn->value;
        if(dfscolor[v]==WHITE) dfsvisit(v);
    }

    dfscolor[u]=BLACK;
    ll_push_front(head1, ll_new(u));
}

int main(){
    long test, t, n, m, i, u, v, mustpush;
    node *pn;

    while(scanf("%ld", &test)!=EOF){
        for(t=1;t<=test;t++){
            scanf("%ld%ld", &n, &m);
            initgraph(n);
            head1=init_list(n);

            for(i=0;i<m;i++){
                scanf("%ld%ld", &u, &v);
                ll_push_front(matrix[u].adj, ll_new(v));
            }

            for(i=1;i<=n;i++){
                if(dfscolor[i]==WHITE) dfsvisit(i);
            }

            for(pn=head1->next, mustpush=0;pn; pn=pn->next){
                if(color[pn->value]==WHITE) bfs(pn->value), mustpush++;
            }

            printf("Case %ld: %ld\n", t, mustpush);
            clear_list(head1);
            for(i=1;i<=n;i++) clear_list(matrix[i].adj);
        }
    }

    return 0;
}
