#include<stdio.h>

#define HIGH_CARD 1
#define ONE_PAIR 2
#define TWO_PAIRS 3
#define THREE_OF_A_KIND 4
#define STRAIGHT 5
#define FLUSH 6
#define FULL_HOUSE 7
#define FOUR_OF_A_KIND 8
#define STRAIGHT_FLUSH 9
#define ROYAL_FLUSH 10

char hands[2][5][3];
int rank[128], suitenum[128], result_flag, print_flag=0;

int highest_card(){
    int maxrank0[5], maxrank1[5], i, j;
    
    for(i=0;i<5;i++){
        maxrank0[i]=rank[hands[0][i][0]];
        maxrank1[i]=rank[hands[1][i][0]];
    }
    
    for(i=0;i<4;i++){
        for(j=i+1;j<5;j++){
            if(maxrank1[i]<maxrank1[j]) maxrank1[i]^=maxrank1[j]^=maxrank1[i]^=maxrank1[j];
            if(maxrank0[i]<maxrank0[j]) maxrank0[i]^=maxrank0[j]^=maxrank0[i]^=maxrank0[j];
        }
    }
    
    for(i=0, j=0;i<5 && j<5 && maxrank0[i]==maxrank1[j];i++, j++);
    
    if(i!=5 && j!=5) return maxrank0[i]-maxrank1[i];
    return 0;
}

int is_straight(int x){
    int tmp[5], i, j;
    
    for(i=0;i<5;i++) tmp[i]=rank[hands[x][i][0]];
    for(i=0;i<4;i++){
        for(j=i+1;j<5;j++){
            if(tmp[i]>tmp[j]) tmp[i]^=tmp[j]^=tmp[i]^=tmp[j];
        }
    }
    
    for(i=1;i<5;i++) if(tmp[i]-tmp[i-1]!=1) return 0;
    
    return tmp[4];
}

int is_flush(int x){
    int i;
    char suite=hands[x][0][1];
    
    for(i=1;i<5;i++){
        if(hands[x][i][1]!=suite) return 0;
    }
    
    return rank[hands[x][4][0]];
}

int is_royal_flush(int x){
    int i;
    
    if(!is_flush(x)) return 0;
    for(i=0;i<5;i++){
        switch(hands[x][i][0]){
            case 'T' :
            case 'J' :
            case 'Q' :
            case 'K' :
            case 'A' : break;
            default  : return 0;
        }
    }
    
    return rank['A'];
}

int is_straight_flush(int x){
    int i;
    
    if(!is_flush(x)) return 0;
    for(i=1;i<5;i++){
        if(rank[hands[x][i][0]]!=rank[hands[x][i-1][0]]+1) return 0;
    }
    
    return rank[hands[x][4][0]];
}

int is_four_of_a_kind(int x){
    int i, temp[15];
    
    for(i=0;i<15;i++) temp[i]=0;
    for(i=0;i<5;i++) temp[rank[hands[x][i][0]]]++;
    for(i=0;i<15;i++) if(temp[i]==4) return i;
    return 0;
}

int is_three_of_a_kind(int x){
    int i, temp[15];
    
    for(i=0;i<15;i++) temp[i]=0;
    for(i=0;i<5;i++) temp[rank[hands[x][i][0]]]++;
    for(i=0;i<15;i++) if(temp[i]==3) return i;
    return 0;
}

int is_one_pair(int x){
    int i, temp[15];
    
    for(i=0;i<15;i++) temp[i]=0;
    for(i=0;i<5;i++) temp[rank[hands[x][i][0]]]++;
    for(i=0;i<15;i++) if(temp[i]==2) return i;
    return 0;
}

int is_two_pair(int x){
    int i, temp[15], max, count=0;
    
    for(i=0;i<=14;i++) temp[i]=0;
    for(i=0;i<5;i++) temp[rank[hands[x][i][0]]]++;
    for(i=0;i<=14;i++) if(temp[i]==2) max=i, count++;
    
    if(count==2) return max;
    return 0;
}

int is_full_house(int x){
    int max=is_one_pair(x), max1;
    
    if(!max) return 0;
    else max1=is_three_of_a_kind(x);
    if(!max1) return 0;
    
    return max+4*max1;
}

int winner(){
    int one, two;
    
    one=is_royal_flush(0), two=is_royal_flush(1);
    if(print_flag) if(one || two) printf("Royal Flush\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_straight_flush(0), two=is_straight_flush(1);
    if(print_flag) if(one || two) printf("Straight Flush\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_four_of_a_kind(0), two=is_four_of_a_kind(1);
    if(print_flag) if(one || two) printf("Four of a kind\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_full_house(0), two=is_full_house(1);
    if(print_flag) if(one || two) printf("Full House\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_flush(0), two=is_flush(1);
    if(print_flag) if(one || two) printf("Flush\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_straight(0), two=is_straight(1);
    if(print_flag) if(one || two) printf("Straight\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_three_of_a_kind(0), two=is_three_of_a_kind(1);
    if(print_flag) if(one || two) printf("Three Of A Kind\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_two_pair(0), two=is_two_pair(1);
    if(print_flag) if(one || two) printf("Two pairs\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    one=is_one_pair(0), two=is_one_pair(1);
    if(print_flag) if(one || two) printf("One pair\n");
    if(one-two) return one-two;
    if(one==two && one){
        if(print_flag) printf("Highest card\n");
        one=highest_card();
        return one;
    }
    
    if(print_flag) printf("Highest card\n");
    one=highest_card();
    return one;
}

int cmp(char *a, char *b){
    if(*(a+1)==*(b+1)) return rank[*a]-rank[*b];
    else return *(a+1)-*(b+1);
}

int main(){
    int i, j, k, result, count=0, totl=0, casenum=1;
    char input[50];
    
    suitenum['C']=0, suitenum['D']=1, suitenum['H']=2, suitenum['S']=3;
    rank['T']=10, rank['J']=11, rank['Q']=12, rank['K']=13, rank['A']=14;
    for(i=2;i<10;i++) rank[i+'0']=i;
    
    while(gets(input)){
        sscanf(input, "%s%s%s%s%s%s%s%s%s%s", &hands[0][0], &hands[0][1],
          &hands[0][2], &hands[0][3], &hands[0][4], &hands[1][0], &hands[1][1],
          &hands[1][2], &hands[1][3], &hands[1][4]);
        
        for(i=0;i<4;i++){
            for(j=i+1; j<5; j++){
                if(cmp(hands[0][i], hands[0][j])>0){
                    strcpy(input, hands[0][i]);
                    strcpy(hands[0][i], hands[0][j]);
                    strcpy(hands[0][j], input);
                }
            }
        }
        
        for(i=0;i<4;i++){
            for(j=i+1; j<5; j++){
                if(cmp(hands[1][i], hands[1][j])>0){
                    strcpy(input, hands[1][i]);
                    strcpy(hands[1][i], hands[1][j]);
                    strcpy(hands[1][j], input);
                }
            }
        }
        
        sprintf(input, "%s %s %s %s %s %s %s %s %s %s", hands[0][0], hands[0][1],
          hands[0][2], hands[0][3], hands[0][4], hands[1][0], hands[1][1],
          hands[1][2], hands[1][3], hands[1][4]);
          
        /*score0=score(0);
        score1=score(1);
        printf("%s\n", input);
        printf("%d %d\n", is_straight_flush(0), is_four_of_a_kind(1));*/
        
        result=winner();
        if(result>0) count++;
        else if(result<0) totl++;
        
        if(result) printf("%s wins.\n", result < 0? "White" : "Black");
        else printf("Tie.\n");
    }
    
    return 0;
}
