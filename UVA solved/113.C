#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    char str[200]="0";
    char *ptr;
    double num, x;
    int index;
    while(scanf("%d", &index)==1)
    {
        scanf("%s", str);
        ptr=str;
        /*printf("%s\n", str);*/
        num=0;
        while(*ptr!='\0')
        {
      /*      putchar(*ptr);
            printf("\a");*/
            num=10*num+*ptr-'0';
            ptr++;
        }
        /*printf("\n\a%lf\n\a", num);*/
        x=log10(num)/index;
        printf("%.0lf\n", pow(10,x));
    }
    return 0;
}
