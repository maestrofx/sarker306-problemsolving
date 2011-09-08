#include<stdio.h>
#include<string.h>

int main()
{
    long long n, m;
    int rad, i, j;
    char number[15];
      
    while(scanf("%s", number)!=EOF){
        j=strlen(number);
        sscanf(number, "%lld", &m);
        if (number[0]=='-') break;
        if(number[0]='0' && number[1]=='x') rad=16;
        else rad=10;
        n=0;
        if(rad==16){
            for(i=2;i<j;i++)
            if(number[i]>='0' && number[i]<='9') n=rad*n+number[i]-'0';
            else if(number[i]>='A' && number[i]<='F') n=rad*n+number[i]-'A'+10;
            else if(number[i]>='a' && number[i]<='f') n=rad*n+number[i]-'a'+10;
            printf("%lld\n", n);
        }
        else  printf("0x%llX\n", m);
    }
    
    return 0;
}
