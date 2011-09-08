#include<stdio.h>
#include<string.h>

long nsol;
char array[50];
int in_comb[129];
int a[50];

void comb(int a[], int index, int used, int ln){
    register int i, j, tmp;

    if(used==ln){
        for(i=0;i<26;i++){
            for(j=0;j<a[i];j++) putchar(i+'a');
        }
        puts("");
        nsol++;
        return;
    }

    for(i=index;i<26;i++){
		for( j=in_comb[i];j>0;j--){
            tmp=a[i];
            a[i]=j;
            if(used+j<=ln) comb(a, i+1, used+j, ln);
            a[i]=tmp;
        }
    }
}

int main(){
    int i, n;

    while(scanf("%s%d", array, &n)!=EOF){
		for(i=0;i<26;i++) in_comb[i]=0;
		for(i=0;array[i];i++) in_comb[array[i]-'a']++; /* lowercase only */
		nsol=a[0]=0;
		comb(a, 0, 0, n);
    }

    return 0;
}
