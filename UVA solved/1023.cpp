#include <cstdio>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define ALL(v) (v).begin(), (v).end()
#define SET(a, x) memset((a), (x), sizeof(a))
#define SZ(a) ((int)(a).size())
#define CL(a) ((a).clear())
#define SORT(x) sort(ALL(x))
#define mp make_pair
#define pb push_back
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

struct Node{
	int col;
	int isLeaf;
	int level;
	char sub[405];
	Node *child[4];

	void init (){
		isLeaf = 0;
		col = 0;
		level = 0;
		for ( int i = 0 ; i < 4 ; i++ ) child[i] = 0;
	}

	Node (int c){
		isLeaf = 0;
		col = c;
		level = 0;
		for ( int i = 0 ; i < 4 ; i++ ) child[i] = 0;
	}
};

struct Tree{
	Node *root;
};

vector<char> img1, img2;
Tree h1, h2;
unsigned val[128];

int len;

Node* S(vector<char> &img, int lvl){
	Node *nd = (Node*) malloc(sizeof(Node));
	nd->init();
	nd->level = lvl;
	
	if ( img[len] == '1' ){
		len++;
		nd->isLeaf = 1;
		nd->col = img[len];
		strcpy(nd->sub, ( img[len] == '1' ) ? "11" : "10");
		len++;
	} else {
		len++;
		nd->sub[0] = '0';
		nd->sub[1] = 0;
		for ( int i = 0 ; i < 4 ; i++ ){
			nd->child[i] = S(img, lvl + 1);
			strcat(nd->sub, nd->child[i]->sub);
		}
	}

	return nd;
}

void walk(Node *h){
	if ( h == 0 ) return;
	
	cout << h->sub << ' ' << h->level << endl;
	for ( int i = 0 ; i < 4 ; i++ ) walk(h->child[i]);
}

void merge(Node *h1, Node *h2, char *outStr){
	char temp[20000];
	
	if ( h1->isLeaf && h2->isLeaf ){
	//	puts("Leaf leaf");
		if (( h1->col & h2->col ) == '0') strcat(outStr, "10");
		else strcat(outStr, "11");
	}
	else if ( h1->isLeaf == 0 && h2->isLeaf == 0 ){
	//	puts("Aha");
		temp[0] = 0;
		for ( int i = 0 ; i < 4 ; i++ ){
			char intermed[10000];
			intermed[0] = 0;
			merge(h1->child[i], h2->child[i], intermed);
			strcat(temp, intermed);
		}
		if ( strcmp(temp, "10101010") == 0 ){
			strcat(outStr, "10");
		}
		else{
			strcat(outStr, "0");
			strcat(outStr, temp);
		}
	}
	else{
	//	puts("Non Leaf Leaf");
		if ( h1->isLeaf ){
			if ( h1->col == '0' ){
				strcat(outStr, "10");
			}
			else{
				strcat(outStr, h2->sub);
			}
		}
		else {
			if ( h2->col == '0' ){
				strcat(outStr, "10");
			}
			else{
				strcat(outStr, h1->sub);
			}
		}
	}
	
	//cout << outStr << endl;
}

void clearImage(Node *h){
	if ( h == 0 ) return;
	for ( int i = 0 ; i < 4 ; i++ )
		if ( h->child[i] ) clearImage(h->child[i]);

	free(h);
}

void makeImage(char *inp, vector<char> &img, Tree *tree){
	for ( int i = 0 ; inp[i] ; i++ ){
		for ( unsigned pwr = 8 ; pwr ; pwr >>= 1 ){
			if ( val[inp[i]] & pwr ) img.pb('1');
			else img.pb('0');
		}
	}
	for ( int i = 0 ; inp[i] ; i++ ) img.pb(inp[i]);
	
	for ( len = 0 ; img[len] == '0' ; len++ );
	len++;
	tree->root = 0;
	tree->root = S(img, 0);
}

char res[1000000];

int main(){
	char inp1[105], inp2[105];
	stack<int>stck;
	int ks = 1;
	
	for ( int i = 0 ; i < 10 ; i++ ) val[i + '0'] = i;
	for ( int i = 'A' ; i < 'G' ; i++ ) val[i] = 10 + i - 'A';

	while ( cin >> inp1 >> inp2 ){
		if ( strcmp(inp1, "0") == 0 && strcmp(inp2, "0") == 0 ) break;
		
		res[0] = '1';
		res[1] = 0;
		
		makeImage(inp1, img1, &h1);
		makeImage(inp2, img2, &h2);

		merge(h1.root, h2.root, res);
		
		int j = 0;
		int now = 0;
		for ( int i = strlen(res) - 1 ; i >= 0 ; i-- ){
			now = now + ((res[i] - '0')<<j);
			j++;
			if ( j == 4 ){
				stck.push(now);
				j = 0;
				now = 0;
			}
		}
		
		if ( now ) stck.push(now);
		
		if ( ks > 1 ) puts("");
		printf("Image %d:\n", ks++);
		while ( stck.empty() == false ){
			printf("%X", stck.top());
			stck.pop();
		}
		puts("");
		
		img1.clear();
		img2.clear();
		
		clearImage(h1.root);
		clearImage(h2.root);
	}
	
	return 0;
}
/*
7
6
7
7
B75BFA
3EE5F3EB
2BE
2EB
15EBE
174EB
*/
