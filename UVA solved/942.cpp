#include <stdio.h>
#include <string.h>
#include <set>
#include <string>

using namespace std;

int main(){
    long long a, b, c, aa, bb,cc;
    int test;
    char x, xx, tmp[40];
    
    while( scanf("%d", &test) != EOF){
        while(test--){
            scanf("%lld%lld", &a, &b);
            printf("%lld", a/b);
            a -= (a/b)*b;
            aa = a, bb = b;
            set<string>sstr;
            putchar('.');
            xx = cc = 1<<62;
            do{
                a = a * 10;
                c = a % b;
                x = a/b;
                sprintf(tmp, "%lld.%lld", x, c);
                if ( x == 0 && c == 0 ) break;
                string str(tmp);
                if( sstr.find(str) != sstr.end() ){
                    cc = c, xx = x;
                    break;
                }
                else sstr.insert(str);
                a = c;
            }while( x || c );
            
            a = aa, b = bb;
            aa = 0, bb = 0;
            do{
                a = a * 10;
                c = a % b;
                x = a/b;
                if( x == xx && c == cc ){
                    aa++;
                    if ( aa == 2 ) break;
                    if( xx || cc ) putchar('(');
                }
                
                if ( x==0 && c==0 && bb ) break;
                printf("%d", x);
                a = c;
                bb++;
            }while( 1 );
            if( xx || cc ) puts(")");
            else puts("");
            
            sstr.clear();
        }
    }
    
    return 0;
}
