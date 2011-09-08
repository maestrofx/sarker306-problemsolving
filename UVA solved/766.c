#include<stdio.h>

char output[23][200] = {"1 1 0",
"2 1 1 0",
"6 2 3 1 0",
"4 1 2 1 0 0",
"30 6 15 10 0 -1 0",
"12 2 6 5 0 -1 0 0",
"42 6 21 21 0 -7 0 1 0",
"24 3 12 14 0 -7 0 2 0 0",
"90 10 45 60 0 -42 0 20 0 -3 0",
"20 2 10 15 0 -14 0 10 0 -3 0 0",
"66 6 33 55 0 -66 0 66 0 -33 0 5 0",
"24 2 12 22 0 -33 0 44 0 -33 0 10 0 0",
"2730 210 1365 2730 0 -5005 0 8580 0 -9009 0 4550 0 -691 0",
"420 30 210 455 0 -1001 0 2145 0 -3003 0 2275 0 -691 0 0",
"90 6 45 105 0 -273 0 715 0 -1287 0 1365 0 -691 0 105 0",
"48 3 24 60 0 -182 0 572 0 -1287 0 1820 0 -1382 0 420 0 0",
"510 30 255 680 0 -2380 0 8840 0 -24310 0 44200 0 -46988 0 23800 0 -3617 0",
"180 10 90 255 0 -1020 0 4420 0 -14586 0 33150 0 -46988 0 35700 0 -10851 0 0",
"3990 210 1995 5985 0 -27132 0 135660 0 -529074 0 1469650 0 -2678316 0 2848860 0 -1443183 0 219335 0",
"840 42 420 1330 0 -6783 0 38760 0 -176358 0 587860 0 -1339158 0 1899240 0 -1443183 0 438670 0 0",
"6930 330 3465 11550 0 -65835 0 426360 0 -2238390 0 8817900 0 -24551230 0 44767800 0 -47625039 0 24126850 0 -3666831 0"};

int main(){
    int k, test;

    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d", &k);
            puts(output[k]);
            if(test) puts("");
        }
    }

    return 0;
}
/*
S[0] : n; S[1] : n*(n+1)/2;
for i : 2 thru 20 do { S[i] : (n+1)**(i+1)-1-n, for j:2 thru i do S[i]: S[i]-binomial(i+1, j)*S[i-j+1] , S[i] : S[i]/(i+1)  , print(rat(S[i]))};
for i:0 thru 20 do { print(ratdenom(S[i])), for j:0 thru i+1 do print(ratcoef(S[i]*ratdenom(S[i]), n, i+1-j)), print("************")};
*/
