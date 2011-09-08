#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<map>
#include<string>
#define MAXPOINT 105
#define MAXROAD 1005
#define INF -99999999

using namespace std;
long matrix[MAXPOINT][MAXPOINT];

long min(long a, long b){
	return (a<b)? a:b;
}

long max(long a, long b){
	return (a>b)? a:b;
}

void initmat(long n){
	long i, j;
	
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++)
			matrix[i][j]=INF;
}

void floyd_warshal_maxmin(long n){
	long i, j, k;
	
	for(k = 0; k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(matrix[i][k]!=INF && matrix[k][j]!=INF){
					matrix[i][j]=max(matrix[i][j], min(matrix[i][k], matrix[k][j]));
				}
			}
		}
	}
}

int main(){
	long test=1, N, M, A, i=1, j, k, x, y;
	string city1, city2;
	map<string, long>mapi;
	map<string, long>::iterator pmap;
	
	while(scanf("%ld%ld", &N, &M)!=EOF){
		if(N==0 && M==0) break;
		initmat(N); 
		for(j=0, i=0; j<M; j++){
			cin>>city1>>city2>>k;
			pmap=mapi.find(city1);
			if(pmap!=mapi.end()) x=pmap->second;
			else mapi.insert(pair<string, long>(city1, i)), x=i++;
			pmap=mapi.find(city2);
			if(pmap!=mapi.end()) y=pmap->second;
			else mapi.insert(pair<string, long>(city2, i)), y=i++;
			matrix[x][y]=matrix[y][x]=k;
		}
		floyd_warshal_maxmin(N);
		cin>>city1>>city2;
		x=(mapi.find(city1))->second, y=(mapi.find(city2))->second;
		printf("Scenario #%ld\n%ld tons\n\n", test++, matrix[x][y]);
		mapi.clear();
	}
	
	return 0;
}
