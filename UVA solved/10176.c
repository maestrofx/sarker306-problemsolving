#include<stdio.h>

int main(){
	long rem=0;
	char ch;
	
	while((ch=getchar())!=EOF){
		if(ch=='#'){
			printf("%s\n", (!rem)?"YES":"NO");
			rem=0;
		}
		else if(ch>='0' && ch<='9') rem=(2*rem+ch-'0')%131071;
	}
	
	return 0;
}
