#include <stdio.h>
#define MAXVAL 10
#define LIMIT 30000

int values;
long fval[2][MAXVAL];
char opStack[12], top;
long valStack[MAXVAL][12], vTop;
char solFound;
enum { DUP, ADD, MUL, SUB, DIV };
char commands[5][4] = { "DUP", "ADD", "MUL", "SUB", "DIV" };

long Abs( long a ) { return a > 0 ? a : -a ; }

void printStack(){
    int i, j;
    
    puts("\n**********************");
    for ( j = 0 ; j < vTop ; j++ ){
        printf("Level %d-> ", j);
        for ( i = 0 ; i < values ; i++ ) printf("%6d ", valStack[i][j]);
        puts("");
    }
    puts("**********************");
}

int doDup(){
    int i;
    
    opStack[top++] = DUP;
    for ( i = 0 ; i < values ; i++ ) valStack[i][vTop] = valStack[i][vTop - 1];
    vTop++;
    
    return 1;
}

int doAdd(long *oldVal){
    int i;
    long temp[MAXVAL];
    
    if ( vTop <= 1 ) return 0;
    for ( i = 0 ; i < values ; i++ ){
        temp[i] = valStack[i][vTop-2] + valStack[i][vTop - 1];
        if ( Abs(temp[i]) > LIMIT ) return 0;
    }
    
    opStack[top++] = ADD;
    vTop -= 2;
    for ( i = 0 ; i < values ; i++ ){
        oldVal[i] = valStack[i][vTop];
        valStack[i][vTop] = temp[i];
    }
    vTop++;
    for ( i = 0 ; i < values ; i++ ) oldVal[i+values] = valStack[i][vTop];
    
    return 1;
}

int doMul(long *oldVal){
    int i;
    long temp[MAXVAL];
    
    if ( vTop <= 1 ) return 0;
    for ( i = 0 ; i < values ; i++ ){
        temp[i] = valStack[i][vTop-2] * valStack[i][vTop - 1];
        if ( Abs(temp[i]) > LIMIT ) return 0;
    }
    
    opStack[top++] = MUL;
    vTop -= 2;
    for ( i = 0 ; i < values ; i++ ){
        oldVal[i] = valStack[i][vTop];
        valStack[i][vTop] = temp[i];
    }
    vTop++;
    for ( i = 0 ; i < values ; i++ ) oldVal[i+values] = valStack[i][vTop];
    
    return 1;
}

int doSub(long *oldVal){
    int i;
    long temp[MAXVAL];
    
    if ( vTop <= 1 ) return 0;
    for ( i = 0 ; i < values ; i++ ){
        temp[i] = valStack[i][vTop-2] - valStack[i][vTop - 1];
        if ( Abs(temp[i]) > LIMIT ) return 0;
    }
    
    opStack[top++] = SUB;
    vTop -= 2;
    for ( i = 0 ; i < values ; i++ ){
        oldVal[i] = valStack[i][vTop];
        valStack[i][vTop] = temp[i];
    }
    vTop++;
    for ( i = 0 ; i < values ; i++ ) oldVal[i+values] = valStack[i][vTop];
    
    return 1;
}

int doDiv(long *oldVal){
    int i;
    long temp[MAXVAL];
    
    if ( vTop <= 1 ) return 0;
    for ( i = 0 ; i < values ; i++ ){
        if ( valStack[i][vTop-1] == 0 ) return 0;
        temp[i] = valStack[i][vTop-2] / valStack[i][vTop - 1];
        if ( Abs(temp[i]) > LIMIT ) return 0;
    }
    
    opStack[top++] = DIV;
    vTop -= 2;
    for ( i = 0 ; i < values ; i++ ){
        oldVal[i] = valStack[i][vTop];
        valStack[i][vTop] = temp[i];
    }
    vTop++;
    for ( i = 0 ; i < values ; i++ ) oldVal[i+values] = valStack[i][vTop];
    
    return 1;
}

void doStep( int remaining ){
    int i;
    long temp[MAXVAL<<1];
    
    /*printf("-> %d\n", remaining);*/
    if ( remaining == 0 ){
        if ( vTop != 1 ) return;
        /*printStack();*/
        for ( i = 0 ; i < values ; i++ )
            if ( valStack[i][0] != fval[1][i] ) break;
        
        if ( i == values ){
            solFound = 1;
            for ( i = 0 ; i < top ; i++ )
                printf("%s%s", i ? " " : "" , commands[opStack[i]]);
            
            puts("\n");
        }
        
        return;
    }
    
    if ( solFound ) return;
    if ( doAdd(temp) ){
        /*printf("Adding, %d ops remaining\n", remaining - 1);
        for ( i = 0 ; i < values ; i++ ) printf("%d ", temp[i]);
        puts("");
        printStack();*/
        doStep(remaining-1);
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop - 1] = temp[i];
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop] = temp[i + values];
        vTop ++, top--;
        /*printf("Adding, %d ops remaining... reset\n", remaining-1);
        printStack();*/
    }
    
    if ( solFound ) return;
    if ( doDiv(temp) ){
        /*printf("Dividing, %d ops remaining\n", remaining-1);
        printStack();*/
        doStep(remaining-1);
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop - 1] = temp[i];
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop] = temp[i + values];
        vTop ++, top--;
        /*printf("Dividing, %d ops remaining... reset\n", remaining-1);
        printStack();*/
    }
    
    if ( solFound ) return;
    if ( vTop < remaining ){
        doDup();
        /*printf("Duplicating, %d ops remaining\n", remaining - 1);
        printStack();*/
        doStep(remaining-1);
        vTop--, top--;
        /*printf("Duplicating, %d ops remaining... reset\n", remaining-1);
        printStack();*/
    }
    
    if ( solFound ) return;
    if ( doMul(temp) ){
        /*printf("Multiplicating, %d ops remaining\n", remaining - 1);
        printStack();*/
        doStep(remaining-1);
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop - 1] = temp[i];
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop] = temp[i + values];
        vTop ++, top--;
        /*printf("Multiplicating, %d ops remaining... reset\n", remaining-1);
        printStack();*/
    }
    
    if ( solFound ) return;
    if ( doSub(temp) ){
        /*printf("Subtracting, %d ops remaining\n", remaining-1);
        printStack();*/
        doStep(remaining-1);
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop - 1] = temp[i];
        for ( i = 0 ; i < values; i++ ) valStack[i][vTop] = temp[i + values];
        vTop ++, top--;
        /*printf("Subtracting, %d ops remaining... reset\n", remaining-1);
        printStack();*/
    }
}

void initStack(){
    int i;
    
    top = 0;
    for ( i = 0 ; i < values ; i++ ) valStack[i][0] = fval[0][i];
    vTop = 1;
}

int findProgramSeq(){
    int i, step;
    
    for ( i = 0 ; i < values ; i++ ) if ( fval[0][i] != fval[1][i] ) break;
    if ( i == values ){
        puts("Empty sequence\n");
        return 0;
    }
    
    solFound = 0;
    for ( step = 1 ; step <= 10 && !solFound ; step++ ){
        /*printf("Step Allowed : %d\n", step);*/
        initStack();
        doStep(step);
    }
    
    if ( solFound == 0 ) puts("Impossible\n");
    
    return 0;
}

int main(){
    int kase = 1, i;
    
    while ( scanf("%d", &values) == 1 && values > 0 ){
        for ( i = 0 ; i < values ; i++ )
            scanf("%ld", &fval[0][i]);
        for ( i = 0 ; i < values ; i++ )
            scanf("%ld", &fval[1][i]);
        
        printf("Program %d\n", kase++);
        findProgramSeq();
    }
    
    return 0;
}
