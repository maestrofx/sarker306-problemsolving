/*
  Name: 10300
  Copyright: 
  Author: 
  Date: 31/08/09 04:55
  Description: Ecological Premium
*/
#include<iostream>
using namespace std;
int main()
{
    int test, testcount=0;
    int farmers, farmercount;
    unsigned long area_size, animals, env_frnd;
    unsigned long long temp;
    int i;
    cin>>test;
    for(testcount=0;testcount<test;testcount++)
    {
        temp=0;
        cin>>farmers;
        for(farmercount=0;farmercount<farmers; farmercount++)
        {
            cin>>area_size>>animals>>env_frnd;
            temp+=area_size*env_frnd;
        }
        cout<<temp<<endl;
    }
    return 0;
}
