#include<stdio.h>

long time[10005];

int main(){
    int m[3], t, i, j;
    
    m[0]=0;
    while(scanf("%d%d%d", &m[1], &m[2], &t)!=EOF){
        for(i=0;i<=t;i++) time[i]=0;
        time[0]=0;
        for(i=1;i<3;i++){
            if(m[i]==m[i-1]) break;
            for(j=m[i], time[m[i]]++;j<=t;j++){
                if(time[j-m[i]]) time[j]=(time[j]>time[j-m[i]]+1)?time[j]:time[j-m[i]]+1;
            }       
            /*for(j=0;j<=t; j++) printf("%2d - %2d\n", j, time[j]);*/
        }
        
        if(time[t]) printf("%d\n", time[t]);
        else{
            for(j=t-1;time[j]==0 && j>=0;j--);
            if(j<0) j++;
            printf("%d %d\n", time[j], t-j);
        }
    }
    
    return 0;
}
