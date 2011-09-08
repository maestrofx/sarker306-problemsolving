#include<stdio.h>

#define SIZE 104

int m, n;
char oil[SIZE][SIZE];
char visited[SIZE][SIZE];

void traverse(int i, int j)
{
    visited[i][j]=1;
    if(i>0)
    {
        if(j>0)
        {
            if(visited[i-1][j-1]==0)
            {
                if(oil[i-1][j-1]=='@') traverse(i-1, j-1);
            }
        }
        if(j<n-1)
        {
            if(visited[i-1][j+1]==0)
            {
                if(oil[i-1][j+1]=='@') traverse(i-1, j+1);
            }
        }
        if(visited[i-1][j]==0)
        {
            if(oil[i-1][j]=='@') traverse(i-1, j);
        }
    }
    if(i<m-1)
    {
        if(j>0)
        {
            if(visited[i+1][j-1]==0)
            {
                if(oil[i+1][j-1]=='@') traverse(i+1, j-1);
            }
        }
        if(j<n-1)
        {
            if(visited[i+1][j+1]==0)
            {
                if(oil[i+1][j+1]=='@') traverse(i+1, j+1);
            }
        }
        if(visited[i+1][j]==0)
        {
            if(oil[i+1][j]=='@') traverse(i+1, j);
        }
    }
    if(j>0)
    {
        if(visited[i][j-1]==0)
        {
            if(oil[i][j-1]=='@') traverse(i, j-1);
        }
    }
    if(j<n-1)
    {
        if(visited[i][j+1]==0)
        {
            if(oil[i][j+1]=='@') traverse(i, j+1);
        }
    }
    return;
}

int main()
{
    int i, j;
    char ch;
    int counter;
    while(scanf("%d%d", &m, &n)!=EOF && m && n)
    {
        getchar();
        counter=0;
        for(i=0;i<m;)
        for(j=0;j<n;)
        {
            if((ch=getchar())=='*' || ch=='@') oil[i][j]=ch, j++;
            if(ch=='\n')
            {
                i++;
                break;
            }
        }
        /*for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++) putchar(oil[i][j]);
            printf("\n");
        }*/
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(oil[i][j]=='@'&& visited[i][j]==0)
                {
                    traverse(i,j);
                    counter++;
                }
                visited[i][j]=1;
            }
        }
        printf("%d\n", counter);
        for(i=0;i<SIZE;i++)
        for(j=0;j<SIZE;j++) visited[i][j]=0;
    }
    return 0;
}
