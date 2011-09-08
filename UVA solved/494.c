#include<stdio.h>

int main()
{
    char flag_word=0, ch, temp=0;
    long word_count=0;
    while((ch=getchar())!=EOF)
    {
        if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))
        {
            if(!flag_word) flag_word=1;
            temp=ch;
            continue;
        }
        else if(ch=='\n')
        {
            flag_word=0;
            if(temp) word_count++;
            printf("%ld\n", word_count);
            word_count=temp=0;
        }
        else if(flag_word)
        {
            flag_word=0;
            word_count++;
        }
        temp=0;
    }
    return 0;
}
