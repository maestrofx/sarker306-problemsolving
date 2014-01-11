#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

char valid[] = "abcdefghilmnoprstu_";
char LIM;
char inp[1005];
char vInd[128];
int realFreq[22];
typedef struct Pos{
	int v;
	struct Pos *next, *prev;
}Pos;
Pos list[22];

void removePos(Pos *ptr){
	ptr->next->prev = ptr->prev;
	ptr->prev->next = ptr->next;
}

void readdPos(Pos *ptr){
	ptr->next->prev = ptr->prev->next = ptr;
}

typedef struct Chars{
	char ch;
	char freq;
}Char;
Char chars[22];

void init(){
	int i;
	
	LIM = strlen(valid);
	for ( i = 0 ; valid[i] ; i++ ) vInd[valid[i]] = i;
	memset(list, 0, sizeof(list));
	for ( i = 1 ; i <= LIM ; i++ ){
		list[i].v = LIM - i;
		list[i].next = &list[i+1];
		list[i].prev = &list[i-1];
	}
	
	list[0].next = &list[1];
	list[LIM + 1].prev = &list[LIM];
}

int charCmp(const void *a, const void *b){
	return ((Char*)b)->freq - ((Char*)a)->freq;
}

void preprocess(){
	int i;
	
	for ( i = 0 ; valid[i] ; i++ ) chars[i].ch = valid[i], chars[i].freq = 0, realFreq[i] = 0;
	for ( i = 0 ; inp[i] ; i++ ) chars[vInd[inp[i]]].freq++, realFreq[vInd[inp[i]]]++;
	qsort(chars, LIM, sizeof(Char), charCmp);
	/*for ( i = 0 ; i < LIM ; i++ ) printf("%c - %d\n", chars[i].ch, chars[i].freq);*/
}

char order[22];
char orderFound;

int calcThresholdCost(int ind){
	Pos *ptr;
	int arr[22];
	int c = 0, i = 0, len = 0;

/*  Assuming the remaining characters are assigned order in this manner:
	the more frequent it is, the lower its order is,
	what will be the cost? */
	for ( ptr = list[0].next ; ptr->next != 0 ; ptr = ptr->next, len++);
	for ( ptr = list[0].next ; ptr->next != 0 ; ptr = ptr->next, i++ ) arr[len - i - 1] = ptr->v + 1;
	for ( i = 0 ; ind < LIM ; ind++, i++ ){
		/*printf("%d %d\n", arr[i], chars[ind].freq);*/
		c += arr[i] * chars[ind].freq;
	}
	
	return c;
}

int cost;
int verifyOrder(){
	int i, res = 0;
	
/*	puts("Order verify");*/
	for ( i = 0 ; order[i] ; i++ ){
	/*	printf("%c %d %d\n", order[i], realFreq[vInd[order[i]]], realFreq[vInd[order[i]]] * (i+1));*/
		res += realFreq[vInd[order[i]]] * (i+1);
	}
	return (res == cost);
}

void bkTk(int ind, int remCost){
	Pos *ptr;
	int i, tmp;
	
	if ( remCost < 0 ) return;
	if ( ind == LIM ){
		if ( remCost == 0 && verifyOrder()){
			orderFound = 1;
			puts(order);
		}
		return;
	}

	tmp = calcThresholdCost(ind);
	/*printf("Ind - %d, remCost - %d, tmp - %d ", ind, remCost, tmp);
	for ( i = 0 ; i < LIM ; i++ ) putchar(order[i] == 0 ? '*' : order[i]);
	puts("");*/
	/*getchar();*/
	if ( tmp > remCost ) return;
	
	for ( ptr = list[0].next ; ptr->next != 0 && orderFound == 0; ptr = ptr->next ){
		order[ptr->v] = chars[ind].ch;
		removePos(ptr);
		bkTk(ind + 1, remCost - chars[ind].freq * (ptr->v + 1));
		readdPos(ptr);
		order[ptr->v] = 0;
	}
}

void findOrder(int cost){
	orderFound = 0;
	bkTk(0, cost);
}

int  main(){
	init();
	
	while ( scanf("%s", inp) == 1 && inp[0] != '*' ){
		scanf("%d", &cost);
		preprocess();
		findOrder(cost);
	}
	
	return 0;
}
/*
tsnobfsr_emlllla_dtuangtcrhgpguthngrff
366
aausuufoisuflhdeihdauhnhiatlcusion
353
o_nmhfulhfmihl_febdiaommff_
304
*
*/
