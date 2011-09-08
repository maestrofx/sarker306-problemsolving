#include<stdio.h>
#define SIZE 1002
long long derangement[SIZE], comb[SIZE][SIZE], ans[SIZE][SIZE], perm[1001];

long long nCr(long n, long r)
{
    long long x;

	if(r==0) x=1;
	else if(n<1001 && r<501 && comb[n][r])
		x=comb[n][r];
	else if(2*r>n)
		x=nCr(n, n-r);
	else
		x=nCr(n-1,r) + nCr(n-1,r-1);
	if(n<1001 && r<501 && !comb[n][r])
		comb[n][r]=x%1000000007;

	return x%1000000007;
}

long long calc(long m, long n)
{
    if(m<0 || n<0) return 0;
    if(ans[m][n]) return ans[m][n];
    if(m==0) ans[m][n] = perm[n];
    else if(n==0) ans[m][n] = derangement[m];

    /*printf("%d %d\n", m, n);*/
    else ans[m][n]=(n-1)*calc(m-1, n-1)+(m-1)*calc(m-2, n-2);
    ans[m][n]%=1000000007;
    return ans[m][n];
}

int main(){
    int i, test, n, m, k;
    long long answer;

    perm[0]=perm[1]=1;
    for(i=2, derangement[0]=1, derangement[1]=0; i<1001;i++){
        derangement[i]=i*derangement[i-1];
        if(i&1) derangement[i]--;
        else derangement[i]++;
        perm[i]=(i*perm[i-1])%1000000007;
        derangement[i]%=1000000007;
        if(derangement[i]<0) derangement[i]+=1000000007;
    }

    while(scanf("%d", &test)!=EOF){
        for(i=1;i<=test;i++){
            scanf("%d%d%d", &n, &m, &k);
            answer=nCr(m, k);
            answer*=calc(m-k, n-k)%1000000007;
            printf("Case %d: %lld\n", i, answer%1000000007);
        }
    }

    return 0;
}
