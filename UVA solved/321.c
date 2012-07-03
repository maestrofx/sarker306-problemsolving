#include <stdio.h>
#include <limits.h>
#define SIZE 12
#define MAXQUEUESIZE 1000000

char adjacent[SIZE][SIZE];
char light[SIZE][SIZE];
unsigned distance[SIZE][1<<SIZE], parent[SIZE][1<<SIZE];

typedef struct{
	char room;
	int lightConf;
}pos;

pos Queue[MAXQUEUESIZE + 1];
unsigned head, tail;

void initAll(int n){
	int i, j;
	
	for ( i = 0 ; i < n ; i++ ){
		for ( j = 0 ; j < n ; j++ )
			adjacent[i][j] = 0, light[i][j] = 0;
		for ( j = 0 ; j < ( 1 << n ) ; j++ )
			distance[i][j] = INT_MAX, parent[i][j] = INT_MAX;
	}
	
	distance[0][1] = 0;
	head = tail = 0;
}

void displayLightConf(unsigned value){
	const int SHIFT = SIZE - 1;
	const unsigned MASK = 1 << SHIFT;
	int i;
	for ( i = 1; i <= SHIFT + 1; i++ ) 
	{
		printf("%c", ( value & MASK )? '1' : '0' );
		value <<= 1;

		if ( i % 4 == 0 )
			printf(" ");
	}
}

void printSteps(unsigned room, unsigned lightConf){
	unsigned parRoom, parLightConf, i;
	
	if ( parent[room][lightConf] != INT_MAX ){
		parRoom = parent[room][lightConf];
		parLightConf = parRoom & ~( ~0 << SIZE );
		parRoom >>= SIZE;
		printSteps(parRoom, parLightConf);
		if ( parRoom == room ){
			parRoom = parLightConf ^ lightConf ;
			for ( i = 0 ; parRoom ; parRoom >>= 1 , i++ );
			printf("- Switch %s light in room %d.\n", 
				( lightConf & (1<<(i-1)) ) ? "on" : "off" , i);
		}
		else printf("- Move to room %d.\n", room + 1);
	}
}

void findOptimalStepToBedroom(int n){
	pos u, v;
	int i, finalLightConf = 1 << (n-1);
	
	u.room = 0, u.lightConf = 1;
	Queue[tail++] = u;
	
	while ( head != tail ){
		u = Queue[head++];
		
		/* printf("%d ", u.room);
		displayLightConf(u.lightConf);
		printf(" -> "); */
		if ( u.room == n - 1 && u.lightConf == finalLightConf ){
			printf("The problem can be solved in %u steps:\n", 
				distance[u.room][u.lightConf] );
			printSteps(u.room, u.lightConf);
			return ;
		}
		
		for ( i = 0 ; i < n ; i++ ){
			if ( adjacent[u.room][i] && distance[i][u.lightConf] == INT_MAX 
				&& ( u.lightConf & ( 1 << i ) ) ){
				v.room = i;
				v.lightConf = u.lightConf;
				distance[i][v.lightConf] = distance[u.room][u.lightConf] + 1;
				parent[i][v.lightConf] = ((u.room)<<SIZE) | u.lightConf;
				Queue[tail++] = v;
				/* printf("(%d ", v.room);
				displayLightConf(v.lightConf);
				printf(") "); */
			}
		}
		
		for ( i = 0 ; i < n ; i++ ){
			if ( light[u.room][i] && i != u.room &&
				distance[u.room][u.lightConf ^ ( 1 << i )] == INT_MAX ) {
				v.room = u.room;
				v.lightConf = u.lightConf ^ ( 1 << i );
				distance[v.room][v.lightConf] = distance[u.room][u.lightConf] + 1;
				parent[v.room][v.lightConf] = ((u.room)<<SIZE) | u.lightConf;
				Queue[tail++] = v;
				/*printf("(%d ", v.room);
				displayLightConf(v.lightConf);
				printf(") ");*/
			}
		}
		
		/*puts("");*/
	}
}

int main(){
	int n, s, d, u, v, testCount = 1;
	
	while ( scanf("%d%d%d", &n, &d, &s) == 3 ){
		if ( n == 0  && s == 0 && d == 0 ) break;
		
		initAll(n);
		
		while ( d-- ){
			scanf("%d%d", &u, &v);
			u--, v--;
			adjacent[u][v] = adjacent[v][u] = 1;
		}
		while ( s-- ){
			scanf("%d%d", &u, &v);
			u--, v--;
			light[u][v] = 1;
		}
		
		printf("Villa #%d\n", testCount++);
		findOptimalStepToBedroom(n);
		if ( distance[n-1][1<<(n-1)] == INT_MAX )
			puts("The problem cannot be solved.");
		
		puts("");
	}
	
	return 0;
}
