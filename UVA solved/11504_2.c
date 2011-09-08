#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>

typedef struct t_node{
    long value;
    struct t_node *next, *prev;
}node;

typedef struct{
	long size;
	node *head, *tail;
}list;

typedef struct{
	long n;
	long *parent;
	list *adjacent;
}graph;

node *ll_new(long x){
    node *ptr = (node*)malloc(sizeof(node));

    if(!ptr) return 0;
    ptr->value = x;
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
	lst->head = ll_new(INT_MAX);
	lst->tail = ll_new(INT_MAX);
	lst->head->next = lst->tail;
	lst->tail->prev = lst->head;
}

void list_show(list *lst){
	node *ptr;

	for( ptr = lst->head->next ; ptr != lst->tail ; ptr = ptr->next) printf(" %d", ptr->value);
	puts("");
}

void list_push_back(list *lst, long n){
	ll_push_back(lst->tail, ll_new(n));
}

void list_push_front(list *lst, long n){
	ll_push_front(lst->head, ll_new(n));
}

long list_pop_front(list *lst){
    node *ptr = ll_delete(lst->head->next);
    long x = ptr->value;
    free(ptr);
    return x;
}

void list_clear(list *lst){
	ll_clear(lst->head);
}

long list_empty(list *lst){
    return (lst->head->next == lst->tail) ? 1 : 0;
}

void graph_init(graph *g, long n){
	long i;

	g->n = n;
	g->parent = (long*)malloc(sizeof(long) * n);
	g->adjacent = (list*)malloc(sizeof(list) * n);
	for( i = 0 ; i < n ; i++ ){
	    list_init(g->adjacent + i);
	    g->parent[i] = INT_MAX;
	}
}

void graph_show(graph *g){
	long i;

	puts("***********************");
	printf("Vertices : %d\n", g->n);
	for( i = 0 ; i < g->n ; i++ ){
		printf("Vertex %d :", i);
		list_show(g->adjacent + i);
	}

	puts("**********************");
}

void graph_add_edge(graph *g, long u, long v){
	list_push_back(g->adjacent + u, v);
}

void graph_clear(graph *g){
	long i;

	free(g->parent);
	for( i = 0 ; i < g->n ; i++ ) list_clear(&g->adjacent[i]);
	free(g->adjacent);
}

void bfs(graph *g, long start){
    long u, v;
    list queue;
    node *ptr;

    list_init(&queue);
    list_push_back(&queue, start);

    while( list_empty(&queue) == 0 ){
        u = list_pop_front(&queue);

        for( ptr = g->adjacent[u].head->next ; ptr != g->adjacent[u].tail ; ptr = ptr->next){
            if(g->parent[ v = ptr->value ] == INT_MAX){
                g->parent[v] = u;
                list_push_back(&queue, v);
            }
        }
    }

    list_clear(&queue);
}

void dfs(graph *g, long u, long *parent, list *sorted){
    long v;
    node *ptr;

    for( ptr = g->adjacent[u].head->next ; ptr != g->adjacent[u].tail ;  ptr = ptr->next ){
        if(parent[ v = ptr->value ] == INT_MAX){
            parent[v] = u;
            dfs(g, v, parent, sorted);
        }
    }

    list_push_front(sorted, u);
}

void topological_sort(graph *g){
    node *ptr;
    list queue, sorted;
    long i, indx = 0, *parent, u, v;

    parent = (long*)malloc(sizeof(long) * g->n);
    for(i = 0 ; i < g->n ; i++) parent[i] = INT_MAX;
    list_init(&sorted);
    list_init(&queue);

    for( i = 0 ; i < g->n ; i++ ){
        if(parent[i] == INT_MAX){
            parent[i] = i;
            dfs(g, i, parent, &sorted);
        }
    }

    for( ptr = sorted.head->next ; ptr != sorted.tail ; ptr = ptr->next ){
        u = ptr->value;
        if(g->parent[u] == INT_MAX){
			/*printf("%d ", u);*/
            g->parent[u] = u;
            bfs(g, u);
            list_push_back(&queue, u);
            indx++;
        }
    }

    printf("%ld\n", indx);

    list_clear(&queue);
    list_clear(&sorted);
    free(parent);
}

int main(){
	long n, m, u, v, test;
	graph g;

	while( scanf("%ld", &test) != EOF){
        while(test--){
            scanf("%ld", &n);
            graph_init(&g, n);
            scanf("%ld", &m);

            while(m--){
                scanf("%ld%ld", &u, &v);
                graph_add_edge(&g, --u, --v);
            }

            topological_sort(&g);
            graph_clear(&g);
		}
	}

	return 0;
}
