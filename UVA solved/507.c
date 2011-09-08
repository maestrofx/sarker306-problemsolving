#include<stdio.h>

int main(){
    long routes, n, stopage, x, max, a, b, i, j, current;
    
    while(scanf("%ld", &routes)!=EOF){
        for(n=1;n<=routes;n++){
            scanf("%ld", &stopage);
            max=-999999999, a=0, b=0, current=0;
            for(i=j=1;i<stopage;i++){
                scanf("%ld", &x);
                current+=x;
                if(current>max) max=current, a=j, b=i+1;
                else if(current==max){
                    if(b-a<i+1-j) a=j, b=i+1;
                }
                if(current<0) current=0, j=i+1;
            }
           /* printf("%ld  ", max);*/
            if(max<=0) printf("Route %ld has no nice parts\n", n);
            else printf("The nicest part of route %ld is between stops %ld and %ld\n", n, a, b);
        }
    }
    
    return 0;
}
