#include<cstdio>
#include<iostream>
#include<set>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;

set<string>set1;
set<string>set2;
set<string>::iterator puh, puuh;
char grid1[5][5], grid2[5][5];
int xdir[]={-1,-1,-1,0,0,1,1,1};
int ydir[]={-1,0,1,-1,1,-1,0,1};
int f;

int safe(char *str){
	int flag=0;
	
	for(;*str;str++){
		if(*str=='A' || *str=='E' || *str=='I' || *str=='O' || *str=='U' || *str=='Y')
		flag++;
	}
	
	return (flag==2)?1:0;
}

void backtrack(char grid[][5], char *str, int *a, int index, int x, int y){
	int i, j, xx, yy;
	string ss;
	
	if(index==4){
		if(safe(str)){
            str[index]=0;
            ss.assign(str, 0, 4);
            //cout<<ss<<endl;
            if(f==0) set1.insert(ss);
            else set2.insert(ss);
        }
		return;
	}
	
	for(i=0;i<8;i++){
		xx=x+xdir[i], yy=y+ydir[i];
		if(xx>=0 && xx<4 && yy>=0 && yy<4){
            for(j=0;j<index;j++) if(a[j]==4*xx+yy) break;
            if(j<index) continue;
			str[index]=grid[xx][yy];
			a[index]=4*xx+yy;
			backtrack(grid, str, a, index+1, xx, yy);
		}
	}
}

void list_words(char grid[][5]){
	int i, j;
	char str[6];
	int pos[5];
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			str[0]=grid[i][j];
			pos[0]=i*4+j;
			backtrack(grid, str, pos, 1, i, j);
		}
	}
}

int main(){
    int i, j, test=0;
    char ch, str[50], *p;
    
    while(gets(str)){
        if(str[0]=='#') break;
        f=0;
        if(str[0]==0) continue;
        for(i=0, p=str;i<4;p++){
            ch=*p;
            if(ch>='A' && ch<='Z') grid1[0][i++]=ch;
        }
        
        for(i=0;i<4;p++){
            ch=*p;
            if(ch>='A' && ch<='Z') grid2[0][i++]=ch;
        }
        
        for(j=1;j<4;j++){
            gets(str);
            for(i=0, p=str;i<4;p++){
                ch=*p;
                if(ch>='A' && ch<='Z') grid1[j][i++]=ch;
            }
            
            for(i=0;i<4;p++){
                ch=*p;
                if(ch>='A' && ch<='Z') grid2[j][i++]=ch;
            }
        }
        
        list_words(grid1);
        f=1;
        list_words(grid2);
        if(test++) printf("\n");
        for(puh=set1.begin(), f=0; puh!=set1.end();puh++){
            puuh=set2.find(*puh);
            if(puuh!=set2.end()){
                f=1;
                cout<<*puh<<endl;
            }
        }
        
        if(f==0) printf("There are no common words for this pair of boggle boards.\n");
        set1.clear();
        set2.clear();
    }
    
    return 0;
}
