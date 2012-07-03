#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char exp[100], *curPos;
}parser;

int isSlump(parser *s){
	if ( s->curPos[0] == 0 ) return 0;
	if (( s->curPos[0] == 'D' | s->curPos[0] == 'E') && s->curPos[1] == 'F'){
		for ( s->curPos += 2 ; s->curPos[0] == 'F' ; s->curPos++ );
		if ( s->curPos[0] == 'G' ){
		/*	printf("Slump -> [DE][F]+[G]\n");*/
			s->curPos++;
			return 1;
		}
		else if (isSlump(s)==1){
		/*	printf("Slump -> [DE][F]+ Slump\n");*/
			return 1;
		}
	}
	
	return 0;
}

int isSlimp(parser *s){
	if ( s->curPos[0] == 'A' ){
		if ( s->curPos[1] == 'H' ){
			s->curPos += 2;
			return 1;
		}
		else if ( s->curPos[1] == 'B' ){
			s->curPos += 2;
			if ( isSlimp(s) && s->curPos[0] == 'C' ){
			/*	printf("Slimp -> \"AB\" Slimp \"C\"\n");*/
				s->curPos++;
				return 1;
			}
		}
		else{
			s->curPos++;
			if ( isSlump(s) && s->curPos[0] == 'C' ){
			/*	printf("Slimp -> \"A\" Slump \"C\"\n");*/
				s->curPos++;
				return 1;
			}
		}
	}
	
	return 0;
}

int isSlurpy(parser *s){
	return isSlimp(s) && isSlump(s) && (s->curPos[0] == 0);
}

int main(){
	parser p;
	int count;
	
	puts("SLURPYS OUTPUT");
	scanf("%d", &count);
	while ( count-- ){
		scanf("%s", p.exp);
		p.curPos = p.exp;
		printf("%s\n", isSlurpy(&p) ? "YES" : "NO");
	}
	puts("END OF OUTPUT");
	
	return 0;
}
