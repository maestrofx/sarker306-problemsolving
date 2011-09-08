#include<stdio.h>
#include<string.h>

#define SIZE 1001

int palindrome[SIZE][SIZE];

int len_longpalin(char *a, int x, int y)
{
    int i, j, m, n;
    
    if(x>y) return 0;
    if(palindrome[x][y]) return palindrome[x][y];
    
    if(x==y){
        palindrome[x][y]=1;
    }
    
    /*if(palindrome[x][y]) return palindrome[x][y];
    if(!palindrome[x][y])for(i=x, j=y; i<=j; i++, j--){
        if(a[i]!=a[j]) break;
    }
    
    if(i>j){
        if(!palindrome[x][y]) palindrome[x][y]=y-x+1;
    }
    else{
        m=len_longpalin(a, x+1, y);
        n=len_longpalin(a, x, y-1);
        palindrome[x][y]=(m>n)? m:n;
    }*/
    else if(a[x]==a[y]){
        palindrome[x][y]=len_longpalin(a, x+1, y-1)+2;
    }
    else{
        m=len_longpalin(a, x+1, y);
        n=len_longpalin(a, x, y-1);
        palindrome[x][y]=(m>n)? m:n;
    }
    
    return palindrome[x][y];
}

int main()
{
    char array[SIZE];
    int n, i, j, len;
    
    scanf("%d", &n);
    gets(array);
    for(;n;n--){
        gets(array);
        len=strlen(array);
        printf("%d\n", (len)?len_longpalin(array, 0, len-1):0);
        
        for(i=0;i<len;i++){
            for(j=0;j<len;j++){
                palindrome[i][j]=0;
            }
        }
    }
    
    return 0;
}
