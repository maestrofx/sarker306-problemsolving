#include<stdio.h>
#define SIZE 1000000

char array[SIZE+5];
char temp[SIZE+5];

int main(){
    long i, j, test=1, n;
    
    while(gets(array)){
		if(array[0]==0) break;
		for(i=j=0; array[i]; i++){
			if(array[i]==array[j]) temp[i]=j;
			else temp[i]=j=i;
		}
		scanf("%ld", &n);
		printf("Case %ld:\n", test++);
		while(n--){
			scanf("%ld%ld", &i, &j);
			if(i>j) i^=j^=i^=j;
			printf("%s\n", (temp[i]==temp[j])? "Yes":"No");
		}
		getchar();
	}
	
	return 0;
}
