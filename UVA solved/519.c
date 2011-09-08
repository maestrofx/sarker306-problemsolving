#include<stdio.h>

char piece[40][6];
char value[128];
char pieces[120];
int puzzle[8][8];
int n, m, lim;
char flag;

int value_piece(char *piece){
    int i, x=0;

    for(i=0;piece[i];i++) x=3*x+value[piece[i]];

    return x;
}

int side(int piece, int x){ /* x= 0(top), 1( right), 2(bottom), 3(left) */
    int i, m=1;
    char tmp[5];

    for(i=0;i<4;i++, piece/=3) tmp[i]=piece%3;
    return tmp[3-x];
}

int next(int r, int c, int *arr){
    int x=0, i, j;
    char tmp[5]="XXXX";

    if(r==0) tmp[0]='F';
    if(r+1==m) tmp[2]='F';
    if(c==0) tmp[3]='F';
    if(c+1==n) tmp[1]='F';
    if(r) tmp[0]=value[3-side(puzzle[r-1][c],2)];
    if(c) tmp[3]=value[3-side(puzzle[r][c-1], 1)];

    for(i=1;i<3;i++){
        if(tmp[1]!='F') tmp[1]=value[i];
        for(j=1;j<3;j++){
            if(tmp[2]!='F') tmp[2]=value[j];
            /*printf("  %s", tmp);*/
            arr[x++]=value_piece(tmp);
        }
    }

    /*puts("");*/
    return x;
}

void print_state(){
    int i, j;

    puts("\n****************\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++) printf("%2d ", puzzle[i][j]);
        puts("");
    }

    puts("\n****************");
}

void backtrack(int r, int c){
    int i, x;
    int toPlace[10];

    if(r==m){
        flag=1;
        /*print_state();*/
        return ;
    }

    x=next(r, c, toPlace);
    for(i=0;i<x && flag==0;i++){
        if(pieces[toPlace[i]]){
            puzzle[r][c]=toPlace[i];
            pieces[toPlace[i]]--;
            /*print_state();*/
            if(c+1<n) backtrack(r, c+1);
            else backtrack(r+1, 0);
            pieces[toPlace[i]]++;
        }
    }

    puzzle[r][c]=-1;
}

void init_puzzle(){
    int i, j;

    for(i=0;i<m;i++) for(j=0;j<n;j++) puzzle[i][j]=-1;
    flag=0;
    for(i=0;i<81;i++) pieces[i]=0;
}

void solve(){
    if(precheck()) backtrack(0,0);
}

int precheck(){
    int i, j, resside=0, resO=0, resI=0, x;

    for(i=0;i<lim;i++){
        for(j=x=0;piece[i][j];j++){
            if(piece[i][j]=='F') x++;
            else if(piece[i][j]=='O') resO++;
            else if(piece[i][j]=='I') resI++;
            else return 0;
        }

        if(x) resside+=x;
    }

    if( resside!=2*(m+n)) return 0;
    if(resI!=resO) return 0;
    return 1;
}

int main(void){
    int i;
    char word[10];
    value['I']=1, value['F']=0, value['O']=2;
    value[0]='F', value[1]='I', value[2]='O';

    while(scanf("%d%d", &m, &n)!=EOF){
        if(m==0 && n==0) break;

        init_puzzle();
        for(i=0, lim=m*n;i<lim;i++){
            scanf("%s", piece[i]);
            pieces[value_piece(piece[i])]++;
        }

        solve();
        if(flag) puts("YES");
        else puts("NO");
    }

    return 0;
}
