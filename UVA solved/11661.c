#include<stdio.h>

long minimum(long a, long b){ return (a>b)? b:a; }
long abs(long a) { return (a>0) ? a: -a; }
int main(){
    long posD, posR, n, min;
    long i;
    char ch;
    
    while(scanf("%ld", &n)!=EOF){
        if(n==0) break;
        getchar();
        for(i=0, posD=-3000000, posR=min=3000000;i<n;i++){
            ch=getchar();
            switch(ch){
                case 'Z': posR=i;
                case 'D': posD=i; break;
                case 'R': posR=i;
            }
            if(ch!='.') min=minimum(min, abs(posD-posR));
        }
        
        printf("%ld\n", min);
    }
    
    return 0;
}
