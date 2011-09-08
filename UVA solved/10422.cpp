#include <cstdio>
#include <cstring>
#include <map>
#include <list>
#define MOD 1048583
/*   Backward search limit = 10     time = 0.604 sec  MOD = 1048583
     Backward search limit = 7      time = 0.040 sec  MOD = 32771
     Backward search limit = 5      time = 0.020 sec  MOD = 2053
*/
using namespace std;

long long stringToValue(char *str){
    int i;
    long long x;
    
    /* '1' = 01, '0' = 00, ' ' = 10
        goal corresponds to 375024771924992
    */
    for ( i = x = 0 ; i < 25 ; i++ ){
        x <<= 2;
        x |= ( str[i] == '1' ) ? 1 : ( ( str[i] == '0' ) ? 0 : 2 );
    }
    
    return x;
}

char* valueToString(char *str, long long x){
    int i;
    char charVal[3];
    /* 1765786078701159424 -> 111110111100 110000100000 */
    charVal[0] = '0', charVal[1] = '1', charVal[2] = ' ';
    for ( i = 24 , str[25] = 0 ; i >= 0 ; i--, x >>= 2 ) str[i] = charVal[x & 3];
    
    return str;
}

char* input(char *str){
    int i;
    
    for ( i = 0 ; i < 5 ; i++ ) gets(str + i*5);
    
    return str;
}

void checkEncodeDecode(){
    char str1[26] = "11111011110001 0000100010", str2[] = "111110111100 110000100000", tmp[30];
    long long x = stringToValue(str1);
    printf("%s -> %lld -> %s\n", str1, x, valueToString(tmp, x));
    x = stringToValue(str2);
    printf("%s -> %lld -> %s\n", str2, x, valueToString(tmp, x));
}

map<long long, char>preStates[MOD];
pair< map<long long, char>::iterator, bool > isFound;

struct pos{
    long long x;
    char step;
    
    pos(long long xx, char sstep);
};

pos::pos(long long xx, char sstep){
    x = xx, step = sstep;
}

char xdir[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
char ydir[] = { -1, 1, -2, 2, -2, 2, -1, 1 };

void bfsFromGoal( char *goal, int limit ){
    list<pos>Queue;
    long long x, count = 1;
    char tmpState[30], blank, i, j;
    
    pos startPos( x = stringToValue( goal ), 0 );
    Queue.push_back(startPos);
    preStates[ x % MOD ][ x ] = 0;
    
    while ( Queue.empty() == false ){
        pos u = Queue.front();
        
        valueToString( tmpState, u.x );
        //printf("%s (%16lld / %16lld) - %d\n", tmpState, u.x, stringToValue(tmpState), u.step);
        if ( u.step != (char)limit ){
            for ( i = 0 ; i < 25 ; i++ ) if ( tmpState[i] == ' ' ) break;
            blank = i;
            
            for ( i = 0 ; i < 8 ; i++ ){
                j = 5 * ( (blank/5) + xdir[i] ) + (blank%5) + ydir[i];
                if ( j < 0 ) continue;
                if ( j > 24 ) break;
                tmpState[blank] ^= tmpState[j] ^= tmpState[blank] ^= tmpState[j];
                //if ( strcmp ( "1011001 11101110100100000", tmpState ) == 0 ) puts("got");
                pos v( stringToValue( tmpState ), u.step + 1 );
                tmpState[blank] ^= tmpState[j] ^= tmpState[blank] ^= tmpState[j];
                
                isFound = preStates[ v.x % MOD ].insert( pair < long long, char > ( v.x, v.step ) );
                if ( isFound.second == true ){
                    Queue.push_back( v );
                    count++;
                    //if ( stringToValue("1011001 11101110100100000") == v.x ) puts("got");
                }
            }
        }
        
        Queue.pop_front();
    }
    
    printf("%lld states with limit %d\n", count, limit);
}

int main(){
    int test;
    char inputGrid[26], goalGrid[] = "111110111100 110000100000";
    long long x;
    
    bfsFromGoal(goalGrid, 5);
    //checkEncodeDecode();
    while( scanf("%d", &test) == 1 ){
        getchar();
        while(test-- > 0 ){
            input( inputGrid );
            x = stringToValue( inputGrid );
            //printf("%s %lld\n", inputGrid, x);
            isFound.first = preStates[ x%MOD ].find(x);
            if ( isFound.first != preStates[x%MOD].end() ) printf("Solvable in %d move(s).\n", isFound.first->second );
            else puts("Unsolvable in less than 11 move(s).");
        }
    }
    
    return 0;
}
