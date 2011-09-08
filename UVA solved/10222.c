#include<stdio.h>

int main()
{
    char ch;
    while((ch=getchar())!=EOF)
    {
        if(ch>='a'&& ch<='z') ch-=32;
        switch(ch)
        {
            case 'E': ch='q';
                      break;
            case 'R': ch='w';
                      break;
            case 'T': ch='e';
                      break;
            case 'Y': ch='r';
                      break;
            case 'U': ch='t';
                      break;
            case 'I': ch='y';
                      break;
            case 'O': ch='u';
                      break;
            case 'P': ch='i';
                      break;
            case '[': ch='o';
                      break;
            case ']': ch='p';
                      break;
            case 'D': ch='a';
                      break;
            case 'F': ch='s';
                      break;
            case 'G': ch='d';
                      break;
            case 'H': ch='f';
                      break;
            case 'J': ch='g';
                      break;
            case 'K': ch='h';
                      break;
            case 'L': ch='j';
                      break;
            case ';': ch='k';
                      break;
            case '\'': ch='l';
                      break;
            case 'C': ch='z';
                      break;
            case 'V': ch='x';
                      break;
            case 'B': ch='c';
                      break;
            case 'N': ch='v';
                      break;
            case 'M': ch='b';
                      break;
            case ',': ch='n';
                      break;
            case '.': ch='m';
                      break;
            case '/': ch=',';
                      break;
            case '2': ch='`';
                      break;
            case '3': ch='1';
                      break;
            case '4': ch='2';
                      break;
            case '5': ch='3';
                      break;
            case '6': ch='4';
                      break;
            case '7': ch='5';
                      break;
            case '8': ch='6';
                      break;
            case '9': ch='7';
                      break;
            case '0': ch='8';
                      break;
            case '-': ch='9';
                      break;
            case '=': ch='0';
                      break;
            case '\\': ch='-';
                      break;
        }
        putchar(ch);
    }
    return 0;
}
