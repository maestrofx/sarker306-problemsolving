#include<stdio.h>

char array[][20]={"", "", "6", "28", "", "496", "", "8128", "", "", "", "-", "", "33550336", "", "", "", "8589869056", "", "137438691328", "", "", "", "-", "", "", "", "", "", "-", "", "2305843008139952128"};

int main(){
    int n;
    
    while(scanf("%d", &n)!=EOF && n>0 && n<32){
        if(array[n][0]==0) printf("Given number is NOT prime! NO perfect number is available.\n");
        else if(array[n][0]=='-') printf("Given number is prime. But, NO perfect number is available.\n");
        else printf("Perfect: %s!\n", array[n]);
    }
    
    return 0;
}
