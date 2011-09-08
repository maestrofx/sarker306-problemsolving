#include<stdio.h>
#include<stdbool.h>

int main()
{
    char ch, temp=0, ch2;
    bool flag=false, vowela=true;
    while((ch=getchar())!=EOF)
    {
        if((ch>='a'&& ch<='z')||(ch>='A' && ch<='Z'))
        {
            if(!flag)
            {
                if(ch>='A' && ch<='Z') ch2=ch+32;
                else ch2=ch;
                if(ch2!='a'&&ch2!='e'&&ch2!='i'&&ch2!='o'&&ch2!='u') vowela=false;
                else vowela=true;
                if(vowela) putchar(ch);
                else temp=ch;
                flag=true;
            }
            else putchar(ch);
        }
        else
        {
            if(temp)
            {
                putchar(temp);
                temp=0;
            }
            if(flag)
            {
                printf("ay");
                flag=false;
            }
            putchar(ch);
        }
    }
    return 0;
}
