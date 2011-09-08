#include<stdio.h>

#define SIZE 1005

int main()
{
    char number[SIZE];
    int sum=0, flag=0;
    char *ptr;
    while(gets(number))
    {
        if(strcmp(number, "0")==0) break;
        else
        {
            sum=flag=0;
            ptr=number;
            while(*ptr!=0)
            {
                if(flag)
                {
                    sum+=*ptr-'0';
                    flag=0;
                }
                else
                {
                    sum-=*ptr-'0';
                    flag=1;
                }
                ptr++;
            }
            printf("%s is", number);
            if(sum%11) printf(" not");
            printf(" a multiple of 11.\n");
        }
    }
    return 0;
}
