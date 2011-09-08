#include<stdio.h>

int main()
{
    int test;
    int i;
    int press;
    char array[110];
    int value[27]={1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4,1};
    char *ptr;
    scanf("%d", &test);
    for(i=1;i<=test;)
    {
        press=0;
        gets(array);
        if(array[0]==0) continue;
        ptr=array;
        while(*ptr)
        {
            if (*ptr>='a'&&*ptr<='z') press+=value[*ptr-'a'];
            else press++;
            ptr++;
        }
        printf("Case #%d: %d\n", i, press);
        i++;
    }
    return 0;
}
