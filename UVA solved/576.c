#include<stdio.h>
#include<string.h>

int isvowel(char ch){ return (ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'||ch=='y'); }

int main(){
    char haiku[3][200], input[600];
    int i, j, syl[3];

    while(gets(input)){
        if(strcmp(input, "e/o/i")==0) break;
        strcpy(haiku[0],strtok(input, "/"));
        strcpy(haiku[1],strtok(0, "/"));
        strcpy(haiku[2],strtok(0, "/"));
        for(i=0;i<3;i++){
            syl[i]=0;
            for(j=0;haiku[i][j];j++){
                if(isvowel(haiku[i][j])){
                    if(haiku[i][j+1] && !isvowel(haiku[i][j+1])) syl[i]++;
                    else if(haiku[i][j+1]==0) syl[i]++;
                }
            }
        }

        if(syl[0]!=5) printf("1");
        else if(syl[1]!=7) printf("2");
        else if(syl[2]!=5) printf("3");
        if(syl[0]==5 && syl[1]==7 && syl[2]==5) printf("Y");
        puts("");
    }

    return 0;
}
