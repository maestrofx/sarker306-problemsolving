#include<stdio.h>

int array[1005];
int n;

int main(){
    int i, j, k, expected, top, x;
    int stck[1005];
    
    while(scanf("%d", &n)!=EOF && n>0){
        while(scanf("%d", &array[1]) && array[1]){
            for(i=2;i<=n;i++) scanf("%d", &array[i]);
            
            top = 0;
            expected = n;
            for ( i = n ; i ; i-- ){
                x = array[i];
                if ( x == expected ){
                    expected--;
                    continue;
                }
                else if ( top && expected ==  stck[top-1] ){
                    while ( top && expected == stck[top-1] ) top--, expected--;
                    stck[top++] = x;
                }
                else{
                    stck[top++] = x;
                }
            }
            
            while ( top ){
                if ( expected == stck[top-1] ){
                    expected--;
                    top--;
                }
                else break;
            }
            
            if ( top ) puts("No");
            else puts("Yes");
        }
        
        puts("");
    }
    
    return 0;
}
