#include<stdio.h>

char words[105][258], rules[1001], *possible[1001];
char digits[][2]={"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
int n;

void backtrack(register int index){
    register int i;
    
    if(rules[index]==0){
        for(i=0;i<index;i++) printf("%s", possible[i]);
        puts("");
        return;
    }
    
    if(rules[index]=='0'){
        for(i=0;i<10;i++){
            possible[index]=digits[i];
            backtrack(index+1);
        }
    }
    else{
        for(i=0;i<n;i++){
            possible[index]=words[i];
            backtrack(index+1);
        }
    }
}

int main(){
    int i, m;
    
    while(scanf("%d", &n)!=EOF){
        puts("--");
        for(i=0;i<n;i++) scanf("%s", words[i]);
        
        scanf("%d", &m);
        for(i=0;i<m;i++){
            scanf("%s", rules);
            backtrack(0);
        }
    }
    
    return 0;
}
