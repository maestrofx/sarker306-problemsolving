#include<stdio.h>
#define MAX 1002
#define SIZE 13

int freq[MAX], number[SIZE];
int color[SIZE], colorfreq[SIZE];
char _foundsum;

void backtrack(int num, int comb, int index, int size, int N){
    int i, j, x, tmp;
    
    if(num==N){
        printf("%d", number[color[0]]);
        for(j=1;j<colorfreq[0]; j++) printf("+%d", number[color[0]]);
        for(i=1;i<comb;i++){
            for(j=0;j<colorfreq[i];j++) printf("+%d", number[color[i]]);
        }
        printf("\n");
        _foundsum=1;
        return ;
    }
    
    for(i=index+1;i<size;i++){
        color[comb]=i;
        tmp=colorfreq[comb];
        for(j=freq[number[i]];j>tmp;j--){
            x=number[i]*(j-tmp)+num;
            colorfreq[comb]=j;
            if(x<=N){
                backtrack(x, comb+1, i, size, N);
            }
        }
        colorfreq[comb]=tmp;
        color[comb]=-1;
    }
}

void findsum(int N, int size){
    int i, j;
    
    for(i=0;i<size;i++){
        color[0]=i;
        for(j=freq[number[i]];j;j--){
            colorfreq[0]=j;
            backtrack(j*number[i], 1, i, size, N);
        }
        color[0]=-1;
    }
}

int main(){
    int i, n, N, x, count;
    
    while(scanf("%d%d", &N, &n)!=EOF && n){
        for(i=0;i<MAX;i++) freq[i]=0;
        for(i=0, _foundsum=0, count=0;i<n;i++){
            scanf("%d", &x);
            if(freq[x]==0) number[count++]=x;
            freq[x]++;
        }
        color[0]=-1, colorfreq[0]=0;
        printf("Sums of %d:\n", N);
        findsum(N, count);
        if(!_foundsum) printf("NONE\n");
    }
    
    return 0;
}
