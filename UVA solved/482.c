#include<stdio.h>
#define MAX 100001

long order[MAX], n;
char input[MAX][20];

int main(){
    long test, i;
    
    while(scanf("%ld", &test)!=EOF){
        getchar();
        while(test--){
            getchar();
            i=1;
            scanf("%ld", &order[0]);
            while(getchar()!='\n') scanf("%ld", &order[i++]);
            n=i;
            
            for(i=0;i<n;i++){
                scanf("%s", input[order[i]-1]);
            }
            
            for(i=0;i<n;i++) printf("%s\n", input[i]);
            
            if(test) printf("\n");
        }
    }
    
    return 0;
}
