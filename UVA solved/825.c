#include<stdio.h>

#define ERR -99999999
#define SIZE 105

long long unsigned ways[SIZE][SIZE];

int main()
{
    int tests, maxx, maxy, i, j, boo, num;
    long long unsigned sum;
    char ch;
    
    scanf("%d", &tests);
    for(;tests; tests--){
        scanf("%d%d", &maxx, &maxy);
        
        for(i=1;i<=maxx; i++){
            ways[i][0]=0;
            for(j=1;j<=maxy;j++){
                ways[i][j]=1;
            }
            scanf("%d", &boo);
            num=0;
            while((ch=getchar())!=EOF){
                if(ch>='0' && ch<='9'){
                    num=10*num+ch-'0';
                }
                else{
                    if(num) ways[boo][num]=0;
                    num=0;
                    if(ch=='\n') break;
                }
            }
        }
        
        for(i=1;i<=maxx;i++){
            for(j=1;j<=maxy;j++){
                if(i==1 && j==1) continue;
                sum=(i-1)?ways[i-1][j]:0;
                sum+=(j-1)?ways[i][j-1]:0;
                if(ways[i][j]) ways[i][j]=sum;
            }
        }
        
        /*for(i=0;i<=maxx;i++){
            for(j=0;j<=maxy;j++){
                printf("%3d", ways[i][j]);
            }
            printf("\n");
        }*/
        
        printf("%I64u\n", ways[maxx][maxy]);
        if(tests>1) printf("\n");
    }
    
    return 0;
}
