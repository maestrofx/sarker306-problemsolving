#include<stdio.h>
#include<string.h>

#define lower(x) ((x)>='A' && (x)<='Z')? ((x)+32):(x)

int len;
char array[1000];

int compare(char a, char b)
{
    char ch1=a, ch2=b;
    
    ch1=lower(ch1);
    ch2=lower(ch2);
    if(ch1-ch2) return (ch2-ch1);
    if(a-b) return (b-a);
    return 0;
}

void sort(char *a, int count)
{
    int i, j;
    char temp;
    
    for(i=0;a[i+1];i++){
        for(j=i+1;a[j];j++){
            if(compare(a[i], a[j])<0){
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}

void perm(char a[], int index)
{
    int i, j, k, counter1, counter;
     
    index++;
    if(index==len)
    {
        printf("%s\n", a);
        return;
    }
    
    for(i=0; array[i]; i++)
    {
		for(j=0;j<i;j++)
		{
			if(array[j]==array[i])
				break;
		}

		if(j==i)
		{
			counter1=counter=0;

			for(j=0;j<index;j++)
			{
				if(array[i]==a[j])
					counter++;
			}

			for(j=0;array[j];j++)
			{
				if(array[j]==array[i])
					counter1++;
			}
        
			if(counter1-counter>0)
			{
				a[index]=array[i];
				a[index+1]=0;
				perm(a, index);
			}
		}

    }
}

int main()
{
    char a[1000], i, j, flag;
    int test;
    
    scanf("%d", &test);
    gets(array);
    for(;test;test--)
    {
        gets(array);
        len=strlen(array);
        sort(array, len);
        for(i=0;i<len;i++)
        {
			flag=1;
			for(j=0;j<i;j++)
			{
				if(array[i]==array[j])
				{
					flag=0;
					break;
				}
			}
			if(flag)
			{
				a[0]=array[i];
				perm(a, 0);
			}
        }
    }
    
    return 0;
}
