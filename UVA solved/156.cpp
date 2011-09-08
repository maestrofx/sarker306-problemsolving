#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cctype>
#include<vector>
#include<map>
#include<algorithm>
#include<string>

using namespace std;

int main(){
    map<string, vector<string> >map1;
    map<string, vector<string> >::iterator pmap1;
    vector<string>anagram;
    vector<string>::iterator pvec;
    string word, sorted;
    char input[50], flag=0;
    int i;
    
    for( ; ; ){
        while(scanf("%s", input)!=EOF){
            flag=1;
            if(input[0]=='#') break;
			word.assign(input);
            for (i = 0 ; input[i] ; i++) input[i] = tolower(input[i]);
            sort(input, input+i);
            sorted.assign(input);
            
            if((pmap1=map1.find(sorted))!=map1.end()){
                (pmap1->second).push_back(word);
            }
            else{
                anagram.push_back(word);
                map1.insert(pair<string, vector<string> > (sorted, anagram));
                anagram.clear();
            }
        }
        
        if(!flag) break;
        
		for(pmap1=map1.begin();pmap1!=map1.end();pmap1++){
            if((pmap1->second).size()==1) anagram.push_back( (pmap1->second)[0]);;
        }
        
        sort(anagram.begin(), anagram.end());
        for(pvec=anagram.begin() ; pvec!=anagram.end(); pvec++) cout<<*pvec<<endl;
        anagram.clear();
		map1.clear();
		flag=0;
    }
    
    return 0;
}
