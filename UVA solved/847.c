#include<stdio.h>

int main(){
    long unsigned n;
    int flag=0;
    
    while(scanf("%lu", &n)!=EOF){
        if(n>612220032) flag=0;
        else if(n>306110016) flag=1;
        else if(n>34012224) flag=0;
        else if(n>17006112) flag=1;
        else if(n>1889568) flag=0;
        else if(n>944784) flag=1;
        else if(n>104976) flag=0;
        else if(n>52488) flag=1;
        else if(n>5832) flag=0;
        else if(n>2916) flag=1;
        else if(n>324) flag=0;
        else if(n>162) flag=1;
        else if(n>18) flag=0;
        else if(n>9) flag=1;
        else if(n>=1) flag=0;
        
        printf("%s wins.\n", (!flag)? "Stan" : "Ollie");
    }
    
    return 0;
}
