#include<stdio.h>

int m, n, lim;
char value[128];
char piece[100][5], puzzle[9][9], used[100], flag;
/* pieces .. [0]-> top , [1]-> right, [2]->bottom, [3]->left */

int placable(int rank, int r, int c){
    if(r==0 && piece[rank][0]!='F') return 0;
    if(r==m-1 && piece[rank][2]!='F') return 0;
    if(c==0 && piece[rank][3]!='F') return 0;
    if(c==n-1 && piece[rank][1]!='F') return 0;
    if(r!=0 && piece[rank][0]=='F') return 0;
    if(r!=m-1 && piece[rank][2]=='F') return 0;
    if(c!=0 && piece[rank][3]=='F') return 0;
    if(c!=n-1 && piece[rank][1]=='F') return 0;

    if(r>0 && value[piece[puzzle[r-1][c]][2]]+value[piece[rank][0]]!=3) return 0;
    if(c>0 && value[piece[puzzle[r][c-1]][1]]+value[piece[rank][3]]!=3) return 0;
    return 1;
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
    int i, j;

    if(r==m){
        flag=1;
       /* print_state();*/
        return ;
    }

    for(i=0;i<lim && flag==0;i++){
        if(used[i]==0 && placable(i, r, c)){
            puzzle[r][c]=i;
            used[i]=1;
            if(c+1<n) backtrack(r, c+1);
            else backtrack(r+1, 0);
          /*  print_state();*/
            used[i]=0;
        }
    }

    puzzle[r][c]=-1;
}

void init_puzzle(){
    int i, j;

    for(i=0;i<lim;i++) used[i]=0;
    for(i=0;i<m;i++) for(j=0;j<n;j++) puzzle[i][j]=-1;
    flag=0;
}

int precheck(){
    int i, j, rescorner=0, resside=0, resO=0, resI=0, x;

    for(i=0;i<lim;i++){
        for(j=x=0;piece[i][j];j++){
            if(piece[i][j]=='F') x++;
            else if(piece[i][j]=='O') resO++;
            else if(piece[i][j]=='I') resI++;
            else return 0;
        }

        if(x>=2) rescorner++;
        if(x) resside+=x;
    }

    /*if( rescorner==1 && m!=1 && n!=1) return 0;
    if( rescorner==2 && (m!=1 || n!=1)) return 0;
    if( rescorner!=4 ) return 0;*/
    if( resside!=2*(m+n)) return 0;
    if(resI!=resO) return 0;
    return 1;
}

void solve(){
    if(precheck()) backtrack(0,0);
}

int main(){
    int i;

    value['I']=1, value['F']=0, value['O']=2;
    while(scanf("%d%d", &m, &n)!=EOF){
        if(m==0 && n==0) break;
        for(i=0, lim=m*n;i<lim;i++) scanf("%s", piece[i]);
        init_puzzle();
        solve();
        if(flag) puts("YES");
        else puts("NO");
    }

    return 0;
}
/*
3 3
IIII
OFFO
FIIF
OIFI
IFIO
OOIF
FOOO
FFOI
OOFF
3 5
FOOI
IOOI
FFOI
FOOI
IOOF
IOOI
FOOI
FOOF
IFOI
IOFI
IOOI
IOFF
IOFI
IFFI
IOFI
6 6
OFFI
OFIO
OFII
IFII
OFOO
FFII
OOFI
OIII
IOII
OOOI
IIIO
FOOO
OOFO
OOII
OOIO
IOII
OIOI
FIII
OIFI
IOII
IIOI
IOOI
OOOO
FOIO
IOFO
OOOO
IOIO
OOOI
IIII
FIOI
IIFF
OIOF
OIIF
IOIF
OOOF
FOIF
*/
