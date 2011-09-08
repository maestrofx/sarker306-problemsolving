#include<cstdio>
#include<cstring>
#include<set>
#include<string>
#include<locale>

#define SIZE 1048585

std::set<std::string>array[SIZE];
std::set<std::string>::iterator pmap;

char input[120005][100];

unsigned long hash(char *str){
    unsigned long x=0;
    
    for(;*str++;){
        x=(x<<5)+x+*str;
    }
    
    //printf("%lu %lu %lu\n", x, x>>20, x&~(-1<<20));
    
    x=((x>>20)^(x&(~(-1<<20))))& (~(-1<<20));
    return x;
}

int main(){
    unsigned long x, y, count=0, i, j, k, lim;
    char a[100], b[100];
    char flag;
    
    while(gets(input[count])){
        std::string inp=input[count];
        
        x=hash(input[count++]);
        array[x].insert(inp);
    }
    
    for(i=0;i<count;i++){
        lim=std::strlen(input[i]);
        for(j=0, flag=0;j<lim && flag==0;j++){
            for(k=0;k<=j;k++) a[k]=input[i][k];
            a[k]=0;
            std::string temp=a;
            x=hash(a);
            pmap=array[x].find(temp);
            if(pmap!=array[x].end()){
                for(k=j+1;k<lim;k++) a[k-j-1]=input[i][k];
                a[k-j-1]=0;
                temp=a;
                x=hash(a);
                pmap=array[x].find(temp);
                if(pmap!=array[x].end()){
                    flag=0;
                    printf("%s\n", input[i]);
                    break;
                }
            }
        }
    }
    
    for(x=0;x<SIZE;x++) array[x].clear();
    return 0;
}
