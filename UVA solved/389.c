#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa:  convert n to characters in s */
void itoa(long n, char s[], int rad)
{
    long i, sign;
    char digit[16]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = digit[n % rad];   /* get next digit */
    } while ((n /= rad) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    long n, m;
    int rad1, rad2;
    char digit[16]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char array[40];
    char number[40];
    char *ptr;
    int temp;
    while(scanf("%s%d%d", number, &rad1, &rad2)==3)
    {
        m=0;
        n=1;
        ptr=number;
        while(*ptr)
        {
            if(*ptr>='0'&&*ptr<='9') temp=*ptr-'0';
            else temp=*ptr-'A'+10;
            m=rad1*m+temp;
            ptr++;
        }
        n=m;
        itoa(n, array, rad2);
        if(strlen(array)<=7)printf("%7s\n", array);
        else printf("  ERROR\n");
    }
    return 0;
}
