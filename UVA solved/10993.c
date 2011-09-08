#include<stdio.h>
#include<string.h>

#define SIZE 1000000
#define WHITE 0
#define GRAY 2
#define BLACK 4

long queue[SIZE+1];
long visit[SIZE+1];
int parent[SIZE+1];
int digit[SIZE+1];
long head, tail;
long n, cnt;
char array[SIZE+1];
char availables[15];

void enqueue(long x){
    queue[tail]=x;
    if(tail==SIZE) tail=0;
    else tail++;
}

long dequeue(){
    long x=queue[head];
    if(head==SIZE) head=0;
    else head++;
    return x;
}

void init(){
    long i;
    
    for(i=0;i<n;i++) visit[i]=WHITE, parent[i]=-1, digit[i]=-1;
}

void print_jinish(long index){
    if(parent[index]!=-1) print_jinish(parent[index]);
    array[cnt++]=digit[index];
}

int bfs(){
    long i, u, v, len=strlen(availables);
    
    head=tail=0;
    init();
    
    for(i=len-1; i>=0; i--){
        if(availables[i]=='0') continue;
        u=availables[i]-'0';
        v=u%n;
        if(!visit[v]){
            enqueue(v);
            visit[v]=GRAY;
            digit[v]=u+'0';
        }
    }
    
    while(head!=tail){
        u=dequeue();
        
        if(u==0){
            cnt=0;
            print_jinish(u);
            array[cnt]=0;
            printf("%s\n", array);
            return 1;
        }
        
        for(i=len-1; i>=0 ;i--){
            v=(10*u+availables[i]-'0')%n;
            if(visit[v]==WHITE){
                visit[v]=GRAY;
                enqueue(v);
                parent[v]=u;
                digit[v]=availables[i];
            }
        }
        
        visit[u]=BLACK;
    }
    
    return 0;
}

int main(){
    while(scanf("%s%ld", availables, &n)!=EOF){
        if(n==0 && availables[0]=='0') break;
        if( n==0 || !bfs()) printf("impossible\n");
    }
        
    return 0;
}
