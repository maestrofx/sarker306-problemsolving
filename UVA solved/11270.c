#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long configs[100][1024][1024], res[101][101];
int visited[100][1024][1024];
int Row, Col, Kase = 0;

/* backtrack returns number of configurations possible with current row configuration, where 0 is blank and 1 is cell occupied by a domino.
we can vertically place a domino, so next row configuration is needed,
*/
unsigned long long backtrack(int col, int curRow, unsigned curRowCnf, unsigned nxtRowConf){
	unsigned mask = 1 << ( col - 1 ); /* start from leftmost column for blank cell */
	if ( curRow == Row && curRowCnf == 0 && nxtRowConf == 0 ) return 1;
	if ( curRow == Row ) return 0;
	if ( visited[curRow][curRowCnf][nxtRowConf] == Kase )
		return configs[curRow][curRowCnf][nxtRowConf];
	
	visited[curRow][curRowCnf][nxtRowConf] = Kase;
	/* find the first blank position in current row */
	for ( ; mask ; mask >>= 1 )
		if ( (curRowCnf & mask) == 0 ) break;
	
	if ( mask == 0  )
		configs[curRow][curRowCnf][nxtRowConf] = backtrack( col, curRow + 1, nxtRowConf, 0);  /* the curRow is full, go to next column */
	else{
		if ( (curRow + 1) < Row && (nxtRowConf & mask) == 0 ) configs[curRow][curRowCnf][nxtRowConf] = backtrack(col, curRow, curRowCnf | mask, nxtRowConf | mask); /* nxtRow is blank in this column, add a domino then */
		if ( mask > 1 && ( curRowCnf & (mask >> 1)) == 0 ) configs[curRow][curRowCnf][nxtRowConf] += backtrack(col, curRow,  curRowCnf | mask | ( mask >> 1 ) , nxtRowConf); /* add a domino at this row horizontally */
	}
	
	return configs[curRow][curRowCnf][nxtRowConf];
}

int main(int argc, char **argv){
	unsigned i, j;

	for ( Col = 1 ; Col < 101 ; Col++ )
		for (Row = 1 ; Row*Col < 101 ; Row++ ){
			res[Row][Col] = -1;
			/*Kase++;
			if ( Row % 2 && Col % 2 ) continue;
			res[Row][Col] = backtrack(Col, 0, 0, 0);
			printf("res[%d][%d] = %lluLL;\n", Row, Col, res[Row][Col]);
			memset(configs, 0, sizeof(configs));*/
		}
	
	res[2][2] = 2LL;
res[3][2] = 3LL;
res[4][2] = 5LL;
res[5][2] = 8LL;
res[6][2] = 13LL;
res[7][2] = 21LL;
res[8][2] = 34LL;
res[9][2] = 55LL;
res[10][2] = 89LL;
res[11][2] = 144LL;
res[12][2] = 233LL;
res[13][2] = 377LL;
res[14][2] = 610LL;
res[15][2] = 987LL;
res[16][2] = 1597LL;
res[17][2] = 2584LL;
res[18][2] = 4181LL;
res[19][2] = 6765LL;
res[20][2] = 10946LL;
res[21][2] = 17711LL;
res[22][2] = 28657LL;
res[23][2] = 46368LL;
res[24][2] = 75025LL;
res[25][2] = 121393LL;
res[26][2] = 196418LL;
res[27][2] = 317811LL;
res[28][2] = 514229LL;
res[29][2] = 832040LL;
res[30][2] = 1346269LL;
res[31][2] = 2178309LL;
res[32][2] = 3524578LL;
res[33][2] = 5702887LL;
res[34][2] = 9227465LL;
res[35][2] = 14930352LL;
res[36][2] = 24157817LL;
res[37][2] = 39088169LL;
res[38][2] = 63245986LL;
res[39][2] = 102334155LL;
res[40][2] = 165580141LL;
res[41][2] = 267914296LL;
res[42][2] = 433494437LL;
res[43][2] = 701408733LL;
res[44][2] = 1134903170LL;
res[45][2] = 1836311903LL;
res[46][2] = 2971215073LL;
res[47][2] = 4807526976LL;
res[48][2] = 7778742049LL;
res[49][2] = 12586269025LL;
res[50][2] = 20365011074LL;
res[2][3] = 3LL;
res[4][3] = 11LL;
res[6][3] = 41LL;
res[8][3] = 153LL;
res[10][3] = 571LL;
res[12][3] = 2131LL;
res[14][3] = 7953LL;
res[16][3] = 29681LL;
res[18][3] = 110771LL;
res[20][3] = 413403LL;
res[22][3] = 1542841LL;
res[24][3] = 5757961LL;
res[26][3] = 21489003LL;
res[28][3] = 80198051LL;
res[30][3] = 299303201LL;
res[32][3] = 1117014753LL;
res[2][4] = 5LL;
res[3][4] = 11LL;
res[4][4] = 36LL;
res[5][4] = 95LL;
res[6][4] = 281LL;
res[7][4] = 781LL;
res[8][4] = 2245LL;
res[9][4] = 6336LL;
res[10][4] = 18061LL;
res[11][4] = 51205LL;
res[12][4] = 145601LL;
res[13][4] = 413351LL;
res[14][4] = 1174500LL;
res[15][4] = 3335651LL;
res[16][4] = 9475901LL;
res[17][4] = 26915305LL;
res[18][4] = 76455961LL;
res[19][4] = 217172736LL;
res[20][4] = 616891945LL;
res[21][4] = 1752296281LL;
res[22][4] = 4977472781LL;
res[23][4] = 14138673395LL;
res[24][4] = 40161441636LL;
res[25][4] = 114079985111LL;
res[2][5] = 8LL;
res[4][5] = 95LL;
res[6][5] = 1183LL;
res[8][5] = 14824LL;
res[10][5] = 185921LL;
res[12][5] = 2332097LL;
res[14][5] = 29253160LL;
res[16][5] = 366944287LL;
res[18][5] = 4602858719LL;
res[20][5] = 57737128904LL;
res[2][6] = 13LL;
res[3][6] = 41LL;
res[4][6] = 281LL;
res[5][6] = 1183LL;
res[6][6] = 6728LL;
res[7][6] = 31529LL;
res[8][6] = 167089LL;
res[9][6] = 817991LL;
res[10][6] = 4213133LL;
res[11][6] = 21001799LL;
res[12][6] = 106912793LL;
res[13][6] = 536948224LL;
res[14][6] = 2720246633LL;
res[15][6] = 13704300553LL;
res[16][6] = 69289288909LL;
res[2][7] = 21LL;
res[4][7] = 781LL;
res[6][7] = 31529LL;
res[8][7] = 1292697LL;
res[10][7] = 53175517LL;
res[12][7] = 2188978117LL;
res[14][7] = 90124167441LL;
res[2][8] = 34LL;
res[3][8] = 153LL;
res[4][8] = 2245LL;
res[5][8] = 14824LL;
res[6][8] = 167089LL;
res[7][8] = 1292697LL;
res[8][8] = 12988816LL;
res[9][8] = 108435745LL;
res[10][8] = 1031151241LL;
res[11][8] = 8940739824LL;
res[12][8] = 82741005829LL;
res[2][9] = 55LL;
res[4][9] = 6336LL;
res[6][9] = 817991LL;
res[8][9] = 108435745LL;
res[10][9] = 14479521761LL;
res[2][10] = 89LL;
res[3][10] = 571LL;
res[4][10] = 18061LL;
res[5][10] = 185921LL;
res[6][10] = 4213133LL;
res[7][10] = 53175517LL;
res[8][10] = 1031151241LL;
res[9][10] = 14479521761LL;
res[10][10] = 258584046368LL;

	while ( scanf("%d%d", &Row, &Col) == 2 ){
		Kase++;
		if ( Row < Col ) Row ^= Col ^= Row ^= Col;
		if ( res[Row][Col] != -1 ){
			printf("%llu\n", res[Row][Col]);
			continue;
		}
		
		if ( Row%2 && Col%2 ){
			res[Row][Col] = 0;
			printf("%llu\n", res[Row][Col]);
			continue;
		}
		
		if ( Col == 1 ){
			res[Row][Col] = 1;
			printf("%llu\n", res[Row][Col]);
			continue;
		}
		/*
		res[Row][Col] = backtrack(Col, 0, 0, 0);
		printf("%llu\n", res[Row][Col]);
		memset(configs, 0, sizeof(configs));*/
	}
	
	return 0;
}
