#include<stdio.h>
#include<string.h>

#define SIZE 1005
#define LEN 700

void int_str_mult(char *A, long n, char *B){
    long carry=0, i, x, j, prod;
    char p[100]={0};
    x=strlen(A);
    for(i=x-1; i+1;i--){
        prod=(A[i]-'0')*n+carry;
        B[i]=prod%10+'0';
        carry=prod/10;
    }
    B[x]=0;
    if(carry){
        prod=carry;
        for(j=0;prod;j++, prod/=10) p[j]=prod%10+'0';
        for(i=x;i+1;i--) B[i+j]=B[i];
        j--;
        for(i=0;j>=0;j--, i++) B[i]=p[j];
    }
}

void int_str_div(char *A, long n, char *B){
	long i, j, flag=0, value, res=0;
	
	for(i=0, j=0;A[i];i++){
		res=10*res+A[i]-'0';
		value=res/n;
		if(!flag && value) flag=1;
		if(flag) B[j++]=value+'0';
		res%=n;
	}
	
	if(!flag) B[j++]='0';
	B[j]=0;
}

char catalan[SIZE+5][LEN+5];
char temp[LEN+5];

int main(){
	long n, i;
	
	strcpy(catalan[0], "1");
	for(i=1;i<=SIZE;i++){
		int_str_mult(catalan[i-1], 2*(2*i-1), temp);
		int_str_div(temp, i+1, catalan[i]);
	}
	
	while(scanf("%ld", &n)!=EOF){
		if(n>SIZE || n<0) printf("ERROR!\a\n");
		else printf("%s\n", catalan[n]);
	}
	
	return 0;
}
