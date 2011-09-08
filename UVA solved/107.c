#include<stdio.h>
#include<math.h>

typedef long long llong;

llong bigexp(llong b,llong p){
	llong c;
	if(p==0) return 1;
	else if(p&1==0){
		c=bigexp(b,p>>1);
		return c*c;
	}
	else return b*bigexp(b,p-1);
}

int main(){
	llong W, H, N, level;
	
	while(scanf("%lld%lld", &H, &W)!=EOF && H && W){
		if(H==1 && W==1) printf("0 1\n");
		else{
			if(H==W+1) level=1, N=W;
			else for(level=2;level<64;level++){
				N=(llong)(pow(W, 1.0/level)+0.5);
				if(bigexp(N+1, level)==H) break;
			}
			if(level!=64) printf("%lld %lld\n", (N==1)? level:(W-1)/(N-1), (H-W)*N+H);
		}
	}
	
	return 0;
}
