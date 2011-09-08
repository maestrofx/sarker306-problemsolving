#include<cstdio>
#include<map>
#include<string>

using namespace std;

int main(){
    string input, password;
    map<string, long>mapi;
    map<string,long>::iterator pmap;
    int N, i, max;
    char ch;
    
    while(scanf("%d", &N)!=EOF){
        for(i=0, max=1;i<N;){
            ch=getchar();
            if(ch>='a' && ch<='z') input.push_back(ch), i++;
        }
        password=input;
        mapi.insert(pair<string, long>(input, 1));
        while((ch=getchar())!='\n'){
            input.erase(input.begin());
            input.push_back(ch);
            if((pmap=mapi.find(input))!=mapi.end()){
                if(++pmap->second>max) max=pmap->second, password=input;
            }
            else mapi.insert(pair<string, long>(input, 1));
        }
        
        printf("%s\n", password.c_str());
        mapi.clear();
        input.clear();
    }
    
    return 0;
}
