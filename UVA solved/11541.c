#include<stdio.h>

int main()
{
    char ch, temp=0;
    long i=0, num=0;
    long test;
    scanf("%ld", &test);
    getchar();
    for(i=0;i<test;)
    {
        printf("Case %ld: ", i+1);
        ch=getchar();
        do
        {
            if(ch>='A'&& ch<='Z')
            {
                if(temp) for(;num;num--) printf("%c", temp);
                temp=ch;
                num=0;
            }
            else if(ch>='0'&& ch<='9') num=10*num+ch-'0';
            ch=getchar();
        }while(ch!='\n');
        if(temp) 
        {
            for(;num;num--) printf("%c", temp);
            printf("\n");
            i++;
            num=temp=0;
        }
    }
    return 0;
}
