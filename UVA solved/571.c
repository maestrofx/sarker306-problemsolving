#include<stdio.h>

#define MAXLITER 1001
#define QUEUESIZE 2000000
#define INF 1<<29

long jug_state[MAXLITER+1][MAXLITER+1];
long state_parent[MAXLITER+1][MAXLITER+1];
long Ca, Cb, N;

char steps[][10]={"fill A","fill B","empty A","empty B","pour A B","pour B A"};
long head, tail, queue[QUEUESIZE+1];
void push(long x){
    queue[tail]=x;
    if(tail==QUEUESIZE) tail=0;
    else tail++;
}

long pop(){
    long x=queue[head];
    if(head==QUEUESIZE) head=0;
    else head++;
    return x;
}

void init(){
    int i, j;
    
    for(i=0;i<=Ca;i++){
        for(j=0;j<=Cb;j++){
            jug_state[i][j]=INF;
            state_parent[i][j]=-1;
        }
    }
    
    head=tail;
    
    state_parent[Ca][0]=Ca*MAXLITER;
    jug_state[Ca][0]=0;
    push(Ca*MAXLITER);
    state_parent[0][Cb]=Cb;
    jug_state[0][Cb]=1;
    push(Cb);
}

void print_path(long u){
    int ua=u/MAXLITER, ub=u%MAXLITER;
    
    if(state_parent[ua][ub]!=u){
        print_path(state_parent[ua][ub]);
    }
    
    printf("%s\n", steps[jug_state[ua][ub]]);
}

void bfs(){
    long u, v, ua, ub, va, vb;
    init();
    
    while(head!=tail){
        u=pop();
        ua=u/MAXLITER, ub=u%MAXLITER;
        if(ub==N){
            print_path(u);
            printf("success\n");
            return;
        }
        
        /* fill A */
        if(ua<Ca && state_parent[Ca][ub]==-1){
            jug_state[Ca][ub]=0;
            state_parent[Ca][ub]=u;
            push(Ca*MAXLITER+ub);
        }
        
        /* fill B */
        if(ub<Cb && state_parent[ua][Cb]==-1){
            jug_state[ua][Cb]=1;
            state_parent[ua][Cb]=u;
            push(ua*MAXLITER+Cb);
        }
        
        /* empty A */
        if(ua>0 && state_parent[0][ub]==-1){
            jug_state[0][ub]=2;
            state_parent[0][ub]=u;
            push(ub);
        }
        
        /* empty B */
        if(ub>0 && state_parent[ua][0]==-1){
            jug_state[ua][0]=3;
            state_parent[ua][0]=u;
            push(ua*MAXLITER);
        }
        
        /* pour A B */
        if(ua+ub<=Cb) va=0, vb=ua+ub;
        else vb=Cb, va=ua+ub-Cb;
        if(state_parent[va][vb]==-1){
            jug_state[va][vb]=4;
            state_parent[va][vb]=u;
            push(va*MAXLITER+vb);
        }
        
        /* pour B A */
        if(ua+ub<=Ca) va=ua+ub, vb=0;
        else va=Ca, vb=ua+ub-Ca;
        if(state_parent[va][vb]==-1){
            jug_state[va][vb]=5;
            state_parent[va][vb]=u;
            push(va*MAXLITER+vb);
        }
    }
}

int main(){
    while(scanf("%ld%ld%ld", &Ca, &Cb, &N)!=EOF) bfs();
    
    return 0;
}
