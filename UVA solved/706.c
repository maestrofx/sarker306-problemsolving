#include<stdio.h>

#define SIZE 15

void print_up(int n, char *array);
void print_up_up(int n, char *array);
void print_mid(int n, char *array);
void print_low_low(int n, char *array);
void print_low(int n, char *array);

int main()
{
    char array[SIZE];
    int n;
    while(scanf("%d%s", &n, array)!=EOF && n>0)
    {
        print_up(n, array);
        print_up_up(n, array);
        print_mid(n, array);
        print_low_low(n, array);
        print_low(n, array);
        printf("\n");
    }
    return 0;
}
    
void print_up(int n, char *a)
{
    int i, j;
    for(i=0;a[i];i++)
    {
        if(i) printf(" ");
        printf(" ");
        switch(a[i])
        {
            case '1': 
            case '4':for(j=0;j<n;j++) printf(" "); break;
            case '2':
            case '3':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0': for(j=0;j<n;j++) printf("-"); break;
        }
        printf(" ");
    }
    printf("\n");
    return;
}
void print_mid(int n, char *a)
{
    int i, j;
    for(i=0;a[i];i++)
    {
        if(i) printf(" ");
        printf(" ");
        switch(a[i])
        {
            case '0':
            case '1': 
            case '7':for(j=0;j<n;j++) printf(" "); break;
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '8':
            case '9': for(j=0;j<n;j++) printf("-"); break;
        }
        printf(" ");
    }
    printf("\n");
    return;
}
void print_low(int n, char *a)
{
    int i, j;
    for(i=0;a[i];i++)
    {
        if(i) printf(" ");
        printf(" ");
        switch(a[i])
        {
            case '1': 
            case '4':
            case '7':for(j=0;j<n;j++) printf(" "); break;
            case '2':
            case '3':
            case '5':
            case '6':
            case '8':
            case '9':
            case '0': for(j=0;j<n;j++) printf("-"); break;
        }
        printf(" ");
    }
    printf("\n");
    return;
}
void print_up_up(int n, char *a)
{
    int i, j, k;
    for(k=0;k<n;k++)
    {
        for(i=0;a[i];i++)
        {
            if(i) printf(" ");
            switch(a[i])
            {
                case '1':
                case '2':
                case '3':
                case '7': printf(" ");break;
                case '0':
                case '4':
                case '5':
                case '6':
                case '8':
                case '9': printf("|");break;
            }
            for(j=0;j<n;j++) printf(" ");
            switch(a[i])
            {
                case '5':
                case '6': printf(" ");break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '7':
                case '8':
                case '9': printf("|");break;
            } 
                  
        }
        printf("\n"); 
    }
    return;
}
void print_low_low(int n, char *a)
{
    int i, j, k;
    for(k=0;k<n;k++)
    {
        for(i=0;a[i];i++)
        {
            if(i) printf(" ");
            switch(a[i])
            {
                case '1':
                case '3':
                case '4':
                case '5':
                case '7':
                case '9': printf(" ");break;
                case '0':
                case '2':
                case '6':
                case '8': printf("|");break;
            }
            for(j=0;j<n;j++) printf(" ");
            switch(a[i])
            {
                case '2': printf(" ");break;
                case '0':
                case '1':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9': printf("|");break;
            }      
        }
        printf("\n"); 
    }
    return;
}
