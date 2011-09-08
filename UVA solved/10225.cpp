#include <cstdio>
#include <map>
#include <cmath>
#include <list>
#include <locale>
#define LIMIT 4611686018427387904LL
using namespace std;
typedef unsigned long long ll;

ll mul_mod(ll x, ll y, ll mod){
    ll tmp;

    x %= mod, y %= mod;
    if (y == 0 ) return 0;
    tmp = ( LIMIT / y );
    if ( x > tmp ){
        for ( tmp = 0 ; y ; y >>= 1, x = ( x << 1 ) % mod )
            if ( y & 1 != 0 ) tmp = ( tmp + x ) % mod;
        return tmp;
    }
    else return (x*y)%mod;
}

ll fastmod(ll b, ll p, ll mod){
	ll tmp;
	
	if(p == 0) return 1;
	tmp = fastmod(b, p>>1, mod);
	tmp = (tmp * tmp )% mod;
	if ( p & 1 ) tmp = ( tmp * b ) % mod;
	return tmp;
}

/*
    b^x = p mod m -> h = ceiling of sqrt(m), x = h*i - j
    -> b^hi = pb^j mod m -> RHS = pb^j for j = 0,1...h-1
    LHS = b^hi for i = 0,1,...,h-1
*/
ll discrete_log(ll b, ll p, ll mod){
    map<ll, list<ll> >rhs;
    map<ll, list<ll> >::iterator rhsPtr;
    list<ll>::iterator listPtr;
    ll i, h, y, x = mod, xx;
    
    h = sqrt(mod);
    if( h*h != mod ) h++;
    
    for ( i = 0 ; i < h ; i++ , p = ( p * b ) % mod ){
        rhsPtr = rhs.find( p );
        if ( rhsPtr == rhs.end() ){
            list<ll> newList;
            newList.push_back(i);
            rhs.insert( pair<ll, list<ll> > ( p, newList ) );
        }
        else (rhsPtr->second).push_back(i);
    }
    
    b = fastmod( b, h, mod);
    for ( i = 0, y = 1 ; i < h ; i++, y = ( y * b )%mod ){
        rhsPtr = rhs.find( y );
        if ( rhsPtr != rhs.end() ){
            for ( listPtr = (rhsPtr->second).begin() ; listPtr !=(rhsPtr->second).end() ; listPtr++ ){
                xx = h*i - *listPtr;
                if ( xx >= 0 && x > xx ) x = xx;
            }
        }
    }
    
    rhs.clear();
    return x;
}

int main(){
    ll b, p, n, x;
    
    /*setlocale(LC_CTYPE, "");
    printf("%s\n", "Sch�ne Gr��e");*/
    while( scanf("%lld%lld%lld", &p, &b, &n) == 3 ){
        x = discrete_log(b, n, p);
        if( x == p ) puts("no solution");
        else printf("%lld\n", x);
    }
    
    return 0;
}
