#include<stdio.h>
#include<string.h>

char grid1[15][15], grid2[15][15];
int n;

int rotate90(char grid1[][15]){
    int i, j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid1[i][j]!=grid2[j][n-i-1]) return 0;
        }
    }

    return 1;
}

int rotate180(char grid1[][15]){
    int i, j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid1[i][j]!=grid2[n-i-1][n-j-1]) return 0;
        }
    }

    return 1;
}

int rotate270(char grid1[][15]){
    int i, j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid1[i][j]!=grid2[n-j-1][i]) return 0;
        }
    }

    return 1;
}

int rotate0(char grid1[][15]){
    int i, j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid1[i][j]!=grid2[i][j]) return 0;
        }
    }

    return 1;
}

int reflect(char grid1[][15]){
    int i, j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid1[i][j]!=grid2[n-i-1][j]) return 0;
        }
    }

    return 1;
}

int combination(char grid1[][15]){
    int i, j;
    char temp[15][15];

    for(i=0;i<n;i++) strcpy(temp[i], grid1[n-i-1]);
    if(rotate90(temp)) return 11;
    if(rotate180(temp)) return 12;
    if(rotate270(temp)) return 13;
}

int check(char grid1[][15]){
    int x;

    if(rotate0(grid1)) return 6;
    if(rotate90(grid1)) return 1;
    if(rotate180(grid1)) return 2;
    if(rotate270(grid1)) return 3;
    if(reflect(grid1)) return 4;
    if(x=combination(grid1)) return x;
    return 0;
}

int main(){
    int i, test=1;

    while(scanf("%d", &n)!=EOF){
        for(i=0;i<n;i++) scanf("%s%s", grid1[i], grid2[i]);
        switch(check(grid1)){
            case 1: printf("Pattern %d was rotated 90 degrees.\n", test); break;
            case 2: printf("Pattern %d was rotated 180 degrees.\n", test); break;
            case 3: printf("Pattern %d was rotated 270 degrees.\n", test); break;
            case 4: printf("Pattern %d was reflected vertically.\n", test); break;
            case 6: printf("Pattern %d was preserved.\n", test); break;
            case 11: printf("Pattern %d was reflected vertically and rotated 90 degrees.\n", test); break;
            case 12: printf("Pattern %d was reflected vertically and rotated 180 degrees.\n", test); break;
            case 13: printf("Pattern %d was reflected vertically and rotated 270 degrees.\n", test); break;
            default: printf("Pattern %d was improperly transformed.\n", test); break;
        }

        test++;
    }

    return 0;
}
