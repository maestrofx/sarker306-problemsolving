#include<cstdio>
#include<iostream>
#include<map>
#include<string>
#include<queue>

using namespace std;
map<string,long>mapi;

int bfs(){
    queue<string>q;
    string str;
    string::iterator p;
    long count=0, i;

    for(i=0;i<26;i++){
        str.append(1, i+'a');
        q.push(str);
        mapi.insert(pair<string, long>(str, ++count));
        //cout<<str<<endl;
        str.erase(str.end()-1);
    }

    while(!q.empty()){
        str=q.front();
        q.pop();
        if(str.size()>=5) break;
        for(p=str.begin();p!=str.end();p++);
        for(i=*--p-'a'+1;i<26;i++){
            str.append(1, i+'a');
            q.push(str);
            mapi.insert(pair<string, long>(str, ++count));
            str.erase(str.end()-1);
        }
    }

    while(!q.empty()) q.pop();
}

int main(){
    string word;
    string::iterator p;
    map<string, long>::iterator ptr;

    bfs();

    while(cin>>word){
        for(p=word.begin()+1;p!=word.end();p++){
            if(*p<=*(p-1)) break;
        }

        if(p!=word.end()) cout<<0<<endl;
        else{
            ptr=mapi.find(word);
            if(ptr!=mapi.end()) cout<<ptr->second<<endl;
            else cout<<":("<<endl;
        }
    }

    mapi.clear();
    return 0;
}
