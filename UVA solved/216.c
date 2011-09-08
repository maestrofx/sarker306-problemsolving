#include<stdio.h>
#include<math.h>
#define EPS 1e-6

typedef struct{
    int x, y;
}pos;
pos array[10];
int minsol[10], n;
double minlen;

double lineardis(pos a, pos b){
    int delx=a.x-b.x, dely=a.y-b.y;
    return sqrt(delx*delx+dely*dely);
}

void backtrack(int *a, int index, double len){
    int i, available[10];
    double distance, delx, dely;
    
    if(index==n && (len<minlen )){
        minlen=len;
        for(i=0;i<n;i++) minsol[i]=a[i];
        return;
    }
    
    for(i=0;i<n;i++) available[i]=0;
    for(i=0;i<index;i++) available[a[i]]=1;
    
    for(i=0;i<n;i++){
        if(available[i]==0){
            distance=lineardis(array[i], array[a[index-1]])+len+16;
            if(distance<minlen){
                a[index]=i;
                backtrack(a, index+1, distance);
            }
        }
    }
}

int search(){
    int i, solutions[10];
    
    for(i=0;i<n;i++){
        solutions[0]=i;
        backtrack(solutions, 1, 0);
    }
}

int main(){
    int i, test=1;
    
    while(scanf("%d", &n)!=EOF && n>0){
        for(i=0;i<n;i++) scanf("%d%d", &array[i].x, &array[i].y);
        
        minlen=150*100;
        search();
        printf("**********************************************************\nNetwork #%d\n", test++);
        for(i=1;i<n;i++){
            printf("Cable requirement to connect ");
            printf("(%d,%d) to (%d,%d)", array[minsol[i-1]].x, array[minsol[i-1]].y, array[minsol[i]].x, array[minsol[i]].y);
            printf(" is %.2lf feet.\n", 16+lineardis(array[minsol[i-1]], array[minsol[i]]));
        }
        
        printf("Number of feet of cable required is %.2lf.\n", minlen);
    }
    
    return 0;
}
