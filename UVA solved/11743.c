#include<stdio.h>

int digit_sum[]={0,2,4,6,8,1,3,5,7,9};

int main(){
    int t,i,sum;
    char grp[5];
    
    while(scanf("%d",&t)==1){
        while(t--){
            sum=0;
            for (i=0; i<4; i++){
                scanf("%s",grp);
                sum+= digit_sum[grp[0]-'0']+digit_sum[grp[2]-'0']+grp[1]+grp[3]-'0'-'0';
            }
            
            if (sum%10) printf("Invalid\n");
            else printf("Valid\n");
        }
    }
    
    return 0;
}
