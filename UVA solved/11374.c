#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct priorityQ{
    int queue[3005], size;
    int (*cmp)(int, int);
}pq;

int left(int ind){ return ind<<1 + 1 ; }
int right(int ind) { return (ind+1)<<1 ; }
int parent(int ind) { return (ind-1)>>1; }

int minHeapify( pq *queue, int ind ){
    int l, r, minInd;
    
    if ( ind >= queue->size ) return;
    l = left(ind), r = right(ind);
    if(l < queue->size && queue->cmp(l, ind) < 0)
        minInd = l;
    else minInd = ind;
    if(r < queue->size && queue->cmp(r, minInd) < 0)
        minInd = r;
        
    if ( minInd != ind ){
        l = queue->queue[minInd];
        queue->queue[minInd] = queue->queue[ind];
        queue->queue[ind] = l;
        minHeapify(queue, minInd);
    }
}

void buildMinHeap(pq *queue, int *initArr, int size, int (*cmp)(int, int)){
	int i;
	
	if ( initArr != 0 && size > 0 ){
        for ( i = 0 ; i < size ; i++ ) queue->queue[i] = initArr[i];
    }
    
    queue->size = size;
	queue->cmp = cmp;
	for(i = queue->size/2;i>=0;i--){
		minHeapify(queue, i);
	}
}

int heapExtractMin(pq *queue){
	int x;
	
	x = queue->queue[0];
	queue->queue[0] = queue->queue[queue->size - 1];
	queue->size--;
	minHeapify(queue, 0);
	return x;
}

int heapDecreaseKey(pq *queue, int key, int i){
	int x;
	
	queue->queue[i] = key;
	while(i){
		x=parent(i);
		if(queue->cmp(x, i) < 0) break;
		queue->queue[i]^=queue->queue[x]^=queue->queue[i]^=queue->queue[x];
		i=x;
	}
	return 0;
}

int minHeapInsert(pq *queue, int key){
	/* set something as INF so that queue->cmp( ANYTHING, queue->size ) returns POSITIVE */
	queue->size++;
	heapDecreaseKey(queue, key, queue->size-1);
}

/*******************************************************************/


typedef struct t_node{
    int key;
    long value;
    struct t_node *next, *prev;
}node;

typedef struct{
	int size;
	node *head, *tail;
}list;

typedef struct{
	int n;
	int *parent;
	list *adjacent;
}graph;

node *ll_new(int _key, long _val){
    node *ptr = (node*)malloc(sizeof(node));

    if(!ptr) return 0;
    ptr->key = _key;
    ptr->value = _val;
	ptr->next = ptr->prev = 0;
    return ptr;
}

node *ll_push_front(node *prev, node *ptr){
   if(prev == 0 || ptr == 0) return 0;

    ptr->next = prev->next;
    ptr->prev = prev;
    prev->next = ptr;
	if(ptr->next) ptr->next->prev = ptr;

    return ptr;
}

node *ll_push_back(node *next, node *ptr){
	if(next == 0 || ptr == 0) return 0;

	ptr->prev = next->prev;
	next->prev = ptr;
	ptr->next = next;
	if( ptr->prev ) ptr->prev->next = ptr;
	return ptr;
}

node *ll_delete(node *ptr){
	if(ptr == 0) return 0;

	if( ptr->next ) ptr->next->prev = ptr->prev;
	if( ptr->prev ) ptr->prev->next = ptr->next;
	return ptr;
}

void ll_clear(node *head){
	node *pn, *ptr;

	if(head == 0) return ;
    for(pn = head ; pn != 0 ; ){
        ptr = pn;
        pn=pn->next;
        free(ptr);
    }
}

void list_init(list *lst){
	lst->head = ll_new(INT_MAX, INT_MAX);
	lst->tail = ll_new(INT_MAX, INT_MAX);
	lst->head->next = lst->tail;
	lst->tail->prev = lst->head;
}

void list_show(list *lst){
	node *ptr;

	for( ptr = lst->head->next ; ptr != lst->tail ; ptr = ptr->next)
        printf(" (%d, %ld)", ptr->key, ptr->value);
	puts("");
}

void list_push_back(list *lst, int _key, long _val){
	ll_push_back(lst->tail, ll_new(_key, _val));
}

void list_push_front(list *lst,  int _key, long _val){
	ll_push_front(lst->head, ll_new(_key, _val));
}
/*
long list_pop_front(list *lst){
    node *ptr = ll_delete(lst->head->next);
    long x = ptr->value;
    free(ptr);
    return x;
}
*/
void list_clear(list *lst){
	ll_clear(lst->head);
}

long list_empty(list *lst){
    return (lst->head->next == lst->tail) ? 1 : 0;
}

void graph_init(graph *g, int n){
	int i;

	g->n = n;
	g->adjacent = (list*)malloc(sizeof(list) * n);
	for( i = 0 ; i < n ; i++ ){
	    list_init(&g->adjacent[i]);
	}
}

void graph_show(graph *g){
	int i;

	puts("***********************");
	printf("Vertices : %d\n", g->n);
	for( i = 0 ; i < g->n ; i++ ){
		printf("Vertex %d :", i);
		list_show(g->adjacent + i);
	}

	puts("**********************");
}

void graph_add_edge(graph *g, int u, int v, long w){
	list_push_back(&g->adjacent[u], v, w);
	list_push_back(&g->adjacent[v], u, w);
}

void graph_clear(graph *g){
	int i;

	for( i = 0 ; i < g->n ; i++ ) list_clear(&g->adjacent[i]);
	free(g->adjacent);
}

/***************************************************************/

int dist[2][1000], pred[2][1000];

int cmp(int a, int b){
    long x = dist[a/1000][a%1000], y = dist[a/1000][a%1000];
    
    return ( x == y ) ? 0 : ( ( x > y ) ? 1 : -1 );
}

void dijkstra(int end, int start, graph *g1, graph *g2){
    int i, j, u, v, uu;
    pq queue;
    node *ptr;
    
    for ( i = 0 ; i < 2 ; i++ )
        for ( j = 0 ; j < 1000 ; j++ ) dist[i][j] = pred[i][j] = INT_MAX;
    
    dist[0][start] = 0, pred[0][start] = start;
    buildMinHeap(&queue, 0, 0, cmp);
    minHeapInsert(&queue, start);
    
    while ( queue.size ){
        u = heapExtractMin(&queue);
      /*  printf("dist[%d][%d] = %ld, pred = %d\n", u/1000, u%1000, dist[u/1000][u%1000], pred[u/1000][u%1000]);
       */ 
       
        uu = u/1000;
        u %= 1000;
        for( ptr = g1->adjacent[u].head->next ; ptr != g1->adjacent[u].tail ; ptr = ptr->next){
            v = ptr->key;
            if ( dist[uu][v] > dist[uu][u] + ptr->value ){
                dist[uu][v] = dist[uu][u] + ptr->value;
                pred[uu][v] = uu*1000+u;
                minHeapInsert(&queue, uu*1000+v);
            }
        }
        
        if ( u / 1000 == 0 ){
            for( ptr = g2->adjacent[u].head->next ; ptr != g2->adjacent[u].tail ; ptr = ptr->next){
                v = ptr->key;
                if ( dist[1][v] > dist[0][u] + ptr->value ){
                    dist[1][v] = dist[0][u] + ptr->value;
                    pred[1][v] = u;
                    minHeapInsert(&queue, v + 1000);
                }
            }
        }
    }
    
    v = dist[0][end] <= dist[1][end] ? dist[0][end] : dist[1][end];
    end = dist[0][end] <= dist[1][end] ? end : 1000 + end;
    u = -1;
    while ( 1 ){
        printf("%d", end%1000 + 1 );
        if ( start == end%1000 ) break;
        putchar(' ');
        if ( pred[end/1000][end%1000] / 1000 == 0 && end / 1000 )
            u = end % 1000;
        end = pred[end/1000][end%1000];
    }
    
    if ( u == -1 ) puts("\nTicket Not Used");
    else printf("\n%d\n", u%1000 + 1);
    printf("%ld\n",  v);
}

int main(){
    int n, u, v, m = -2, s, e;
    long w;
    graph g1, g2;
    
    while(scanf("%d%d%d", &n, &s, &e)==3){
        if ( m != -2 ) puts("");
        graph_init(&g1, n);
        graph_init(&g2, n);
        
        scanf("%d", &m);

        while(m--){
            scanf("%d%d%ld", &u, &v, &w);
            graph_add_edge(&g1, --u, --v, w);
        }
        
        scanf("%d", &m);

        while(m--){
            scanf("%d%d%ld", &u, &v, &w);
            graph_add_edge(&g2, --u, --v, w);
        }
        
        /*graph_show(&g1);
        graph_show(&g2);*/
        
        dijkstra(--s, --e, &g1, &g2);
        graph_clear(&g1);
        graph_clear(&g2);
    }
    
    return 0;
}
