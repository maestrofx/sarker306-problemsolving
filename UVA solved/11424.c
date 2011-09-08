#include<stdio.h>
#include<math.h>

#define SIZE 200005

long long G[SIZE+5];
long long phi[SIZE+5];
long long isnp[SIZE+5];

int main(){
    long long i, j, v, k;
    
    for(i=0;i<SIZE;i++) phi[i]=i;
    for(i=4;i<SIZE;i+=2) isnp[i]=1;
    for(i=3, v=sqrt(SIZE)+1;i<v;i+=2){
		if(isnp[i]==0){
			for(j=i*i;j<SIZE;j+=i){
				isnp[j]=1;
			}
		}
    }
    
    for(i=2;i<SIZE;i++){
		if(isnp[i]==0){
			for(j=i;j<SIZE;j+=i){
				phi[j]-=phi[j]/i;
			}
		}
    }
    
    for(i=2;i<SIZE;i++){
		for(j=2*i, k=2;j<SIZE;j+=i, k++){
			/*G[j]+=i*phi[k];
			if(k!=i) G[j]+=k*phi[i];*/
			G[j]+=i*phi[j/i];
		}
    }
    
    for(i=2;i<SIZE;i++) G[i]+=phi[i]+G[i-1];
    /*return 0;*/
    while(scanf("%I64d", &v)!=EOF){
        if(v<=0||v>SIZE) break;
        printf("%I64d\n", G[v]);
    }
    
    return 0;
}
