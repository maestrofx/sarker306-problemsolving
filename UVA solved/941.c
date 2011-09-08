#include<stdio.h>

unsigned long long factorial[21]={1,1,2};

unsigned long long perm_number(int *frq){
    int j, n;
    unsigned long long x;

    for(x=1, j=n=0;j<26;j++){
        x*=factorial[frq[j]], n+=frq[j];
    }
    return factorial[n]/x;
}

void solve(unsigned long long x, char *word, int len, int *frq){
    int i, j;
    unsigned long long y;

    for(i=0;i<len && x;i++){
        for(j=0;j<26;j++){
            if(frq[j]){
                word[i]=j+'a';
                frq[j]--;
                y=perm_number(frq);
                if(y>=x){
                    word[i+1]=0;
                    break;
                }
                else{
                    x-=y;
                    frq[j]++;
                }
            }
        }
    }

    word[len]=0;
    printf("%s\n", word);
}

int main(){
    int data;
    int i, j;
    unsigned long long x;
    int frq[26];
    char word[30];
    char *p;

    for(i=3;i<=20;i++) factorial[i]=factorial[i-1]*i;
    scanf("%d", &data);
    for(i=1;i<=data;i++){
        for(j=0;j<26;j++) frq[j]=0;
        scanf("%s", word);
        for(p=word;*p;p++) frq[*p-'a']++;

        scanf("%lld", &x);
        memset(word, sizeof(word), 0);
        solve(x+1, word, p-word, frq);
    }

    return 0;
}
