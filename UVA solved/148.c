#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXWORD 2002
#define WORDSIZE 50
#define MAXLETTER 26

char dictionary[MAXWORD+1][WORDSIZE+2];
int dictionarywordsize[MAXWORD+1][MAXLETTER+2];
int wordcount;
int comb[WORDSIZE+3];
char input[WORDSIZE*2];
int inputwordsize[MAXLETTER+2];
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
	int wordlettersize[MAXLETTER+2];
    
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
    
	for(i=0;i<MAXLETTER;i++) wordlettersize[i]=0;
	for(i=0;word[i];i++) wordlettersize[word[i]-'A']++;
    for(i=index;i<size;i++){
        lentmp=len;
        len+=dictionarywordsize[i][MAXLETTER];
        if(len<=inputlen) {
			for(j=0;j<MAXLETTER;j++) if(wordlettersize[j]+dictionarywordsize[i][j]>inputwordsize[j]) break;
			if(j==MAXLETTER){
                strcpy(temp, word);
                strcat(word, dictionary[i]);
                comb[comb_index]=i;
                backtrack(word, len, comb_index+1, i+1, size, str);
                strcpy(word, temp);
            }
        }
        len=lentmp;
    }
}

void check_anagram(const char *str){
    int i, ln;
    char temp[WORDSIZE*2];
    
    for(i=0;i<wordcount;i++){
        strcpy(temp, dictionary[i]);
        ln=dictionarywordsize[i][MAXLETTER];
        comb[0]=i;
        if(ln<=inputlen) backtrack(temp, ln,1,  i+1, wordcount, str);
    }
}

int main(){
    int i,j;
    char trimmedinput[WORDSIZE+3], *ptr, a;
    
    for(;;){
        while(scanf("%s", dictionary[wordcount])!=EOF){
            if(dictionary[wordcount][0]=='#') break;
            for(i=0;i<MAXLETTER;i++) dictionarywordsize[wordcount][i]=0;
			for(i=0;(a=dictionary[wordcount][i]);i++) dictionarywordsize[wordcount][a-'A']++;
            dictionarywordsize[wordcount][MAXLETTER]=i;
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
            
            strcpy(trimmedinput, input);
            qsort(trimmedinput, strlen(trimmedinput), sizeof(char), cmp);
            space_cancel(trimmedinput);
            for(i=0;i<MAXLETTER;i++) inputwordsize[i]=0;
			for(i=0;(a=trimmedinput[i]);i++) inputwordsize[a-'A']++;
            inputlen=i;
            check_anagram(trimmedinput);
            count_words_input=0;
        }
        wordcount=0;
    }
    
    return 0;
}
