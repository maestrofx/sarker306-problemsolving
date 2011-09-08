#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
int main()
{
    char input[20];
    int store[20];
    while(scanf("%s",input)!=EOF)
    {
        if(input[0]=='E')
        break;
        if(input[0]=='1') printf("MEMBER\n");
        else
        {
            double hold=atof(input);
            int still,i;
            double temp;
            still=(int)hold;
            temp=hold-still;
            for(i=0;i<=9;++i)
            {
                temp*=3;
                if(temp<1)
                store[i]=0;
                else if(temp>1)
                {
                    still=(int)temp;
                    if(still==1) break;
                    store[i]=still;
                    temp-=still;
                }
            }
            if(still!=1) printf("MEMBER\n");
            else
            printf("NON-MEMBER\n");
        }
    }
    return 0;
}
