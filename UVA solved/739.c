#include<stdio.h>

char value[128];

void init(){
    value['A']=value['E']=value['I']=value['O']=value['U']=
        value['W']=value['Y']=value['H']=0;
    value['B']=value['P']=value['F']=value['V']=1;
    value['C']=value['S']=value['K']=value['G']=value['J']=
        value['Q']=value['X']=value['Z']=2;
    value['D']=value['T']=3;
    value['L']=4;
    value['M']=value['N']=5;
    value['R']=6;
}

int main(){
    char input[50];
    int i, flag, j;
    
    init();
    printf("         NAME                     SOUNDEX CODE\n");
    
    while(scanf("%s", input)!=EOF){
        printf("         %-25s", input);
        
        putchar(*input);
        
        for(i=1, flag=value[input[0]], j=0;input[i] && j<3;i++){
            if(value[input[i]]!=flag){
                flag=value[input[i]];
                if(flag){
                    printf("%d", flag);
                    j++;
                }
            }
        }
        
        while(j++<3) putchar('0');
        puts("");
    }
    
    printf("                   END OF OUTPUT\n");
    return 0;
}
