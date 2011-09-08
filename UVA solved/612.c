#include<stdio.h>

#define SIZE 55
#define MINDNA 105

char dna[MINDNA][SIZE];
int dna_inv[MINDNA];

int main()
{
    int dna_size, dna_num, counter, min_count, min;
    int i, j, k, m;
    scanf("%d", &m);
    for(;m;m--)
    {
        for(i=0;i<MINDNA;i++) dna_inv[i]=-1;
        scanf("%d%d", &dna_size, &dna_num);
        for(k=0;k<dna_num;k++)
        {
            scanf("%s", dna[k]);
            counter=0;
            for(i=0;i+1<dna_size;i++)
            for(j=i+1;j<dna_size;j++)
            if(dna[k][i]>dna[k][j]) counter++;
            dna_inv[k]=counter;
        }
        do
        {
            for(counter=0, min_count=32000, min=0, i=0;i<dna_num;i++)
            {
                if(min_count>dna_inv[i] && dna_inv[i]>-1)
                {
                    counter=1;
                    min_count=dna_inv[i];
                    min=i;
                }
            }
            if(counter!=0)
            {
                puts(dna[min]);
                dna_inv[min]=-1;
            }
        }while(counter);
        if(m!=1) printf("\n");
    }
    return 0;
}
