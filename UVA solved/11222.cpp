#include<cstdio>
#include<algorithm>
#include<vector>
/*
template<typename T>
void _union(std::vector<T>::iterator first1, std::vector<T>::iterator last1, 
      std::vector<T>::iterator first2, std::vector<T>::iterator last, std::vector<T>::iterator out){
    while(first1!=last1 && first2!=last2){
        out.push_back(*first);
        if(*first!=*second) out.push_back(*second);
        first++, second++;
    }   
}
*/
int main(){
    int test, i, j;
    int num, x, max;
    
    while(std::scanf("%d", &test)!=EOF){
        for(j=1;j<=test;j++){
            std::vector<int>a[3], diff[3], temp[3];
            int boo[3];
            
            for(i=0;i<3;i++){
                std::scanf("%d", &num);
                while(num--){
                    std::scanf("%d", &x);
                    a[i].push_back(x);
                }
                std::sort(a[i].begin(), a[i].end());
                std::vector<int>v(20005);
                temp[i]=v;
                std::vector<int>v1(10005);
                diff[i]=v1;
                boo[i]=0;
            }
        
            std::set_union(a[0].begin(), a[0].end(), a[1].begin(), a[1].end(), temp[2].begin());
            std::set_difference(a[2].begin(), a[2].end(), temp[2].begin(), temp[2].end(), diff[2].begin());
            
            std::set_union(a[1].begin(), a[1].end(), a[2].begin(), a[2].end(), temp[0].begin());
            std::set_difference(a[0].begin(), a[0].end(), temp[0].begin(), temp[0].end(), diff[0].begin());
            
            std::set_union(a[2].begin(), a[2].end(), a[0].begin(), a[0].end(), temp[1].begin());
            std::set_difference(a[1].begin(), a[1].end(), temp[1].begin(), temp[1].end(), diff[1].begin());
            
            std::printf("Case #%d:\n", j);
            
            max=0;
            for(i=0;i<3;i++){
                std::vector<int>::iterator pv=diff[i].begin();
                while(*pv) pv++;
                if(max<=pv-diff[i].begin()) max=pv-diff[i].begin(), boo[i]=max;
            }
            
            for(i=0;i<3;i++){
                //std::printf( " %ld %ld", temp[i].size(), diff[i].size());
                if(max==boo[i]){
                    std::printf("%d %d", i+1, max);
                    std::vector<int>::iterator pvec;
                    for(pvec=diff[i].begin();pvec!=diff[i].end() && *pvec;pvec++)
                        std::printf(" %d", *pvec);
                    
                    std::printf("\n");
                }
            }
        }
    }
    
    return 0;
}
