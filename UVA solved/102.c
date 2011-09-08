#include<stdio.h>

int main()
{
    unsigned long b[3], g[3], c[3];
    unsigned long sum, bcg, bgc, cbg, cgb, gbc, gcb, min;
    while(scanf("%lu%lu%lu%lu%lu%lu%lu%lu%lu", &b[1], &g[1], &c[1], &b[2], &g[2], &c[2], &b[3], &g[3], &c[3])==9)
    {
        sum= b[1]+g[1]+c[1]+b[2]+g[2]+c[2]+b[3]+g[3]+c[3];
        bcg= sum-b[1]-c[2]-g[3];
        bgc= sum-b[1]-c[3]-g[2];
        cbg= sum-b[2]-c[1]-g[3];
        cgb= sum-b[3]-c[1]-g[2];
        gbc= sum-b[2]-c[3]-g[1];
        gcb= sum-b[3]-c[2]-g[1];
        min=(bcg<=bgc)? bcg: bgc;
        min=(min<=cbg)? min: cbg;
        min=(min<=cgb)? min: cgb;
        min=(min<=gbc)? min: gbc;
        min=(min<=gcb)? min: gcb;
        if (min==bcg) printf("BCG");
        else if (min==bgc) printf("BGC");
        else if (min==cbg) printf("CBG");
        else if (min==cgb) printf("CGB");
        else if (min==gbc) printf("GBC");
        else if (min==gcb) printf("GCB");
        printf(" %lu\n", min);
    }
    return 0;
}
