#include<stdio.h>
#include<string.h>

char array[128];

int IsPalindrome(char *a, int len){
	int i, j;
	
	for(i=0, j=len-1; i<=j;i++, j--){
		if(a[i]!=a[j]) break;
	}
	
	return (i>j)? 1: 0;
}

int IsMirror(char *a, int len){
	int i, j;
	
	for(i=0, j=len-1; i<=j;i++, j--){
		if(array[a[i]]!=a[j]) break;
	}
	
	return (i>j)? 2 : 0;
}

int main(){
	char string[10000];
	int len;
	
	array['A']='A', array['E']='3', array['H']='H', array['I']='I', array['J']='L', array['L']='J', array['M']='M', array['O']='O', array['S']='2', array['T']='T', array['U']='U', array['V']='V', array['W']='W', array['X']='X', array['Y']='Y', array['Z']='5', array['1']='1', array['2']='S', array['3']='E', array['5']='Z', array['8']='8';
	
	
	while(scanf("%s", string)!=EOF){
		len=strlen(string);

		switch(IsPalindrome(string, len)|IsMirror(string, len)){
			case 0: printf("%s -- is not a palindrome.\n\n", string); break;
			case 1: printf("%s -- is a regular palindrome.\n\n", string); break;
			case 2: printf("%s -- is a mirrored string.\n\n", string); break;
			case 3: printf("%s -- is a mirrored palindrome.\n\n", string); break;
		}
	}
	
	return 0;
}
