#include<stdio.h>

long array[52];

int main(){
	char ch;
	int i;
	long max;
	
	while((ch=getchar())!=EOF){
		if(ch>='A' && ch<='Z') array[ch-'A']++;
		else if(ch>='a' && ch<='z') array[ch-'a'+26]++;
		else if(ch=='\n'){
			for(i=0, max=0; i<52;i++) max=(max>array[i])? max : array[i];
			for(i=0;i<26;i++){
				if(array[i]==max) putchar(i+'A');
				array[i]=0;
			}
			for(   ;i<52;i++){
				if(array[i]==max) putchar(i+'a'-26);
				array[i]=0;
			}
			printf(" %ld\n", max);
		}
	}
	
	return 0;
}
