#include<stdio.h>

#define SIZE 6000
#define ERR 214984566

long long int heap_size;
long long int A[SIZE];

long long int parent(long long int i)
{
    return i/2;
}

long long int left(long long int i)
{
    return 2*i;
}

long long int right(long long int i)
{
    return 2*i+1;
}

void min_heap(long long int *A, long long int i)
{
    long long int l=left(i);
    long long int r=right(i);
    long long int smallest, temp;
    
    if(l<=heap_size && A[l]<A[i]) smallest=l;
    else smallest=i;
    if(r<=heap_size && A[r]<A[smallest]) smallest=r;
    
    if(smallest!=i)
    {
        temp=A[i];
        A[i]=A[smallest];
        A[smallest]=temp;
        min_heap(A, smallest);
    }
    
    return ;
}

void build_min_heap(long long int *A)
{
    long long int n=heap_size/2, i;
    
    for(i=n;i;i--) min_heap(A, i);
}

void heap_sort_min(long long int *A)
{
    long long int i, temp;
    
    build_min_heap(A);
    
    for(i=1;i<=A[0];i++) printf("%3d ", A[i]);
    printf("\n");
    
    for(i=heap_size;i;i--)
    {
        temp=A[1];
        A[1]=A[i];
        A[i]=temp;
        heap_size--;
        min_heap(A, 1);
    }
}

long long int heap_minimum(long long int *A)
{
    return A[1];
}

long long int heap_extract_min(long long int *A)
{
    long long int min;
    
    if(heap_size<1) return ERR;
    
    min=A[1];
    A[1]=A[heap_size];
    heap_size--;
    min_heap(A, 1);
    return min;
}

void heap_decrease_key(long long int *A, long long int i, long long int key)
{
    long long int temp, x=parent(i);
    
    if(key>A[i]) return;
    A[i]=key;
    while(i>1 && A[x]>A[i]){
        temp=A[x];
        A[x]=A[i];
        A[i]=temp;
        i=x;
    }
}

void min_heap_insert(long long int *A,long long int key)
{
    heap_size++;
    A[heap_size]=ERR;
    heap_decrease_key(A, heap_size, key);
}

int main()
{
    long long int i, x, y, cost;
    
    while(scanf("%d", &heap_size)!=EOF && heap_size>0 && heap_size<SIZE)
    {
        A[0]=heap_size;
        for(i=1;i<=heap_size;i++) scanf("%d", &A[i]);
        cost=0;
        
        build_min_heap(A);
        
        while((x=heap_extract_min(A))!=ERR){
            y=heap_extract_min(A);
            if(y!=ERR){
                cost+=x+y;
                x+=y;
            }
            else break;
            min_heap_insert(A, x);
        }
        printf("%I64d\n", cost);
    }
    
    return 0;
}
