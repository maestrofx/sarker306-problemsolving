#include<stdio.h>

#define SIZE 32

typedef struct{
    long long val;
    char hor, ver;
}grid;

grid nway[SIZE][SIZE];

void init(void){
    int i, j;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            nway[i][j].val=0;
            nway[i][j].hor=nway[i][j].ver=0;
        }
    }

    return;
}

int main(){
    int test, n_road;
    int stx, sty, endx, endy;
    long w;
    int i, j, l;
    int x, y;
    char dir[5];

    /*freopen("data.txt", "rt", stdin);*/
    scanf("%d", &test);
    for(l=0;l<test;l++){
        if(l)init();
        scanf("%d", &n_road);
        scanf("%d%d%d%d", &stx, &sty, &endx, &endy);
        scanf("%ld", &w);
        while(w--){
            scanf("%d%d%s", &x, &y, dir);
            switch(dir[0]){
                case 'S': --y;
                case 'N': nway[x][y].hor=1; break;
                case 'W': --x;
                case 'E': nway[x][y].ver=1; break;
            }
        }

        nway[stx][sty].val=1;
        for(i=stx;i<SIZE;i++){
            nway[i+1][sty].val=nway[i][sty].val*(nway[i][sty].ver==0);
        }
        for(i=sty;i<SIZE;i++){
            nway[stx][i+1].val=nway[stx][i].val*(nway[stx][i].hor==0);
        }

        for(i=stx+1; i<=endx; i++){
            for(j=sty+1; j<=endy;j++){
                nway[i][j].val=nway[i-1][j].val*(nway[i-1][j].ver==0)+nway[i][j-1].val*(nway[i][j-1].hor==0);
            }
        }

        /*for(i=stx;i<=endy;i++){
            for(j=endy;j>=sty;j--){
                printf("%3I64d", nway[i][j].val);
            }
            printf("\n");
        }*/

        printf("%lld\n", nway[endx][endy].val);
    }

    return 0;
}
