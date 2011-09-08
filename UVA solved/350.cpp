#include<cstdio>
#include<map>

using namespace std;
typedef long long llong;

int main(){
    llong Z, I, L, M, count, test=1;
    map<llong, char>mapi;
    map<llong, char>::iterator pmap;

    while(scanf("%lld%lld%lld%lld", &Z, &I, &M, &L)!=EOF && Z && I && L && M){
        count=0;
        Z%=M, I%=M;
        L=(Z*(L%M)+I)%M;
        do{
            mapi.insert(pair<llong,char>(L, 'a'));
            count++;
            L=(Z*(L%M)+I)%M;
            pmap=mapi.find(L);
        }while(pmap==mapi.end());
        printf("Case %lld: %lld\n", test++, count);
        mapi.clear();
    }

    return 0;
}
