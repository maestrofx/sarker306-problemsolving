#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(){
	int hh, mm, a;
	
	scanf("%d", &a);
	while(a--){
		scanf("%d:%d", &hh, &mm);
		if(mm==0) hh=12-hh;
		else{
			if(hh==12) hh=0;
			hh=11-hh;
			mm=60-mm;
		}
		
		if(mm==60) mm=0, hh=(hh+1)%12;
		if(hh==0) hh=12;
		printf("%02d:%02d\n", hh, mm);
	}
	
    return 0;
}
