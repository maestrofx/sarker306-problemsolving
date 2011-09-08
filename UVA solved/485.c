#include<stdio.h>

void int_str_mult(char *A, long n, char *B){
    long carry=0, i, x, j, prod;
    char p[200]={0};
    
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
    long i, res;
    
    for(i=0, res=0; A[i];i++){
        res=res*10+A[i]-'0';
        B[i]=res/n+'0';
        res%=n;
    }
    
    B[i]=0;
    for(i=0;B[i]=='0';i++);
    for(res=0;B[i];res++, i++) B[res]=B[i];
    B[res]=0;
}

int main(){
    char A[100], B[100], temp[100];
    int i, j, n=0;
    
    printf("1\n");
    for(i=1; i<205 ;i++){
        strcpy(A, "1");
        printf("1");
        for(j=1;j<=i;j++){
            int_str_mult(A, i-j+1, B);
            int_str_div(B, j, A);
            printf(" %s", A);
        }
        
        printf("\n");
    }
    
    return 0;
}
