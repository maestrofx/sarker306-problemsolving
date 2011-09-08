#include<stdio.h>
#include<string.h>

typedef struct{
	char name[25];
	int a, d;
}player;

player team[10];

int comp(player a, player b);
void sort(player *a);
void output(void);

int main(){
	int test;
	int i, j, k;
	
	scanf("%d", &test);
	for(i=1;i<=test;i++){
		for(j=0;j<10;j++){
			scanf("%s%d%d", team[j].name, &team[j].a, &team[j].d);
		}
		
		sort(team);
		
		/*for(j=0;j<10;j++){
			printf("%s %d %d\n", team[j].name, team[j].a, team[j].d);
			if(j==4) printf("#\n");
		}*/
		printf("Case %d:\n",i); 
		output();
	}
	
	return 0;
}

int comp(player a, player b){
    if(a.a!=b.a) return (a.a-b.a);
    if(a.d!=b.d) return (b.d-a.d);
    return strcmp(b.name, a.name);
}

void sort(player *a){
	int i, j;
	player temp;
	
	for(i=0;i<9;i++){
		for(j=i+1; j<10;j++){
			if(comp(a[i], a[j])<0){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	
	for(i=0;i<4;i++){
        for(j=i+1;j<5;j++){
            if(strcmp(a[i].name, a[j].name)>0){
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
    
	for(i=5;i<9;i++){
        for(j=i+1;j<10;j++){
            if(strcmp(a[i].name, a[j].name)>0){
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}

void output(void){
    int i;
    
    printf("(%s", team[0].name);
    for(i=1;i<5;i++) printf(", %s", team[i].name);
    printf(")\n(%s", team[5].name);
    for(i=6;i<10;i++) printf(", %s", team[i].name);
    printf(")\n");
}
