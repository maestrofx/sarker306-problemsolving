#include <stdio.h>
#include <ctype.h>

int main(){
    char inp[100000], *ptr, ch;
    int val;

    while(gets(inp)){
        for(ptr = inp, val = 0 ; *ptr; ptr++){
            if( !isdigit(*ptr)){
                if(*ptr != '!'){
                    ch = (*ptr == 'b') ? ' ' : *ptr;
                    while( val-- > 0 ) putchar(ch);
                }
                else putchar('\n');

                val = 0;
            }
            else val += *ptr - '0';
        }

        putchar('\n');
    }

    return 0;
}
