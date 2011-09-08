#include<stdio.h>

#define SIZE 335
#define min(x, y) (x<y)? x : y;

int main(){
	unsigned long long check2, check3, last, n, i, j=1, k, low, mid, high;
	unsigned long long  temp2, temp3, temp, humble[SIZE];
	int flag;
	humble[0]=0, humble[1]=1;
	check2=check3=1;
	temp2=2, temp3=3;
	for(i=2;j<SIZE;i++){
    	temp=min(temp2, temp3);
    	flag=1;
    	for(k=j;humble[k]>=temp;k--){
    		if(humble[k]==temp){
    			flag=0;
    			break;
    		}
    	}
    	if (flag==1){
    		j++;
    		humble[j]=temp;
    	}
    	if(temp==temp2){
    		last=2;
    		check2++;
    	}
    	else if(temp==temp3){
    		last=3;
    		check3++;
    	}
    	 if(last==3)
    		 temp3=humble[check3]*3;
    	 else if(last==2)
    		 temp2=humble[check2]*2;
    }
    
	scanf("%I64u", &n);
	while(n){
        low=0, high=SIZE-1, mid=(low+high)/2;
        while(humble[mid]>n || humble[mid+1]< n){
            if(humble[mid]<n) low=mid;
            if(humble[mid]>n) high=mid;
            mid=(low+high)/2;
        }
        if(humble[mid]==n) printf("%I64u\n", humble[mid]);
        else printf("%I64u\n", humble[mid+1]);
		scanf("%I64u", &n);
    }
	return 0;
}
