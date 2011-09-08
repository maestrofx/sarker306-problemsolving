#include<stdio.h>
#include<string.h>

char name[][30]={"Tanveer Ahsan", "Shahriar Manzoor", "Adrian Kugel", "Anton Maydell", "Derek Kisman", "Rezaul Alam Chowdhury", "Jimmy Mardell", "Monirul Hasan", "K. M. Iftekhar"};
int mod[9]={2,5,7,11,15,20,28,36};
int res[9]={0,3,6,3,3,8,20,24};

void zero_cancel(char *A){
	int zero=0, i, j;
	while(A[zero]=='0') zero++;
	if(zero){
		for(i=zero,j=0;A[i-1]!='\0';i++, j++) A[j]=A[i];
	}
	return;
}

int main(){
    char str[55], ch;
    int rem[9], i, j, test=0, mod4, mod100, mod400, flag;
    
    while(scanf("%s", str)!=EOF){
        zero_cancel(str);
        for(i=0;i<8;i++) rem[i]=0;
        mod4=mod100=mod400=flag=0;
        
        for(i=0;str[i];i++){
            ch=str[i]-'0';
            if(!flag && ch) flag=1;
            for(j=0;j<8;j++) rem[j]=(10*rem[j]+ch)%mod[j];
            mod4=(10*mod4+ch)%4, mod400=(10*mod400+ch)%400, mod100=(10*mod100+ch)%100;
        }
        
        if(!flag) break;
        if(test++) printf("\n");
        printf("%s\n", str);
        flag=0;
        if(strlen(str)>4) flag=1;
        else if(strcmp(str, "2148")>=0) flag=1;
        if(flag){
            for(i=0, flag=0;i<8;i++) if (rem[i]==res[i]) printf("Ghost of %s!!!\n", name[i]), flag++;
            if((mod100 && !mod4) || !mod400) printf("Ghost of %s!!!\n", name[8]), flag++;
        }
        if(!flag) printf("No ghost will come in this year\n");
    }
    
    return 0;
}
