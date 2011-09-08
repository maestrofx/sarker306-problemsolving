#include<stdio.h>

int main()
{
    char pascl[10000];
    char *ptr;
    char flag_num, flag_exp, flag_pt, flag_blank;
    while(gets(pascl))
    {
        ptr=pascl;
        flag_num=flag_exp=flag_pt=flag_blank=0;
        if(*ptr=='*') break;
        else
        for(;*ptr;ptr++)
        {
            if(*ptr==' ' && flag_num && !flag_blank) flag_blank=1;
            if(flag_blank && *ptr>='0' && *ptr<='9'){
                flag_num=0;
                break;
            }
            if(flag_num && flag_exp && (*ptr<'0' || *ptr>'9'))
            {
                flag_num=0;
                break;
            }
            if(!flag_num && *ptr>='0' && *ptr<='9')
            {
                flag_num=1;
                continue;
            }
            if(flag_num && (*ptr=='e' || *ptr=='E'))
            {
                if(ptr==pascl || (*(ptr-1)<'0' || *(ptr-1)>'9')){
                   flag_num=0;
                   break;
                }
                ptr++;
                if((*ptr<'0' || *ptr>'9')&& *ptr!='+' && *ptr!='-')
                {
                    flag_num=0;
                    break;
                }
                else flag_exp=1;
                continue;
            }
            if(!flag_num && (*ptr=='e' || *ptr=='E')) break;

            if(*ptr=='.' && (flag_exp||(flag_num && flag_pt)))
            {
                flag_num=0;
                break;
            }
            if(flag_num && *ptr=='.' && !flag_pt)
            {
                if(ptr==pascl || (*(ptr-1)<'0' || *(ptr-1)>'9')){
                   flag_num=0;
                   break;
                }

                ptr++;
                if(*ptr<'0' || *ptr>'9')
                {
                    flag_num=0;
                    break;
                }
                flag_pt=1;
                continue;
            }
        }
        for(ptr=pascl, flag_blank=0;*ptr;ptr++)
        {
            if(!flag_blank && *ptr==' ') continue;
            else flag_blank=1;
            putchar(*ptr);
        }
        if(flag_num && (flag_pt|| flag_exp)) printf(" is legal.\n");
        else printf(" is illegal.\n");
    }
    return 0;
}
