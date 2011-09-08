#include<stdio.h>
#include<string.h>

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

char array[500], temp[500];
long n, i, m;

int main(){
	while(scanf("%ld%ld", &m, &n)!=EOF){
		if(m==0 && n==0) break;
		sprintf(array, "1");
		if(m!=1) for(i=0;i<n;i++){
			int_str_mult(array, m, temp);
			strcpy(array, temp);
		}
		printf("%s\n", array);
	}
	
	return 0;
}
