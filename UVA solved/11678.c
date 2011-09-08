#include<stdio.h>
#include<stdbool.h>

#define SIZE 100001

bool alice[SIZE], betty[SIZE];

int main()
{
    int card_a, card_b;
    long card_number1, card_number2;
    long exchange_a, exchange_b, min;
    long i;
    while(scanf("%d%d", &card_a, &card_b)==2 && card_a||card_b)
    {
        exchange_a=exchange_b=0;
        for(i=0;i<card_a;i++)
        {
            scanf("%ld", &card_number1);
            if(alice[card_number1]==true) continue;
            else alice[card_number1]=true;
        }
        for(i=0;i<card_b;i++)
        {
            scanf("%ld", &card_number2);
            if(betty[card_number2]==true) continue;
            else betty[card_number2]=true;
            if(alice[card_number2]==false) exchange_a++;
        }
        for(i=0;i<=card_number1;i++)
            if(betty[i]==false && alice[i]==true) exchange_b++;
        min=(exchange_a> exchange_b)? exchange_b : exchange_a;
        printf("%ld\n", min);
        for(i=0;i<=SIZE;i++) alice[i]=false, betty[i]=false;
    }
    return 0;
}
            
