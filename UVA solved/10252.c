#include<stdio.h>
#include<ctype.h>


int a[26], b[26];

int main()
{
    char ch1;
    int flag=1;
    int i, j;
    while((ch1=getchar())!=EOF)
    {
       switch (flag)
       {
            case 1: if (ch1=='\n') flag=0;
                    else a[ch1-'a']++;
                    break;
            case 0: if (ch1=='\n')
                    {
                        flag=1;
                        for(i=0;i<26;i++)
                        {
                            j=(a[i]>b[i])? b[i]: a[i];
                            for(;j;j--) printf("%c", i+'a');
                            a[i]=b[i]=0;
                        }
                        printf("\n");
                    }
                    else b[ch1-'a']++;
                    break;
        }
    }
    return 0;
}
