#include<stdio.h>
#define INF 1<<29
int MAXI(int a, int b)
{
    return a>b ? a:b;
}
int MINI(int a, int b)
{
    return a<b ? a:b;
}
int TREE[1022][1022];
int MINTREE[1022][1022];
int array[501][501];
int X1, X2, Y1, Y2;

void initialize(int nodex, int nodey, int leftx, int rightx, int lefty, int righty)
{
    if (leftx == rightx && lefty == righty)
    {
        TREE[nodex][nodey] = array[leftx][lefty];
        return;
    }
    else if (leftx == rightx)
    {
        int midy = (lefty + righty) / 2;
        initialize(nodex, 2*nodey, leftx, rightx, lefty, midy);
        initialize(nodex, 2*nodey+1, leftx, rightx, midy+1, righty);
        TREE[nodex][nodey] = MAXI(TREE[nodex][2*nodey], TREE[nodex][2*nodey+1]);
    }
    else if (lefty == righty)
    {
        int midx = (leftx + rightx) / 2;
        initialize(2*nodex, nodey, leftx, midx, lefty, righty);
        initialize(2*nodex+1, nodey, midx+1, rightx, lefty, righty);
        TREE[nodex][nodey] = MAXI(TREE[2*nodex][nodey], TREE[2*nodex+1][nodey]);
    }
    else
    {
        int midx = (leftx + rightx) / 2;
        int midy = (lefty + righty) / 2;
        initialize(2*nodex, 2*nodey, leftx, midx, lefty, midy);
        initialize(2*nodex+1, 2*nodey, midx+1, rightx, lefty, midy);
        initialize(2*nodex, 2*nodey+1, leftx, midx, midy+1, righty);
        initialize(2*nodex+1, 2*nodey+1, midx+1, rightx, midy+1, righty);
        TREE[nodex][nodey] = MAXI(TREE[2*nodex][2*nodey], MAXI(TREE[2*nodex+1][2*nodey], MAXI(TREE[2*nodex][2*nodey+1], TREE[2*nodex+1][2*nodey+1])));
    }
}

int query(int nodex, int nodey, int leftx, int rightx, int lefty, int righty)
{
    if (rightx<X1 || X2<leftx || righty<Y1 || Y2<lefty) return -1;
    if (X1<=leftx && rightx<=X2 && Y1<=lefty && righty<=Y2) return TREE[nodex][nodey];
    if (leftx == rightx)
    {
        int a1,a2;
        int midy = (lefty+righty)/2;
        a1 = query(nodex, 2*nodey, leftx, rightx, lefty, midy);
        a2 = query(nodex, 2*nodey+1, leftx, rightx, midy+1, righty);
        return MAXI(a1, a2);
    }
    else if (lefty == righty)
    {
        int a1,a2;
        int midx = (leftx+rightx)/2;
        a1 = query(2*nodex, nodey, leftx, midx, lefty, righty);
        a2 = query(2*nodex+1, nodey, midx+1, rightx, lefty, righty);
        return MAXI(a1, a2);
    }
    else
    {
        int a1,a2,a3,a4;
        int midx = (leftx+rightx)/2, midy = (lefty+righty)/2;
        a1 = query(2*nodex, 2*nodey, leftx, midx, lefty, midy);
        a2 = query(2*nodex, 2*nodey+1, leftx, midx, midy+1, righty);
        a3 = query(2*nodex+1, 2*nodey, midx+1, rightx, lefty, midy);
        a4 = query(2*nodex+1, 2*nodey+1, midx+1, rightx, midy+1, righty);
        return MAXI(a1, MAXI(a2, MAXI(a3,a4)));
    }
}

int update(int nodex, int nodey, int leftx, int rightx, int lefty, int righty, int val)
{
    if (rightx<X1 || X2<leftx || righty<Y1 || Y2<lefty) return TREE[nodex][nodey];
    if (X1<=leftx && rightx<=X2 && Y1<=lefty && righty<=Y2){
        TREE[nodex][nodey] = val;
        /*printf("Tree[%d][%d] = %d, %d\n", nodex, nodey, TREE[nodex][nodey], val);*/
        return TREE[nodex][nodey];
    }
    
    if (leftx == rightx)
    {
        int a1,a2;
        int midy = (lefty+righty)/2;
        a1 = update(nodex, 2*nodey, leftx, rightx, lefty, midy, val);
        a2 = update(nodex, 2*nodey+1, leftx, rightx, midy+1, righty, val);
        return TREE[nodex][nodey] = MAXI(a1, a2);
    }
    else if (lefty == righty)
    {
        int a1,a2;
        int midx = (leftx+rightx)/2;
        a1 = update(2*nodex, nodey, leftx, midx, lefty, righty, val);
        a2 = update(2*nodex+1, nodey, midx+1, rightx, lefty, righty, val);
        return TREE[nodex][nodey] = MAXI(a1, a2);
    }
    else
    {
        int a1,a2,a3,a4;
        int midx = (leftx+rightx)/2, midy = (lefty+righty)/2;
        a1 = update(2*nodex, 2*nodey, leftx, midx, lefty, midy, val);
        a2 = update(2*nodex, 2*nodey+1, leftx, midx, midy+1, righty,val);
        a3 = update(2*nodex+1, 2*nodey, midx+1, rightx, lefty, midy, val);
        a4 = update(2*nodex+1, 2*nodey+1, midx+1, rightx, midy+1, righty, val);
        return TREE[nodex][nodey] = MAXI(a1, MAXI(a2, MAXI(a3,a4)));
    }
}

void initialize1(int nodex, int nodey, int leftx, int rightx, int lefty, int righty)
{
    if (leftx == rightx && lefty == righty)
    {
        MINTREE[nodex][nodey] = array[leftx][lefty];
        return;
    }
    else if (leftx == rightx)
    {
        int midy = (lefty + righty) / 2;
        initialize1(nodex, 2*nodey, leftx, rightx, lefty, midy);
        initialize1(nodex, 2*nodey+1, leftx, rightx, midy+1, righty);
        MINTREE[nodex][nodey] = MINI(MINTREE[nodex][2*nodey], MINTREE[nodex][2*nodey+1]);
    }
    else if (lefty == righty)
    {
        int midx = (leftx + rightx) / 2;
        initialize1(2*nodex, nodey, leftx, midx, lefty, righty);
        initialize1(2*nodex+1, nodey, midx+1, rightx, lefty, righty);
        MINTREE[nodex][nodey] = MINI(MINTREE[2*nodex][nodey], MINTREE[2*nodex+1][nodey]);
    }
    else
    {
        int midx = (leftx + rightx) / 2;
        int midy = (lefty + righty) / 2;
        initialize1(2*nodex, 2*nodey, leftx, midx, lefty, midy);
        initialize1(2*nodex+1, 2*nodey, midx+1, rightx, lefty, midy);
        initialize1(2*nodex, 2*nodey+1, leftx, midx, midy+1, righty);
        initialize1(2*nodex+1, 2*nodey+1, midx+1, rightx, midy+1, righty);
        MINTREE[nodex][nodey] = MINI(MINTREE[2*nodex][2*nodey], MINI(MINTREE[2*nodex+1][2*nodey], MINI(MINTREE[2*nodex][2*nodey+1], MINTREE[2*nodex+1][2*nodey+1])));
    }
}

int query1(int nodex, int nodey, int leftx, int rightx, int lefty, int righty)
{
    if (rightx<X1 || X2<leftx || righty<Y1 || Y2<lefty) return INF;
    if (X1<=leftx && rightx<=X2 && Y1<=lefty && righty<=Y2) return MINTREE[nodex][nodey];
    if (leftx == rightx)
    {
        int a1,a2;
        int midy = (lefty+righty)/2;
        a1 = query1(nodex, 2*nodey, leftx, rightx, lefty, midy);
        a2 = query1(nodex, 2*nodey+1, leftx, rightx, midy+1, righty);
        return MINI(a1, a2);
    }
    else if (lefty == righty)
    {
        int a1,a2;
        int midx = (leftx+rightx)/2;
        a1 = query1(2*nodex, nodey, leftx, midx, lefty, righty);
        a2 = query1(2*nodex+1, nodey, midx+1, rightx, lefty, righty);
        return MINI(a1, a2);
    }
    else
    {
        int a1,a2,a3,a4;
        int midx = (leftx+rightx)/2, midy = (lefty+righty)/2;
        a1 = query1(2*nodex, 2*nodey, leftx, midx, lefty, midy);
        a2 = query1(2*nodex, 2*nodey+1, leftx, midx, midy+1, righty);
        a3 = query1(2*nodex+1, 2*nodey, midx+1, rightx, lefty, midy);
        a4 = query1(2*nodex+1, 2*nodey+1, midx+1, rightx, midy+1, righty);
        return MINI(a1, MINI(a2, MINI(a3,a4)));
    }
}

int update1(int nodex, int nodey, int leftx, int rightx, int lefty, int righty, int val)
{
    if (rightx<X1 || X2<leftx || righty<Y1 || Y2<lefty) return MINTREE[nodex][nodey];
    if (X1<=leftx && rightx<=X2 && Y1<=lefty && righty<=Y2){
        MINTREE[nodex][nodey] = val;
        return MINTREE[nodex][nodey];
    }
    
    if (leftx == rightx)
    {
        int a1,a2;
        int midy = (lefty+righty)/2;
        a1 = update1(nodex, 2*nodey, leftx, rightx, lefty, midy, val);
        a2 = update1(nodex, 2*nodey+1, leftx, rightx, midy+1, righty, val);
        return MINTREE[nodex][nodey] = MINI(a1, a2);
    }
    else if (lefty == righty)
    {
        int a1,a2;
        int midx = (leftx+rightx)/2;
        a1 = update1(2*nodex, nodey, leftx, midx, lefty, righty, val);
        a2 = update1(2*nodex+1, nodey, midx+1, rightx, lefty, righty, val);
        return MINTREE[nodex][nodey] = MINI(a1, a2);
    }
    else
    {
        int a1,a2,a3,a4;
        int midx = (leftx+rightx)/2, midy = (lefty+righty)/2;
        a1 = update1(2*nodex, 2*nodey, leftx, midx, lefty, midy, val);
        a2 = update1(2*nodex, 2*nodey+1, leftx, midx, midy+1, righty,val);
        a3 = update1(2*nodex+1, 2*nodey, midx+1, rightx, lefty, midy, val);
        a4 = update1(2*nodex+1, 2*nodey+1, midx+1, rightx, midy+1, righty, val);
        return MINTREE[nodex][nodey] = MINI(a1, MINI(a2, MINI(a3,a4)));
    }
}

int main()
{
    int t,T;
    int N, M, Q;
    int i,j,s,ans, val;
    char command[3];
    
    while ( scanf("%d%d", &N, &M) == 2 ){
        for (i=1; i<=N; ++i)
        {
            for (j=1; j<=M; ++j) scanf("%d", &array[i][j]);
        }
        initialize(1, 1, 1, N, 1, M);
        initialize1(1, 1, 1, N, 1, M);
        scanf("%d", &Q);
        while(Q--)
        {
            scanf("%s", command);
            if ( command[0] == 'q' ){
                scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
                ans = query(1, 1, 1, N, 1, M);
                printf("%d ", ans);
                ans = query1(1, 1, 1, N, 1, M);
                printf("%d\n", ans);
            }
            else{
                scanf("%d%d%d", &X1, &Y1, &val);
                X2 = X1, Y2 = Y1;
                update(1,1,1,N,1,M, val);
                update1(1,1,1,N,1,M, val);
            }
        }
    }
    
    return 0;
}
