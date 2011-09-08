#include <cstdio>
#include <cstring>
#include <map>
#include <list>
#define MOD 2053
/*   Backward search limit = 10     time = 0.604 sec  MOD = 1048583
     Backward search limit = 7      time = 0.040 sec  MOD = 32771
     Backward search limit = 6      time = 0.020 sec  MOD = 8209
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
    long long x;
    char tmpState[30], blank, i, j;
    
    pos startPos( x = stringToValue( goal ), 0 );
    Queue.push_back(startPos);
    preStates[ x % MOD ][ x ] = 0;
    
    while ( Queue.empty() == false ){
        pos u = Queue.front();
        
        valueToString( tmpState, u.x );
        
        if ( u.step != (char)limit ){
            for ( i = 0 ; i < 25 ; i++ ) if ( tmpState[i] == ' ' ) break;
            blank = i;
            
            for ( i = 0 ; i < 8 ; i++ ){
                j = 5 * ( (blank/5) + xdir[i] ) + (blank%5) + ydir[i];
                if ( j < 0 || j > 25 ) continue;
                tmpState[blank] ^= tmpState[j] ^= tmpState[blank] ^= tmpState[j];
                pos v( stringToValue( tmpState ), u.step + 1 );
                tmpState[blank] ^= tmpState[j] ^= tmpState[blank] ^= tmpState[j];
                
                isFound = preStates[ v.x % MOD ].insert( pair < long long, char > ( v.x, v.step ) );
                if ( isFound.second == true )  Queue.push_back( v );
            }
        }
        
        Queue.pop_front();
    }
}

int bfsFromStart( char *start, int limit ){
    list<pos>Queue;
    map<long long, char>curStates[MOD];
    long long x;
    char tmpState[30], blank, i, j;
    int result = -1;
    
    pos startPos( x = stringToValue( start ), 0 );
    Queue.push_back(startPos);
    curStates[ x % MOD ][ x ] = 0;
    
    while ( Queue.empty() == false ){
        pos u = Queue.front();
        isFound.first = preStates[ u.x%MOD ].find(u.x);
        if ( isFound.first != preStates[u.x%MOD].end() ){
            result = u.step + isFound.first->second;
            break;
        }
        
        valueToString( tmpState, u.x );
        
        if ( u.step != (char)limit ){
            for ( i = 0 ; i < 25 ; i++ ) if ( tmpState[i] == ' ' ) break;
            blank = i;
            
            for ( i = 0 ; i < 8 ; i++ ){
                j = 5 * ( (blank/5) + xdir[i] ) + (blank%5) + ydir[i];
                if ( j < 0 || j > 25 ) continue;
                tmpState[blank] ^= tmpState[j] ^= tmpState[blank] ^= tmpState[j];
                pos v( stringToValue( tmpState ), u.step + 1 );
                tmpState[blank] ^= tmpState[j] ^= tmpState[blank] ^= tmpState[j];
                
                isFound = curStates[ v.x % MOD ].insert( pair < long long, char > ( v.x, v.step ) );
                if ( isFound.second == true ) Queue.push_back( v );
            }
        }
        
        Queue.pop_front();
    }
    
    return result;
}

int main(){
    int test, result;
    char inputGrid[26], goalGrid[] = "111110111100 110000100000";
    long long x;
    
    bfsFromGoal(goalGrid, 5);
    
    while( scanf("%d", &test) == 1 ){
        getchar();
        while(test-- > 0 ){
            input( inputGrid );
            result = bfsFromStart( inputGrid, 5 );
            if ( result == -1 ) puts("Unsolvable in less than 11 move(s).");
            else printf("Solvable in %d move(s).\n", result);
        }
    }
    
    return 0;
}
