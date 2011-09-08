#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXWORD 2002
#define WORDSIZE 50

char dictionary[MAXWORD+1][WORDSIZE+2];
int dictionarywordsize[MAXWORD+1];
int wordcount;
int comb[WORDSIZE+3];
char input[WORDSIZE*2];
char words_input[WORDSIZE+1][WORDSIZE+2];
char *tobesorted[WORDSIZE+1];
int inputlen, count_words_input;

void space_cancel(char *A){
	int space=0, i, j;
	while(A[space]==' '||A[space]=='\t') space++;
	if(space){
		for(i=space,j=0;A[i-1]!='\0';i++, j++) A[j]=A[i];
	}
	return;
}

int cmp(const void *x, const void *y){
    return *((char*)x)-*((char*)y);
}

int cmp1(const void *x, const void *y){
    return strcmp(*(char**)x, *(char**)y);
}

void backtrack(char *word, int len, int comb_index, int index, int size, const char *str){
    int i, j, flag=0, lentmp;
    char temp[2*WORDSIZE];
    
    if(strlen(word)-strlen(str)==0){
        qsort(word, len, sizeof(char), cmp);
        if(strcmp(word, str)) return ;
        if(comb_index==count_words_input){
            flag=1;
            for(i=0;i<comb_index;i++){
                if(strcmp(dictionary[comb[i]], tobesorted[i])) flag=0;
            }
            
            if(flag) return;
        }
        printf("%s =", input);
        for(i=0;i<comb_index;i++) printf(" %s", dictionary[comb[i]]);
        printf("\n");
        return;
    }
    
    for(i=index;i<size;i++){
        lentmp=len;
        len+=dictionarywordsize[i];
        if(len<=inputlen) {  
            strcpy(temp, word);
            strcat(word, dictionary[i]);
            /*for(j=0;j<index;j++) printf(" ");
            printf("%s:\n", word);*/
            /*qsort(word, len, sizeof(char), cmp);*/
            comb[comb_index]=i;
            backtrack(word, len, comb_index+1, i+1, size, str);
            strcpy(word, temp);
        }
        len=lentmp;
    }
    /*printf("\n");*/
}

void check_anagram(const char *str){
    int i, ln;
    char temp[WORDSIZE*2];
    
    for(i=0;i<wordcount;i++){
        strcpy(temp, dictionary[i]);
        ln=dictionarywordsize[i];
        /*printf("->%s:\n", temp);*/
        /*qsort(temp, ln, sizeof(char), cmp);*/
        comb[0]=i;
        if(ln<=inputlen) backtrack(temp, ln,1,  i+1, wordcount, str);
    }
}

int main(){
    int i,j;
    char trimmedinput[WORDSIZE+3], *ptr;
    
    for(;;){
        while(scanf("%s", dictionary[wordcount])!=EOF){
            if(dictionary[wordcount][0]=='#') break;
            dictionarywordsize[wordcount]=strlen(dictionary[wordcount]);
            wordcount++;
        }
        
        if(!wordcount) break;
        
        getchar();
        while(gets(input)){
            if(input[0]=='#') break;
            
            for(ptr=input;*ptr;){
                while(*ptr && (*ptr==' '||*ptr=='\t')) ptr++;
                if(*ptr==0) break;
                sscanf(ptr,"%s", words_input[count_words_input]);
                tobesorted[count_words_input]=words_input[count_words_input];
                count_words_input++;
                while(*ptr!=' ' && *ptr!='\t' && *ptr) ptr++;
            }
            
            qsort(tobesorted, count_words_input, sizeof(char*), cmp1);
            /*for(i=0;i<count_words_input;i++) printf("##  %s\n", tobesorted[i]);*/
            
            strcpy(trimmedinput, input);
            qsort(trimmedinput, strlen(trimmedinput), sizeof(char), cmp);
            space_cancel(trimmedinput);
            inputlen=strlen(trimmedinput);
            /*printf(" ### %s\n", trimmedinput);*/
            check_anagram(trimmedinput);
            count_words_input=0;
        }
        wordcount=0;
    }
    
    return 0;
}
