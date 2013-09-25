#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#define SIZE 60
#define MAXVERTICES 125
#define INF INT_MAX
#define NIL 0

int pair[MAXVERTICES], degree[MAXVERTICES], adj[MAXVERTICES][MAXVERTICES];
int dist[MAXVERTICES], T[MAXVERTICES];

int dfsAugment(int u){
	int i, v;
	
	if ( u == NIL ) return 1;
	for ( i = 0 ; i < degree[u] ; i++ ){
		v = adj[u][i];
		if ( dist[pair[v]] == dist[u] + 1 )
			if ( dfsAugment(pair[v]) ){
				pair[u] = v;
				pair[v] = u;
				return 1;
			}
	}
	
	dist[u] = INF;
	return 0;
}

int queue[MAXVERTICES + 2], head, tail;
int rightEncountered[MAXVERTICES + 2], rightIndex;

int bfsAugment(int leftNodes){
	int i, u, v;
	
	rightIndex = head = tail = 0;
	dist[NIL] = INF;
	for ( i = 1 ; i <= leftNodes ; i++ )
		if ( pair[i] == NIL )
			queue[tail++] = i, dist[i] = 0;
		else dist[i] = INF;
		
	while ( head != tail ){
		u = queue[head++];
		
		for ( i = 0; i < degree[u] ; i++ ){
			v = adj[u][i];
			if ( dist[pair[v]] == INF ){
				rightEncountered[rightIndex++] = v;
				dist[pair[v]] = dist[u] + 1;
				queue[tail++] = pair[v];
			}
		}
	}
	
	return (dist[NIL] != INF);
}

void graphInit( int nodes ){
	int i;
	
	for ( i = 0 ; i < nodes ; i++ )
		pair[i] = NIL, degree[i] = 0;
}

int HopcroftKarp(int leftNodes, int rightNodes){
	int i, matching = 0;
	
	while ( bfsAugment(leftNodes) ){
		for ( i = 1 ; i <= leftNodes ; i++ )
			if ( pair[i] == NIL && dfsAugment( i ) ) matching++;
	}
	
	memset(T, 1, sizeof(T));
	
	for ( i = 0 ; i < tail ; i++ ) T[queue[i]] = 0;
	for ( i = 0 ; i < rightIndex ; i++ ) T[rightEncountered[i]] = 0;
	
	return matching;
}

#define EPS 1e-8
double Abs(double val){
    if ( val < 0 ) val = -val;
    if ( val < EPS ) return 0;
    return val;
}

int ExactMatch( double array[SIZE][SIZE], int match[SIZE], int n ){
    int i, j;
    int zeroes[SIZE], minZero, minZeroInd;
    char isRowSelected[SIZE], isColSelected[SIZE];
    
    for ( i = 1 ; i <= n ; i++ ){
        zeroes[i] = 0;
        isRowSelected[i] = 0;
        isColSelected[i] = 0;
        for ( j = 1 ; j <= n ; j++ )
            if ( Abs(array[i][j])<EPS ){
                array[i][j] = 0;
                zeroes[i]++;
            }
    }
    
    for ( i = 1 ; i <= n ; i++ ){
        minZero = SIZE + 1, minZeroInd = -SIZE;
        for ( j = 1 ; j <= n ; j++ ){
            if ( isRowSelected[j] ) continue;
            /*printf("(%d->%d) ", j, zeroes[j]);*/
            if ( minZero > zeroes[j] )
                minZero = zeroes[j], minZeroInd = j;
        }
        
        if ( minZero == 0 ){
            /*printf("\nNo row contains 0, No further matching found\n");*/
            return 0;
        }
        
        for ( j = 1 ; j <= n ; j++ )
            if ( isColSelected[j] == 0 && Abs(array[minZeroInd][j]) < EPS ) break;
        
        if ( j > n ){
            /*printf("\nColumns containing 0 previously selected.... No further matching found\n");*/
            return 0;
        }
        
        isRowSelected[minZeroInd] = 1;
        match[minZeroInd] = j;
        isColSelected[j] = 1;
        
        /*printf("\n%dth row matched to %dth column....\n", minZeroInd, j);*/
        for ( j = 1 ; j <= n ; j++ )
            if ( Abs(array[j][match[minZeroInd]]) < EPS ) zeroes[j]--;
    }
    
    /*for ( i = 1 ; i <= n ; i++ ) printf("%dth row -> %dth column\n", i, match[i]);*/
    return 1;
}

void printMatrix( double array[SIZE][SIZE], int n ){
    int i, j;
    
    puts("");
    for ( i = 1 ; i <= n ; i++ ){
        for ( j = 1 ; j <= n ; j++ ) printf("%7.3lf ", array[i][j] );
        puts("");
    }
    puts("");
}

void MinimumWeightedMatch( double array[SIZE][SIZE], int match[SIZE], int n ){
    int i, j;
    double mini;
    
    for ( i = 1 ; i <= n ; i++ ){
        mini = 1e100;
        for ( j = 1 ; j <= n ; j++ )
            if ( mini > array[i][j] ) mini = array[i][j];
        
        for ( j = 1 ; j <= n ; j++ ) array[i][j] -= mini;
    }
    
    /*printMatrix(array, n);
    printf("For row...\n\n");*/
    if ( ExactMatch(array, match, n) ) return;
    
    for ( j = 1 ; j <= n ; j++ ){
        mini = 1e100;
        for ( i = 1 ; i <= n ; i++ )
            if ( mini > array[i][j] ) mini = array[i][j];
        
        for ( i = 1 ; i <= n ; i++ ) array[i][j] -= mini;
    }
    
    /*printMatrix(array, n);
    printf("For column...\n\n");*/
    if ( ExactMatch(array, match, n) ) return;
    
    while ( 1 ){
        graphInit( 2 * n + 1 );
        
        mini = 1e100;
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                if ( Abs(array[i][j]) < EPS ) adj[i][degree[i]++] = n + j;
        
        if ( n == HopcroftKarp(n, n) ){
            /*printf("Matching about to be found...\n");*/
            break;
        }
        
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                if ( !T[i] && T[j+n] && (mini > array[i][j]) )
                    mini = array[i][j];

    	for ( i = 1 ; i <= n ; i++ ){
            if ( T[i] ){
                /*printf(" r%d", i);*/
                for ( j = 1 ; j <= n ; j++ )
                    array[i][j] += mini;
            }
        }
        
    	for ( i = 1 ; i <= n ; i++ ){
            if ( !T[i + n] ){
                /*printf(" c%d", i);*/
                for ( j = 1 ; j <= n ; j++ )
                    array[j][i] += mini;
            }
        }
        
        /*puts("");*/
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                array[i][j] -= mini;
        
        /*printMatrix(array, n);
        getchar();*/
    }
    
    ExactMatch(array, match, n);
}

double ProcessMinTravelTime(double array[SIZE][SIZE], int n, int m){
    int i, j;
    int matching[SIZE];
    double totalScore = 0, maxElement = -1.00, tmpArray[SIZE][SIZE];
    
    for ( i = 1 ; i <= n ; i++ )
        for ( j = 1 ; j <= m ; j++ ){
            tmpArray[i][j] = array[i][j];
            if ( maxElement < array[i][j] )
                maxElement = array[i][j];
        }
    
    for ( i = n + 1 ; i <= m ; i++ ){
        for ( j = 1 ; j <= m ; j++ )
            tmpArray[i][j] = maxElement;
    }
    
    /*printMatrix(tmpArray, m);*/
    MinimumWeightedMatch(tmpArray, matching, m);
    /*ExactMatch(array, matching, n);*/
    
    for ( i = 1 ; i <= n ; i++ )
        totalScore += array[i][matching[i]];
        
    return totalScore / n;
}

int main(){
    int test, kase, n, i, m, j;
    double array[SIZE][SIZE];
    
    while ( scanf("%d%d", &n, &m) == 2 && m && n ){
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= m ; j++ ) 
                scanf("%lf", &array[i][j]);
        
        printf("%.2lf\n", ProcessMinTravelTime(array, n, m));
    }
    
    return 0;
}
