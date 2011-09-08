#include<cstdio>

#define WEIGHT 30
#define SIZE 1000

long max(long a, long b){
    return (a>b)?a:b;
}

long Vi[SIZE+3], Wi[SIZE+3], C[SIZE+3][WEIGHT+3];
int www[SIZE+3];

int main(){
    long i, w, N, MW, MM, test;
    
    scanf("%ld", &test);
    
    while(test--){
        scanf("%ld", &N);
        for(i=1;i<=N;i++){
            scanf("%ld%ld", Vi+i, Wi+i);
        }
        
        MW=0;
        scanf("%ld", &MM);
        for(i=1;i<=MM;i++){
            scanf("%ld", www+i);
            if(www[i]>MW) MW=www[i];
        }

        for (i=0;i<=N ;i++) C[i][0] = 0;
        for (w=0;w<=MW;w++) C[0][w] = 0;

        for (i=1;i<=N;i++) {
			for (w=1;w<=MW;w++) {
				if (Wi[i] > w)
					C[i][w] = C[i-1][w];
				else
					C[i][w] = max(C[i-1][w] , C[i-1][w-Wi[i]]+Vi[i]);
			}
		}
		
        for(i=1, MW=0;i<=MM;i++){
            MW+=C[N][www[i]];
        }
        printf("%ld\n", MW);
    }
    
    return 0;
}
