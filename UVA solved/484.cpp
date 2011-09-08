#include<iostream>
#include<cstdio>
#include<map>
#include<list>

using namespace std;
typedef long long llong;

int main(){
	llong x;
	list<llong>listi;
	map<llong, long>mapi;
	map<llong, long>::iterator pmap;
	list<llong>::iterator plist;
	
	while(cin>>x){
		pmap=mapi.find(x);
		if(pmap==mapi.end()){
			mapi.insert(pair< llong, long >(x, 1));
			listi.push_back(x);
		}
		else pmap->second++;
	}
	
	for(plist=listi.begin();plist!=listi.end();plist++){
		cout<<*plist<<' '<<mapi.find(*plist)->second<<endl;
	}
	
	return 0;
}
