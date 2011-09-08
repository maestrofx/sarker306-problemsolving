#include<cstdio>
#include<map>

using namespace std;
long array[105];

int main(){
    int n, i, j, flag, test=0;
    long tmp;
	map<long, int>mapi;
	map<long, int>::iterator pmap;
    
    while(scanf("%d", &n)!=EOF){
        mapi.clear();
        for(i=0;i<n;i++) scanf("%ld", &array[i]);
        flag=1;
        if(array[0]<1) flag=0;
        for(i=1, tmp=array[0];i<n && flag;i++){
            if(tmp>=array[i]) flag=0;
            tmp=array[i];
        }
        for(i=0;i+1<n  && flag;i++)
            for(j=i;j<n;j++){
                pmap=mapi.find(array[i]+array[j]);
                if(pmap==mapi.end()) mapi.insert(pair<long, int>(array[i]+array[j], 1));
                else{
                    flag=0;
                    break;
                }
            }
        
        printf("Case #%d: It is %sa B2-Sequence.\n\n", ++test, (flag)?"":"not ");
    }
    
    return 0;
}
