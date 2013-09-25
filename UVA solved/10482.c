#include<stdio.h>

char arr[33][641][641];
int n, candy[33];

int abs(int p){ return p > 0 ? p : -p; }
int min(int a, int b){ return a > b ? b : a; }
int max(int a, int b){ return a > b ? a : b; }

int main(){
	int test, ks;
	int i, pos, fir, sec, sum, minBadness;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			sum = 0;
			minBadness = 1000;
			for ( i = 1 ; i <= n ; i++ ) scanf("%d", &candy[i]), sum += candy[i];
			
			for ( fir = 0 ; fir <= sum ; fir++ )
			for ( sec = 0 ; sec <= sum ; sec++ ) arr[0][fir][sec] = 0;
			arr[0][0][0] = 1;
			for ( pos = 1 ; pos <= n ; pos++ )
				for ( fir = 0 ; fir <= sum ; fir++ )
					for ( sec = 0 ; sec <= sum ; sec++ ){
						if ( fir >= candy[pos] && arr[pos - 1][fir - candy[pos]][sec] )
							arr[pos][fir][sec] = 1;
						else if ( sec >= candy[pos] && arr[pos - 1][fir][sec - candy[pos]] )
							arr[pos][fir][sec] = 1;
						else arr[pos][fir][sec] = arr[pos - 1][fir][sec];
					}
					
			for ( fir = 0 ; fir <= sum ; fir++ )
				for ( sec = 0 ; sec <= sum ; sec++ )
					if ( arr[n][fir][sec] ){
						pos = max(fir, max(sec, sum - fir - sec)) - min(fir, min(sec, sum - fir - sec));
						if ( minBadness > pos ) minBadness = pos;
					}

			printf("Case %d: %d\n", ks, minBadness);
		}
	}
	
	return 0;
}

