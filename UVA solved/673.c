#include<stdio.h>

#define SIZE 140

int main()
{
    char paren[SIZE];
    char temp, blah;
    long test, i, first, third;
    scanf("%ld", &test);
    getchar();
    for(; test; test--)
    {
        /*scanf("%s", paren);*/
        gets(paren);
        for(i=0, first=0, third=0, temp=0; first>=0 && third>=0 && paren[i]; i++)
        {
            blah=paren[i];
            switch (paren[i])
            {
                case '(' : first++;
                           break;
                case ')' : first--;
                           break;
                case '[' : third++;
                           break;
                case ']' : third--;
                           break;
            }
            if(temp)
            {
                if(temp=='[' && blah==')') break;
                if(temp=='(' && blah==']') break;
            }
            if(blah=='('||blah==')'||blah=='['||blah==']')temp=paren[i];
        }
        if(first==third && third==0) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
