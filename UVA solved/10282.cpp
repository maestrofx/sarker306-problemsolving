#include<cstdio>
#include<map>
#include<string>
#include<locale>

#define SIZE 1048585

std::map<std::string, std::string>array[SIZE];
std::map<std::string, std::string>::iterator pmap;

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
    char word[150], meaning[150], input[500];
    unsigned long x;
    
    while(gets(input)){
        if(input[0]==0) break;
        sscanf(input, "%s%s", word, meaning);
        std::string w=word, m=meaning;
        
        x=hash(meaning);
        array[x].insert(std::pair<std::string, std::string>(m, w));
    }
    
    while(gets(input)){
        std::string word=input;
        
        x=hash(input);
        pmap=array[x].find(word);
        if(pmap==array[x].end()) printf("eh\n");
        else printf("%s\n", (pmap->second).c_str());
    }
    
    for(x=0;x<SIZE;x++) array[x].clear();
    return 0;
}
