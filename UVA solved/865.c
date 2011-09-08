#include<stdio.h>

char plain[128], substitute[128], list[128], input[100];

int main(){
    char ch, flag=1;
    long i, test;
    
    scanf("%ld", &test);
    getchar();
    getchar();
    
    while(test--){
        gets(plain);
        gets(substitute);
        
        for(i=0;plain[i];i++) list[plain[i]]=substitute[i];
        
        printf("%s\n%s\n", substitute, plain);
        while(gets(input)){
            if(input[0]==0) break;
            
            for(i=0; input[i]; i++) putchar(list[input[i]]? list[input[i]] : input[i]);
            puts("");
        }
        
        if(test){
            puts("");
            for(i=0;i<128;i++) list[i]=0;
        }
    }
    
    return 0;
}
