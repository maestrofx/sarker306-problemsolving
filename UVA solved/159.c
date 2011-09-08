#include<stdio.h>
char a[15], b[15], c[15], d[15];
int lena, lenb, lenc, lend, coma, comb, comc, comd;

void printshit(){
    int i, j, x, y, z, p;
    
    if(comb>comd){
        for(j=0, y=0, x=comb-comd;j<x;j++){
            for(i=0;i<coma;i++) putchar(' ');
            putchar(b[j]);
            putchar('\n');
        }
        
        y=0;
    }
    else{
        for(j=0, x=0, y=comd-comb;j<y;j++){
            for(i=0;i<lena;i++) putchar(' ');
            printf("   ");
            for(i=0;i<comc;i++) putchar(' ');
            putchar(d[j]);
            putchar('\n');
        }
    }
    
    for(z=(comb>comd)?(comb-j):(comd-j), p=0; p<z;p++){
        for(i=0;i<coma;i++) putchar(' ');
        printf("%c", b[x++]);
        for(i++;i<lena;i++) putchar(' ');
        printf("   ");
        for(i=0;i<comc;i++) putchar(' ');
        putchar(d[y++]);
        putchar('\n');
    }
    printf("%s   %s\n", a, c);
    for(++y, ++x; b[x] && d[y]; x++, y++){
        for(i=0;i<coma;i++) putchar(' ');
        printf("%c", b[x]);
        for(i++;i<lena;i++) putchar(' ');
        printf("   ");
        for(i=0;i<comc;i++) putchar(' ');
        putchar(d[y]);
        putchar('\n');
    }
    
    if(b[x]){
        for(;b[x];x++){
            for(i=0;i<coma;i++) putchar(' ');
            putchar(b[x]);
            putchar('\n');
        }
    }
    else{
        for(;d[y];y++){
            for(i=0;i<lena;i++) putchar(' ');
            printf("   ");
            for(i=0;i<comc;i++) putchar(' ');
            putchar(d[y]);
            printf("\n");
        }
    }
}
    
int main(){
    int i, j, flag=0;
    
    while(scanf("%s", a)==1){
        if(a[0]=='#') break;
        scanf("%s%s%s", b, c, d);
        lena=strlen(a), lenb=strlen(b), lenc=strlen(c), lend=strlen(d);
        
        for(i=0, coma=-1;i<lena;i++){
            for(j=0, comb=-1;j<lenb;j++){
                if(a[i]==b[j]){
                    coma=i, comb=j;
                    break;
                }
            }
            if(comb!=-1) break;
        }
        
        for(i=0, comc=-1;i<lenc;i++){
            for(j=0, comd=-1;j<lend;j++){
                if(c[i]==d[j]){
                    comc=i, comd=j;
                    break;
                }
            }
            if(comd!=-1) break;
        }
        
        if(flag) printf("\n");
        flag=1;
        if(coma==-1 || comc==-1) printf("Unable to make two crosses\n");
        else printshit();
    }
    
    return 0;
}
