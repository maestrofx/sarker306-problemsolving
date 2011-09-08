#include<stdio.h>
#include<ctype.h>

long wordlength[35];
int maxlen;

int input(){
    char ch, previous=-1;
    int inWord=0, linecount=1, line_offset=0, lettercount=0, wordcount=0;
    
    maxlen=0;
    while((ch=toupper(getchar()))!=EOF){
        line_offset++;
        
        if(ch>='A' && ch<='Z'){
            if( !inWord ) inWord=1, wordcount++;
            lettercount++;
        }
        
        else if(ch!='-' && ch!='\''){
            if(ch=='\n'){
                linecount++, line_offset=0;
                if(previous=='-') continue;
            }
            
            if(inWord){
                inWord=0;
                wordlength[lettercount]++;
                maxlen=(maxlen>lettercount)?maxlen:lettercount;
                lettercount=0;
            }
            
            if(ch=='#' && line_offset==1) return 1;
        }
        
        previous=ch;
    }
    
    return 0;
}

void output(){
    int i;
    
    for(i=1 ; i<=maxlen; i++){
        if(wordlength[i]) printf("%d %d\n", i, wordlength[i]);
        wordlength[i]=0;
    }
    
    puts("");
}

int main(){
    while(input()) output();
    
    return 0;
}
