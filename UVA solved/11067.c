#include<stdio.h>

#define ERR -99999999
#define SIZE 105

long long unsigned ways[SIZE][SIZE];

int main()
{
    int tests, maxx, maxy, i, j, boo, num;
    long long unsigned sum;
    char ch;
    
    while(scanf("%d%d", &maxx, &maxy)!=EOF){
        if(maxx==0 && maxy==0) break;
        
        maxx++, maxy++;
        
        for(i=0;i<=maxx; i++){
            for(j=0;j<=maxy;j++){
                ways[i][j]=1;
            }
        }
            
        scanf("%d", &boo);
        for(;boo;boo--){
            scanf("%d%d", &i,&j);
            if(i>=0 && i<=100 && j>=0 && j<=100)ways[i][j]=0;
        }
        
        /*for(i=0;i<=maxx;i++){
            for(j=0;j<=maxy;j++){
                printf("%7d", ways[i][j]);
            }
            printf("\n");
        }*/
        
        for(i=0;i<maxx;i++){
            for(j=0;j<maxy;j++){
                if(i==0 && j==0) continue;
                sum=(i)?ways[i-1][j]:0;
                sum+=(j)?ways[i][j-1]:0;
                if(ways[i][j]) ways[i][j]=sum;
            }
        }
        
        /*printf("*****************\n");
        for(i=0;i<=maxx;i++){
            for(j=0;j<=maxy;j++){
                printf("%7d", ways[i][j]);
            }
            printf("\n");
        }*/
        
        if(ways[maxx-1][maxy-1]){
            if(ways[maxx-1][maxy-1]==1){
                printf("There is one path from Little Red Riding Hood's house to her grandmother's house.\n");
            }
            else printf("There are %I64d paths from Little Red Riding Hood's house to her grandmother's house.\n", ways[maxx-1][maxy-1]);
        }
        else printf("There is no path.\n");
    }
    
    return 0;
}
