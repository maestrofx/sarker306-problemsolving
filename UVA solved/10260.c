#include<stdio.h>

int main()
{
    int char_val=0, temp_val=0;
    char ch;
    while((ch=getchar())!=EOF)
    {
        if(ch=='\n')
        {
            char_val=0;
            temp_val=0;
            putchar(ch);
        }
        else
        {
            switch(ch)
            {
                case 'B':
                case 'F':
                case 'P':
                case 'V': char_val=1;
                          break;
                case 'C':
                case 'G':
                case 'J':
                case 'K':
                case 'Q':
                case 'S':
                case 'X':
                case 'Z': char_val=2;
                          break;
                case 'D':
                case 'T': char_val=3;
                          break;
                case 'L': char_val=4;
                          break;
                case 'M':
                case 'N': char_val=5;
                          break;
                case 'R': char_val=6;
                          break;
                default: char_val=0;
            }
            if(char_val==temp_val) continue;
            else if(char_val) printf("%d", char_val);
            temp_val=char_val;
        }
    }
    return 0;
}
