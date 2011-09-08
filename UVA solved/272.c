/*
  Name: 272
  Copyright: 
  Author: 
  Date: 02/09/09 00:51
  Description: TeX
*/
#include<stdio.h>
#include<stdbool.h>

int main()
{
    char letter;
    bool flag=0;
    while((letter=getchar())!=EOF)
    {
        if(letter=='"' && flag==0) 
        {
            printf("%c", '`');           
            printf("%c", '`');
            flag=1;
        }
        else if(letter=='"' && flag==1)
        {
            printf("%c", '\'');
            printf("%c", '\'');
            flag=0;
        }
        else putchar(letter);
    }
    return 0;
}










