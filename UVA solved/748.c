#include<stdio.h>

#define SIZE 1000
 
void reverse(char *from, char *to );
void call_mult(char *first,char *sec,char *result);

int main()
{
    char a[SIZE], b[SIZE], temp[SIZE];
    char *ptr;
    int decimal, index, len_a, len_b;
    int i,j;
    while(scanf("%s", a)==1)
    {
        decimal=0;
        scanf("%d", &index);
        ptr=a;
        len_a=strlen(a);
        for(;*ptr!='.';ptr++);
        for(i=len_a-1;a[i]=='0'&&a+i>=ptr;i--) a[i]=0;
        for(i=0;a[i]=='0'&&a+i<=ptr;i++);
        for(j=0;a[i]!=0;) 
        {
            if(a[i]=='.') 
            {
                decimal=1;
                i++;
                continue;
            }
            a[j++]=a[i++];
            if(decimal) decimal++;
        }
        a[j]=0;
        --decimal;
        decimal*=index;
        strcpy(b,a);
        if(index>1)
        {
            for(i=1;i<index;i++)
            {
                call_mult(a,b,temp);
                strcpy(b, temp);
            }
        }
        len_b=strlen(b);
        if(len_b<=decimal)
        {
            printf(".");
            for(i=0;i<decimal-len_b;i++) printf("0");
            printf("%s\n", b);
        }
        else
        {
            for(i=0;i<len_b-decimal;i++) printf("%c", b[i]);
            printf(".");
            for(i;i<len_b;i++) printf("%c", b[i]);
            printf("\n");
        }
    }
    return 0;
}
 
void reverse(char *from, char *to )
{
	int len=strlen(from);
	int l;
	for(l=0;l<len;l++)
	to[l]=from[len-l-1];
	to[len]='\0';
}
       
void call_mult(char *first,char *sec,char *result)
{
	char F[SIZE],S[SIZE],temp[2*SIZE];
	int f_len,s_len,f,s,r,t_len,hold,res;
	f_len=strlen(first);
	s_len=strlen(sec);
	reverse(first,F);
	reverse(sec,S);
	t_len=f_len+s_len;
	r=-1;
	for(f=0;f<=t_len;f++)
		temp[f]='0';
	temp[f]='\0';
	for(s=0;s<s_len;s++)
	{
		hold=0;
		for(f=0;f<f_len;f++)
		{
			res=(F[f]-'0')*(S[s]-'0') + hold+(temp[f+s]-'0');
			temp[f+s]=res%10+'0';
			hold=res/10;
			if(f+s>r) r=f+s;
		}
		while(hold!=0)
		{
			res=hold+temp[f+s]-'0';
			hold=res/10;
			temp[f+s]=res%10+'0';
			if(r<f+s)
				r=f+s;
			f++;
		}
	}
	for(;r>0 && temp[r]=='0';r--);
	temp[r+1]='\0';
	reverse(temp,result);
}
