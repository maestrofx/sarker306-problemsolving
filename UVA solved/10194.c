#include<stdio.h>
#include<string.h>
#include<strings.h>  

typedef struct _rank{
    int points, played, wins, ties, losses, goaldif, goalsc, goalag;
    char name[35];
}rank;

rank teams[35];
char nameofgame[150];
char singlegame[200];
int num_games, num_teams, num_matches;

int compare(rank a, rank b)
{
    int x, i, j;
    char ch1, ch2;
    
    x=a.points-b.points;
    if(x) return x;
    
    x=a.wins-b.wins;
    if(x) return x;
    
    x=a.goaldif-b.goaldif;
    if(x) return x;
    
    x=a.goalsc-b.goalsc;
    if(x) return x;
    
    x=b.played-a.played;
    if(x) return x;
    
    return strcasecmp(b.name, a.name);
}

int stat_upgrade(char *a, int goal, int diff)
{
    int i;
    
    for(i=0;i<num_teams;i++){
        if(!strcmp(a, teams[i].name)) break;
    }
    
    if(i==num_teams) return 0;
    teams[i].played++;
    if(diff>0)teams[i].wins++, teams[i].points+=3;
    if(diff<0)teams[i].losses++;
    if(diff==0)teams[i].ties++, teams[i].points+=1;
    teams[i].goalsc+=goal;
    teams[i].goaldif+=diff;
    teams[i].goalag+=goal-diff;
    return 1;
}

void sort(rank a[], int count)
{
    int i, j=0;
    rank temp;
    
    for(i=0;i<count-1;i++){
        for(j=i+1;j<count;j++){
            if(compare(a[i], a[j])<0){
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}

int main()
{
    char foul[50];
    char team1[100], team2[100];
    int goal1, goal2;
    char *p1, *p2;
    int i;
    
    scanf("%d", &num_games);
    gets(foul);
    for(;num_games;num_games--){
        gets(nameofgame);
        scanf("%d", &num_teams);
        gets(foul);
        for(i=0;i<num_teams;i++){
            gets(teams[i].name);
            teams[i].points=teams[i].played=teams[i].wins=0;
            teams[i].losses=teams[i].ties=teams[i].goaldif=0;
            teams[i].goalsc=teams[i].goalag=0;
        }
        scanf("%d", &num_matches);
        gets(foul);
        for(;num_matches;num_matches--){
            gets(singlegame);
            for(p1=p2=singlegame; *p1 && *p1!='#';p1++);
            *p1=0;
            strcpy(team1, p2);
            p1++;
            for(p2=p1;*p1 && *p1!='@';p1++);
            *p1=0;
            sscanf(p2,"%d", &goal1);
            p1++;
            for(p2=p1;*p1 && *p1!='#';p1++);
            *p1=0;
            sscanf(p2,"%d", &goal2);
            p1++;
            for(p2=p1;*p1;p1++);
            strcpy(team2, p2);
            stat_upgrade(team1, goal1, goal1-goal2);
            stat_upgrade(team2, goal2, goal2-goal1);
        }
        
        sort(teams, num_teams);
        
        printf("%s\n", nameofgame);
        for(i=0;i<num_teams;i++){
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n", i+1, teams[i].name, teams[i].points, teams[i].played, teams[i].wins, teams[i].ties, teams[i].losses, teams[i].goaldif, teams[i].goalsc, teams[i].goalag);
        }
        if(num_games!=1) printf("\n");
    }
    
    return 0;
}
