#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#define SIZE 30
using namespace std;

typedef struct pos{
    char num[SIZE];
}pos;

class cmp{
public:
    bool operator( ) (const pos &a, const pos &b){
        int x, y, res = 0;

        for(x = y = 0; a.num[x] && b.num[y] ; x++, y++){
            if( res == 0 && a.num[x] != b.num[y]){
                res = a.num[x] - b.num[y];
            }
        }

        if( a.num[x] || b.num[y] ){
            while(a.num[x]) x++;
            while(b.num[y]) y++;
        }

        if( x != y ) return x < y ? true : false;
        else return res < 0 ? true : false;
    }
};

priority_queue< pos, vector<pos>, cmp >que;
set<string>visited;
char flag;

void zero_cancel(char *num){
	int zero = 0, i, j;

	while(num[zero] == '0') zero++;
	if(zero) for(i = zero, j = 0 ; num[i-1] != '\0' ; i++, j++) num[j] = num[i];
	if(num[0] == 0) num[1] = 0, num[0] = '0';
}

void divide(char *num, int n){
    int i, res, mod;
    pos u;

    for( i = mod = 0 ; num[i] ; i++ ){
        res = 10 * mod + (num[i] - '0');
        u.num[i] = res / n + '0';
        mod = res % n;
    }

    u.num[i] = 0;
    if(mod) return;
    zero_cancel(u.num);
    string str = u.num;
    if(visited.find(str) == visited.end()){
        visited.insert(str);
        que.push(u);
    }

    flag = 1;
}

void remove(char *num, char ch){
    int i, j;

    for(i = 0 ; num[i] ; i++ ){
        if(num[i] == ch){
            pos u;

            for( j = 0 ; j < i ; j++ ) u.num[j] = num[j];
            for( j = i + 1 ; num[j] ; j++ ) u.num[j - 1] = num[j];
            u.num[j - 1] = 0;
            zero_cancel(u.num);
            string str = u.num;
            if(visited.find(str) == visited.end()){
                visited.insert(str);
                que.push(u);
            }

            flag = 1;
            while(num[i] && num[i] == ch) i++;
            i--;
        }
    }
}

void remove_times(char *num, int n){
    int i, j, k;

    for( i = 0 ; num[i] ; i++ ){
        for( j = 1 ; j < n && num[i + j] ; j++ ) if(num[i + j] != num[i + j - 1]) break;
        if( j == n ){
            pos u;

            for( k = 0 ; k < i ; k++ ) u.num[k] = num[k];
            for( k = i + n ; num[k]; k++) u.num[k - n] = num[k];
            u.num[k - n] = 0;
            zero_cancel(u.num);
            string str = u.num;
            if(visited.find(str) == visited.end()){
                visited.insert(str);
                que.push(u);
            }

            flag = 1;
        }

        i += j - 1;
    }
}

void solve(void){
    while(que.empty() == false){
        pos u = que.top();
        flag = 0;
        divide(u.num, 3);
        divide(u.num, 7);
        remove(u.num, '3');
        remove(u.num, '7');
        remove_times(u.num, 3);
        remove_times(u.num, 7);

        if(flag == 0){
            printf("%s\n", u.num);
            return;
        }

        que.pop();
    }

    puts("0");
}

int main(){
    int test;
    char num[SIZE];

    scanf("%d", &test);
    while( test-- ){
        pos start;
        scanf("%s", start.num);
        que.push(start);
        string str = num;
        visited.insert(str);
        solve();
        while(que.empty() == false) que.pop();
        visited.clear();
    }

    return 0;
}
