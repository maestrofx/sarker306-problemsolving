#include <stdio.h>
#include <string.h>
#include <set>
#include <string>

using namespace std;

int main(){
    long long a, b, c, aa, bb, cc, len;
    int test;
    char x, xx, tmp[40];
    
    while( scanf("%lld%lld", &a, &b) != EOF){
        printf("%lld/%lld = ", a, b);
        printf("%lld", a/b);
        a -= (a/b)*b;
        aa = a, bb = b;
        set<string>sstr;
        putchar('.');
        xx = cc = 1<<62;
        len = 0;
        do{
            a = a * 10;
            c = a % b;
            x = a/b;
            sprintf(tmp, "%lld.%lld", x, c);
            string str(tmp);
            if( sstr.find(str) != sstr.end() ){
                cc = c, xx = x;
                break;
            }
            else sstr.insert(str);
            a = c;
            len++;
        }while( x || c );
        
        a = aa, b = bb;
        aa = 0, bb = 0;
        do{
            if( bb == 50 ){
                printf("...");
                break;
            }
            a = a * 10;
            c = a % b;
            x = a/b;
            if( x == xx && c == cc ){
                aa++;
                if ( aa == 2 ) break;
                putchar('(');
            }
            
            printf("%d", x);
            a = c;
            if( aa ) bb++;
            if ( aa == 0 ) len--;
        }while( 1 );
        puts(")");
        printf("   %lld = number of digits in repeating cycle\n\n", len);
        sstr.clear();
    }
    
    return 0;
}
