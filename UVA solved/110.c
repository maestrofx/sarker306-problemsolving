#include<stdio.h>

void backtrack(char *a, int index, int n){
    int i, j;
    char ch=a[index];
    
    for(i=0;i<index;i++) printf("  ");
    if(index==n){
        printf("writeln(%c", a[0]);
        for(i=1;i<n;i++) printf(",%c", a[i]);
        printf(")\n");
        return;
    }
    
    printf("if %c < %c then\n", a[index-1], ch);
    backtrack(a, index+1, n);
    for(i=index-2;i+1;i--){
        a[i+1]^=a[i+2]^=a[i+1]^=a[i+2];
        for(j=0;j<index;j++) printf("  ");
        printf("else if %c < %c then\n", a[i], ch);
        backtrack(a, index+1, n);
    }
    for(i=0;i<index;i++) printf("  ");
    a[0]^=a[1]^=a[0]^=a[1];
    printf("else\n");
    backtrack(a, index+1, n);
    for(i=0;i<index;i++) a[i]=a[i+1];
    a[index]=ch;
}

void meta_sort(int n){
    char array[]="abcdefghijk";
    int i;
    
    printf("program sort(input,output);\nvar\n%c", array[0]);
    for(i=1;i<n;i++) printf(",%c", array[i]);
    printf(" : integer;\nbegin\n");
    printf("  readln(%c", array[0]);
    for(i=1;i<n;i++) printf(",%c", array[i]);
    printf(");\n");
    
    backtrack(array, 1, n);
    printf("end.\n");
}

int main(){
    int test, n;
    
    /*freopen("110.txt", "w", stdout);*/
    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d", &n);
            meta_sort(n);
            if(test) printf("\n");
        }
    }
    
    return 0;
}
