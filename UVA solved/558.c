#include<stdio.h>
#include<stdlib.h>

#define _EDGE 2005
#define _NODE 1005
#define INF 2147483646

typedef struct
{
    int u, v, cost;
}worm;

worm worms[_EDGE];
long dis[_NODE];

int main()
{
    int test;
    int node, edge;
    int i, j;
    int flag;
    
    scanf("%d", &test);
    for(;test;test--)
    {
        scanf("%d%d", &node, &edge);
        for(i=0;i<edge;i++)
        {
            scanf("%d%d%d", &worms[i].u, &worms[i].v, &worms[i].cost);
        }
        
        for(i=0;i<node;i++) dis[i]=INF;
        dis[worms[0].u]=0;
        
        
        for(i=0;i<node;i++)
        {
            for(j=0;j<edge;j++)
            {
                if(dis[worms[j].v]>dis[worms[j].u]+worms[j].cost)
                dis[worms[j].v]=dis[worms[j].u]+worms[j].cost;
            }
        }
        
        
        flag=1;
        for(i=0;i<edge;i++)
        {
            if(dis[worms[i].v]>dis[worms[i].u]+worms[i].cost)
            {
                flag=0;
                break;
            }
        }
        if(flag) printf("not possible\n");
        else printf("possible\n");
    }
    return 0;
}
