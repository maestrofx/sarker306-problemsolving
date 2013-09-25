#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
char grid[17];
typedef struct llnode{
    int index;
    struct llnode *next, *prev;
}llnode;
std::map<std::string, int> gameTree;

llnode* ll_new(int value){
    llnode *ptr = (llnode*)malloc(sizeof(llnode));
    ptr->index = value;
    ptr->next = ptr->prev = 0;
    return ptr;
}

void ll_insert( llnode *here, llnode *ptr ) {
    ptr->next = here->next;
    ptr->prev = here;
    here->next = ptr;
    ptr->next->prev = ptr;
}

void ll_remove( llnode *ptr ){
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
}

llnode *head, *tail;

void populateList(){
    int i;
    
    for ( i = 15 ; i >= 0 ; i-- ){
        if ( grid[i] == '.' ) ll_insert(head, ll_new(i));
    }
}

void clearList(){
    llnode *ptr, *tmp;
    
    for ( ptr = head->next ; ptr != tail ; ){
        tmp = ptr;
        /*printf("%d ", tmp->index);*/
        ptr = ptr->next;
        ll_remove(tmp);
        free(tmp);
    }
}

int getScore(){
    int i, j, k;
    
    for ( j = 0 ; j < 4 ; j++ ){
        for ( i = 0 ; i < 4 ; i++ )
            if ( grid[j*4 + i] != 'o' ) break;
        if ( i == 4 ) return 0;
    }
    
    for ( i = 0 ; i < 4 ; i++ ){
        for ( j = 0 ; j < 4 ; j++ )
            if ( grid[j*4 + i] != 'o' ) break;
        if ( j == 4 ) return 0;
    }
    
    for ( j = 3, k = 3 ; j >= 0 ; j -= 3, k += 2 ){
        for ( i = 0 ; i < 4 ; i++ ){
            if ( grid[i*k + j] != 'o' ) break;
        }
        
        if ( i == 4 ) return 0;
    }
    
    for ( j = 0 ; j < 4 ; j++ ){
        for ( i = 0 ; i < 4 ; i++ )
            if ( grid[j*4 + i] != 'x' ) break;
        if ( i == 4 ) return 2;
    }
    
    for ( i = 0 ; i < 4 ; i++ ){
        for ( j = 0 ; j < 4 ; j++ )
            if ( grid[j*4 + i] != 'x' ) break;
        if ( j == 4 ) return 2;
    }
    
    for ( j = 3, k = 3 ; j >= 0 ; j -= 3, k += 2 ){
        for ( i = 0 ; i < 4 ; i++ ){
            if ( grid[i*k + j] != 'x' ) break;
        }
        
        if ( i == 4 ) return 2;
    }
    
    for ( i = 0 ; i < 16 ; i++ ) if ( grid[i] == '.' ) return -1;
    return 1;
}

int minimax(int player){
    llnode *ptr, *tmp;
    int value, tmpValue;
    
    std::string now = grid;
    std::map<std::string, int>::iterator treePtr = gameTree.find(now);
    if ( treePtr != gameTree.end() ) return treePtr->second;
    
    value = getScore();
    if ( value != -1 ){
        gameTree.insert(std::pair<std::string, int>(now, value));
        /*printf("->%s %d\n", grid, value);*/
        return value;
    }
    
    /*printf("$$$ %s\n", grid);*/
    value = ( player ) ? 0 : 2;

    for ( ptr = head->next ; ptr != tail ; ){
        tmp = ptr;
        ptr = ptr->next ;
        ll_remove(tmp);
        
        grid[tmp->index] = ( player ) ? 'x' : 'o';
        tmpValue = minimax( player^1 );
        if ( player ){
            if ( value < tmpValue ) value = tmpValue;
        }
        else {
            if ( value > tmpValue ) value = tmpValue;
        }
        
        ll_insert( tmp->prev, tmp );
        grid[tmp->index] = '.';
    }
    
    gameTree.insert(std::pair<std::string, int>(now, value));
    return value;
}

int checkWinningFirstMove(){
    llnode *ptr, *tmp;
    int value;
    
    for ( ptr = head->next ; ptr != tail ; ){
        tmp = ptr;
        ptr = ptr->next ;
        ll_remove(tmp);
        
        grid[tmp->index] = 'x';
        value = minimax( 0 );
        
        ll_insert( tmp->prev, tmp );
        grid[tmp->index] = '.';
        
        if ( value == 2 ) return tmp->index;
    }
    
    return -1;
}

int main(){
    char command[2];
    int i;
    
    head = ll_new(-5);
    tail = ll_new(-5);
    head->next = tail;
    tail->prev = head;
    
    while ( gets(command) ){
        if ( command[0] == '$' ) break;
        for ( i = 0 ; i < 4 ; i++ ) gets(&grid[i<<2]);
        
        populateList();
        i = checkWinningFirstMove();
        if ( i == -1 ) puts("#####");
        else printf("(%d,%d)\n", i / 4, i % 4 );
        clearList();
    }
    
    free(head);
    free(tail);
    gameTree.clear();
    return 0;
}
