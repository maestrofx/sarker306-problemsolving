#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Trie{
	long words, prefixes;
	struct Trie* edge[26];
};

void initTrie( Trie *node ){
	for ( int i = 0 ; i < 26 ; i++ ){
		if ( node->edge[i] != 0 ){
			node->edge[i] = 0;
		}
	}
	
	node->words = node->prefixes = 0;
}

void addWord(Trie *node, char *word){
	Trie *ptr;
	
	if ( *word == 0 && node->words == 0 ) node->words++;
	else{
		node->prefixes++;
		if ( (ptr = node->edge[*word-'a']) == 0 ){
			ptr = node->edge[*word-'a'] = (Trie*)malloc(sizeof(Trie));
			initTrie(ptr);
		}

		addWord(ptr, word+1);
	}
}

void clearTrie( Trie *node ){
	for ( int i = 0 ; i < 26 ; i++ ){
		if ( node->edge[i] != 0 ) clearTrie(node->edge[i]);
	}
	
	free(node);
}

void printTrie( Trie *node, char *word, int index ){
	if ( node->words == 1 ){
		word[index] = 0;
		cout<<word<<endl;
	}
	
	for ( int i = 0 ; i < 26 ; i++ ){
		if ( node->edge[i] != 0 ){
			word[index] = i + 'a';
			printTrie(node->edge[i], word, index + 1 );
		}
	}
}

char scrambled[24];
int scrambledLen;
int used[26], foundAny;

void backTrack( Trie *node, char *word, int index ){
	if ( index == scrambledLen && node->words ){
		word[index] = 0;
		foundAny = 1;
		cout<<word<<endl;
		return;
	}
	
	for ( int i = 0 ; i < 26 ; i++ ){
		if ( used[i] && node->edge[i] != 0 ){
			used[i]--;
			word[index] = i + 'a';
			backTrack(node->edge[i], word, index + 1);
			used[i] ++;
		}
	}
}

int findScrambled( Trie *node, char *word ){
	for ( int i = 0 ; i < 26 ; i++ ) used[i] = 0;
	for ( int i = 0 ; scrambled[i] ; i++ ) used[scrambled[i] - 'a']++;
	
	foundAny = 0;
	backTrack(node, word, 0);
	if ( foundAny == 0 ) cout<<"NOT A VALID WORD"<<endl;
	cout<<"******"<<endl;
}

int main(){
	Trie *root = (Trie*)malloc(sizeof(Trie));
	char word[24];
	
	initTrie(root);
	while ( gets(word) && word[0] != 'X' ){
		addWord(root, word);
	}

	while ( gets(scrambled) && scrambled[0] != 'X' ){
		scrambledLen = strlen(scrambled);
		findScrambled(root, word);
	}
	//printTrie(root, word, 0);
	clearTrie(root);
	return 0;
}

