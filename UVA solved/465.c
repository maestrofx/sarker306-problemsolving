#include<stdio.h>
#include<ctype.h>
#include<string.h>

char input[100000], one[50000], two[50000], res[50], limit[50], op;

void zero_cancel(char *a){
	int zero=0, i, j;
	
	while(a[zero]=='0') zero++;
	if(zero){
		for(i=zero,j=0;a[i-1]!='\0';i++, j++) a[j]=a[i];
	}
	
	if(a[0]==0) a[0]='0', a[1]=0;
	return;
}

int cmp_num(char *a, char *b){
    int diff=strlen(a)-strlen(b);
    
    if(diff) return diff;
    return strcmp(a, b);
}

int main(){
    int i, j;
    long long x, y, z, lim=(1<<31)-1;
    
    sprintf(limit, "%lld", lim);
    
    while(gets(input)){
        for(i=0, j=0; isalnum(input[i]) ; i++, j++) one[j]=input[i];
        one[j]=0;
        
        for(; input[i]!='+' && input[i]!='*'; i++);
        op=input[i];
        
        for(; !isalnum(input[i]); i++);
        
        for(j=0; input[i] && isalnum(input[i]) ; i++, j++) two[j]=input[i];
        two[j]=0;
        
        zero_cancel(one);
        zero_cancel(two);
        
        printf("%s\n", input);
        
        x=-1, y=-1;
        if(cmp_num(one, limit)<=0){
            sscanf(one, "%lld", &x);
        }
        else printf("first number too big\n");
        
        if(cmp_num(two, limit)<=0){
            sscanf(two, "%lld", &y);
        }
        else printf("second number too big\n");
        
        if(x!=-1 && y!=-1){
            if(op=='*') z=x*y;
            else z=x+y;
            if(z>lim) printf("result too big\n");
        }
        else if(x && y) printf("result too big\n");
    }
    
    return 0;
}
