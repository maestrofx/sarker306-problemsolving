#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *prototype(char *to, char *from){
    char val[128], *ptr = to, x, y = 'a';

    for( x = 0 ; x < 127 ; x++ ) val[x] = 0;
    while( *from ){
        x = *from++;
        if( val[x] == 0 ){
            if( isalpha(x) ) val[x] = y++;
            else val[x] = x;
        }
        *to++ = val[x];
    }

    *to = 0;
    return ptr;
}

char input[105][85];
char std_proto[] = "abc defgh ijklm nko peqrs ktcj abc uvwx ykz";
char std_line[] = "the quick brown fox jumps over the lazy dog";

int main(){
    char a[85], b[127];
    int n, i, j, sntnc, flag;

/*    gets(a);
    printf("%s\n", prototype( a, a ) );*/
    while(scanf("%d", &n) != EOF && n > 0){
        getchar();
        getchar();
        while(n--){
            for(j = 0 ; j < 127 ; j++ ) b[j] = 0;
            i = flag = 0;
            while(gets(input[i])){
                if( input[i][0] == 0 ) break;
                if( flag == -1 ) continue;
                prototype(a, input[i]);
                if( strcmp(std_proto, a) == 0 ){
                   if( flag == 0 ){
                       for(j = 0 ; input[i][j] ; j++ ){
                           if(b[input[i][j]] == 0) b[input[i][j]] = std_line[j];
                       }

                       flag = 1;
                   }
                   else{
                       for(j = 0 ; input[i][j] ; j++ ){
                           if( b[input[i][j]] != std_line[j]){
                               flag = -1;
                               break;
                           }
                       }
                   }
                }

                i++;
            }

            sntnc = i;
            if(flag < 1) puts("No solution.");
            else{
                for( i = 0 ; i < sntnc ; i++ ){
                    for( j = 0 ; input[i][j] ; j++ ) putchar(b[input[i][j]]);
                    puts("");
                }
            }

            if( n ) puts("");
        }
    }

    return 0;
}
