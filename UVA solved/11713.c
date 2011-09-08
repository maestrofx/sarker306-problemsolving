#include<stdio.h>

int IsVowel(char ch){
    if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') return 1;
    return 0;
}

int check(char *a, char *b){
    int i;
    
    for(i=0;a[i] && b[i];i++){
        if(a[i]!=b[i]){
            if(!IsVowel(a[i]) || !IsVowel(b[i])) return 0;
        }
    }
    
    return (a[i]||b[i])? 0:1;
}

int main(){
    char a[30], b[30];
    int test;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%s%s", a, b);
            printf("%s\n", (check(a, b))?"Yes":"No");
        }
    }
    
    return 0;
}
