#include<stdio.h>
#include<string.h>
#define SIZE 262141
#define RANGE 100000
#define INF 9223372036854775807LL
struct node
{
    long long S, S2;
    long long Max, Min;
    bool Fa, Fc;
    long long A, C;
};
node TREE[SIZE+3];
long long array[RANGE+3] = {0};
void initialize(int node, int left, int right)
{
    TREE[node].A = TREE[node].C = 0;
    TREE[node].Fa = TREE[node].Fc = false;
    if (left==right)
    {
        TREE[node].Max = TREE[node].Min = array[left];
        TREE[node].S = array[left];
        TREE[node].S2 = array[left] * array[right];
        return;
    }
    int mid = (left+right)>>1;
    initialize(node<<1, left, mid);
    initialize((node<<1)+1, mid+1, right);
    TREE[node].S = TREE[node<<1].S + TREE[(node<<1)+1].S;
    TREE[node].S2 = TREE[node<<1].S2 + TREE[(node<<1)+1].S2;
    TREE[node].Max = TREE[node<<1].Max > TREE[(node<<1)+1].Max ? TREE[node<<1].Max : TREE[(node<<1)+1].Max;
    TREE[node].Min = TREE[node<<1].Min < TREE[(node<<1)+1].Min ? TREE[node<<1].Min : TREE[(node<<1)+1].Min;
}
void updateChild(int node, int left, int right, int mid)
{
    long long l = (mid-left+1), r = (right-mid);
    if (TREE[node].Fc)
    {
        TREE[node<<1].S = l * TREE[node].C;
        TREE[node<<1].S2 = l * TREE[node].C * TREE[node].C;
        TREE[(node<<1)+1].S = r * TREE[node].C;
        TREE[(node<<1)+1].S2 = r * TREE[node].C * TREE[node].C;

        TREE[node<<1].Fa = TREE[(node<<1)+1].Fa = false;
        TREE[node<<1].Fc = TREE[(node<<1)+1].Fc = true;

        TREE[node<<1].A = TREE[(node<<1)+1].A = 0;
        TREE[node<<1].C = TREE[(node<<1)+1].C = TREE[node].C;

        TREE[node<<1].Max = TREE[node<<1].Min = TREE[node].C;
        TREE[(node<<1)+1].Max = TREE[(node<<1)+1].Min = TREE[node].C;

        TREE[node].C = 0;
        TREE[node].Fc = false;
    }
    if (TREE[node].Fa)
    {
        TREE[node<<1].S2 += 2 * TREE[node].A * TREE[node<<1].S + l * TREE[node].A * TREE[node].A;
        TREE[(node<<1)+1].S2 += 2 * TREE[node].A * TREE[(node<<1)+1].S + r * TREE[node].A * TREE[node].A;

        TREE[node<<1].S += l * TREE[node].A;
        TREE[(node<<1)+1].S += r * TREE[node].A;

        TREE[node<<1].Max += TREE[node].A;
        TREE[(node<<1)+1].Max += TREE[node].A;
        TREE[node<<1].Min += TREE[node].A;
        TREE[(node<<1)+1].Min += TREE[node].A;

        TREE[node<<1].A += TREE[node].A;
        TREE[(node<<1)+1].A += TREE[node].A;
        TREE[node<<1].Fa = TREE[(node<<1)+1].Fa = true;

        TREE[node].A = 0;
        TREE[node].Fa = false;
    }
}
int start, end;
long long val;
void updateC(int node, int left, int right)
{
    if (right<start || end<left) return;
    if (start<=left && right<=end)
    {
        long long n = right-left+1;
        TREE[node].Max = TREE[node].Min = val;
        TREE[node].S =  n * val;
        TREE[node].S2 = n * val * val;
        if (left<right)
        {
            TREE[node].A = 0;
            TREE[node].C = val;
            TREE[node].Fa = false;
            TREE[node].Fc = true;
        }
        return;
    }
    int mid = (left+right)>>1;
    if (TREE[node].Fc || TREE[node].Fa) updateChild(node, left, right, mid);
    updateC(node<<1, left, mid);
    updateC((node<<1)+1, mid+1, right);
    TREE[node].S = TREE[node<<1].S + TREE[(node<<1)+1].S;
    TREE[node].S2 = TREE[node<<1].S2 + TREE[(node<<1)+1].S2;
    TREE[node].Max = TREE[node<<1].Max > TREE[(node<<1)+1].Max ? TREE[node<<1].Max : TREE[(node<<1)+1].Max;
    TREE[node].Min = TREE[node<<1].Min < TREE[(node<<1)+1].Min ? TREE[node<<1].Min : TREE[(node<<1)+1].Min;
}
void updateA(int node, int left, int right)
{
    if (right<start || end<left) return;
    if (start<=left && right<=end)
    {
        long long n = right-left+1;
        TREE[node].Max += val;
        TREE[node].Min += val;
        TREE[node].S2 += 2 * TREE[node].S * val + n * val * val;
        TREE[node].S += n * val;
        if (left<right)
        {
            TREE[node].A += val;
            TREE[node].Fa = true;
        }
        return;
    }
    int mid = (left+right)>>1;
    if (TREE[node].Fc || TREE[node].Fa) updateChild(node, left, right, mid);
    updateA(node<<1, left, mid);
    updateA((node<<1)+1, mid+1, right);
    TREE[node].S = TREE[node<<1].S + TREE[(node<<1)+1].S;
    TREE[node].S2 = TREE[node<<1].S2 + TREE[(node<<1)+1].S2;
    TREE[node].Max = TREE[node<<1].Max > TREE[(node<<1)+1].Max ? TREE[node<<1].Max : TREE[(node<<1)+1].Max;
    TREE[node].Min = TREE[node<<1].Min < TREE[(node<<1)+1].Min ? TREE[node<<1].Min : TREE[(node<<1)+1].Min;
}
struct Ret
{
    long long S, S2, Max, Min;
    Ret() {}
    Ret (long long s, long long s2, long long max, long long min) {S=s, S2=s2, Max=max, Min=min;}
};
Ret query(int node, int left, int right)
{
    if (start<=left && right<=end) return Ret(TREE[node].S, TREE[node].S2, TREE[node].Max, TREE[node].Min);
    if (right<start || end<left) return Ret(0, 0, -INF, INF);
    int mid = (left+right)>>1;
    if (TREE[node].Fc || TREE[node].Fa) updateChild(node, left, right, mid);
    Ret a = query(node<<1, left, mid), b = query((node<<1)+1, mid+1, right);
    return Ret (a.S+b.S, a.S2+b.S2, a.Max>b.Max?a.Max:b.Max, a.Min<b.Min?a.Min:b.Min);
}
long long GCD(long long a, long long b)
{
    if (b==0) return a;
    return GCD(b, a%b);
}
int main()
{
    int t,T;
    int N,Q;
    int i,op;
    Ret ret;
    long long S, S2, Max, Min, num, den, n, g, R;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d %d", &N, &Q);
        for (i=1; i<=N; ++i) scanf("%lld", &array[i]);
        initialize(1, 1, N);
        printf("Case %d:\n", t);
        while(Q--)
        {
            scanf("%d %d %d", &op, &start, &end);
            if (op<2) scanf("%lld", &val);
            if (op==0) updateC(1, 1, N);
            else if (op==1) updateA(1, 1, N);
            else
            {
                ret = query(1, 1, N);
                n = end - start + 1;
                num = n * ret.S2 - ret.S * ret.S;
                den = n * n;
                g = GCD(num, den);
                num /= g, den /= g;
                R = ret.Max - ret.Min;
                printf("%lld/%lld %lld\n", num, den, R);
            }
        }
    }
    return 0;
}
