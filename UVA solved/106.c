#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 1000005

char array[MAX];
long ans[MAX][2];

long gcd(long m, long n){
    long temp;
    
    while(n){
        temp=m; m=n; n=temp%n;
    }
    
    return m;
}

int main(){
    long i, j, var, a, b, c, aa, bb, cc, triple, intriple, n;
    
    while(scanf("%ld", &n)!=EOF){
        if(ans[n][0]){
            printf("%ld %ld\n", ans[n][0], ans[n][1]);
            continue;
        }
        
        var=sqrt(n), triple=intriple=0;
        for(i=0;i<=n;i++) array[i]=0;
        
        for(i=1;i<=var;i++){
            for(j=i+1; ;j+=2){
                c=i*i+j*j;
                if(c>n) break;
                a=j*j-i*i, b=2*i*j;
                if(gcd(gcd(a, b), c)==1) triple++;
                for(aa=a, bb=b, cc=c;cc<=n;aa+=a, bb+=b, cc+=c){
                    if(!array[aa]) array[aa]=1, intriple++;
                    if(!array[bb]) array[bb]=1, intriple++;
                    if(!array[cc]) array[cc]=1, intriple++;
                }
            }
        }
        
        printf("%ld %ld\n", triple, n-intriple);
        ans[n][0]=triple, ans[n][1]=n-intriple;
    }
    
    return 0;
}
