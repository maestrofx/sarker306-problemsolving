#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

typedef struct Elephant{
	int weight, iq, order;
}Elephant;

int cmp(const void *a, const void *b){
	return ((Elephant*)a)->weight - ((Elephant*)b)->weight;
}

int n = 1;
Elephant arr[1005];
int length[1005], parent[1005];
int stck[1005], top;

int main(){
	int i, j;
	
	while ( scanf("%d%d", &arr[n].weight, &arr[n].iq) == 2 ){
		arr[n].order = ++n;
	}
	
	qsort(arr, n, sizeof(Elephant), cmp);
	arr[n].weight = INT_MAX, arr[n].iq = INT_MIN, arr[n].order = n + 1;
	
	for ( i = 1 ; i <= n ; i++ ){
		for ( j = 1 ; j < i ; j++ ){
			if ( arr[j].weight < arr[i].weight && arr[j].iq > arr[i].iq && length[i] < length[j] + 1 )
				length[i] = length[j] + 1, parent[i] = j;
		}
	}
	
	i = n, top = 0;
	while ( parent[i] ){
		stck[top++] = parent[i];
		i = parent[i];
	}

	printf("%d\n", length[n]);
	while ( top-- ) printf("%d\n", arr[stck[top]].order);
	
	return 0;
}

