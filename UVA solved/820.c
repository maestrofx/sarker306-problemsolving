#include<stdio.h>

#define SIZE 105
#define INF 1<<30

const long WHITE = 0, GRAY = 1, BLACK = 2;
long flow[SIZE+1][SIZE+1], capacity[SIZE+1][SIZE+1], res_capacity[SIZE+1][SIZE+1];
long parent[SIZE+1], color[SIZE+1], queue[SIZE<<1];
long min_capacity[SIZE+1];
long size, source, sink, first, last, edges;
long max_flow;

long min(long a, long b){ return (a>b) ? b : a; }

long BFS(long source){
    long i, u, v;

	for (i = 0; i < size; i++){
		color[i] = WHITE;
		min_capacity[i] = INF;
	}

	first = last = 0;
	queue[last++] = source;
	color[source] = GRAY;

	while (first != last)  /* While "queue" not empty.. */
	{
		v = queue[first++];
		for (u = 0; u < size; u++)
			if (color[u] == WHITE && res_capacity[v][u] > 0)
			{
				min_capacity[u] = min(min_capacity[v], res_capacity[v][u]);
				parent[u] = v;
				color[u] = GRAY;
				if (u == sink) return 1;
				queue[last++] = u;
			}
	}

	return 0;
}

void maxFlow(){  /* Edmonds-Karp algorithm with O(V³E) complexity */
    long i, j, v, u;

	for (i = 0; i < size; i++)
		for (parent[i]=i, j = 0; j < size; j++){
			res_capacity[i][j] = capacity[i][j];
			flow[i][j] = flow[j][i] = 0;
        }

    max_flow = 0;
	while (BFS(source)){
		max_flow += min_capacity[sink];
		v = sink;
		while (v != source){
			u = parent[v];
			flow[u][v] += min_capacity[sink];
			flow[v][u] -= min_capacity[sink];
			res_capacity[u][v] -= min_capacity[sink];
			res_capacity[v][u] += min_capacity[sink];
			v = u;
		}
	}
}

void init(){
    long i, j;

    for ( i = 0; i < size; i++)
        for ( j = 0; j < size; j++)
            capacity[i][j] = 0;
}

int main(){
    long i, u, v, x, test = 1;

    while(scanf("%ld", &size) != EOF && size > 0){
        scanf("%ld%ld%ld", &source, &sink, &edges);

        init();
        source--, sink--;
        for(i = 0; i < edges ; i++){
            scanf("%ld%ld", &u, &v);
            u--, v--;
            scanf("%ld", &x);

            capacity[u][v] += x;
            capacity[v][u] = capacity[u][v];
        }

        maxFlow();
        printf("Network %ld\nThe bandwidth is %ld.\n\n", test++, max_flow);
    }

    return 0;
}
