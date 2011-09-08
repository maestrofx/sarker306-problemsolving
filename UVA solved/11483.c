#include<stdio.h>
#include<string.h>
char a[10000];
int main()
{
    int x,y,j=1, i, s, d;
    while(scanf("%d",&x)==1 && x)
    {
        printf("Case %d:\n",j++);
        puts("#include<string.h>");
        puts("#include<stdio.h>");
        puts("int main()");
        puts("{");
        for(i=1;i<=x;i++)
        {
            gets(a);
            while(y=strlen(a)==0)
            gets(a);
            printf("printf(\"");
            for(s=0, d=strlen(a);s<d;s++)
            {
                if(a[s]=='\"'|| a[s]== '\\' )
                printf("\\");
                printf("%c",a[s]);
            }
            printf("\\n\");\n");
        }
		printf("printf(\"\\n\");\n");
        puts("return 0;");
        puts("}");
    }
    return 0;
}
