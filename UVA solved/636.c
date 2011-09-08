#include<stdio.h>
#include<math.h>

int main(){
    char input[100];
    long base, num, i;

    while(scanf("%s", input)!=EOF){
        for(i=base=0;input[i];i++) if(base+'0'<input[i]) base=input[i]-'0';
        for(++base; ; base++){
            for(i=0, num=0;input[i];i++) num=base*num+input[i]-'0';
            if(num==0) break;
            i=sqrt(num)+0.5;
            if(i*i==num) break;
        }

        if(num==0) break;
        printf("%ld\n", base);
    }

    return 0;
}
