#include<stdio.h>

int residue[]={
0,
2,
2,
2,
5,
2,
4,
3,
11,
2,
3,
8,
16,
4,
21,
6,
5,
2,
11,
20,
34,
8,
15,
10,
7,
13,
11,
13,
45,
18,
23,
8,
3,
2,
25,
75,
42,
13,
5,
23,
13,
50,
16,
18,
89,
38,
8,
39,
30,
29,
38,
7,
45,
23,
137,
46,
63,
17,
48,
5,
46,
34,
140,
33,
39,
2,
28,
29,
79,
33,
48,
3,
10,
46,
120,
6,
37,
17,
8,
44,
15,
160,
20,
35,
144,
104,
179,
153,
24,
8,
265,
19,
9,
62,
7,
139,
19,
44,
93,
182,
27,
158,
185,
193,
17,
82,
3,
11,
43,
55,
21,
41,
146,
29,
80,
59,
8,
29,
66,
19,
160,
59,
28,
129,
127,
120,
72,
45,
157,
2,
63,
127,
81,
318,
513,
98,
28,
32,
231,
236,
411,
26,
45,
5,
303,
228,
66,
9,
205,
65,
39,
};

int main()
{
    int n;
    while(scanf("%d", &n)==1 && n) printf("%d\n", residue[n]+5);
    return 0;
}
