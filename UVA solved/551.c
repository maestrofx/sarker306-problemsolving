#include<stdio.h>

int receive(char *arr){
    char temp=0, ch, *ptr=arr;

    while(1){
        if((ch=getchar())==EOF) return 0;
        if(ch=='\n'){
            *arr=0;
            /*printf("\" %s \"\n", ptr);*/
            return 1;
        }

        if(temp=='(' && ch=='*'){
            *(arr-1)='+', temp=' ';
        }
        else if(temp=='*' && ch==')'){
            *(arr-1)='-';
            temp=ch;
        }
        else{
            if(ch=='+' || ch=='-') ch=' ';
            *arr++=ch;
            temp=ch;
        }
    }

    *arr=0;
}

void process(char *arr){
    int a=0, b=0, c=0, d=0, top=0;
    char *ptr=arr, stack[4000];
    int indx[4000];

    while(*arr){
        switch(*arr){
            case '(' : stack[top]=*arr; indx[top++]=arr-ptr;break;
            case ')' : if(top==0 || stack[top-1]!='(') a=1;
                       else top--;
                       break;
            case '[' : stack[top]=*arr; indx[top++]=arr-ptr;break;
            case ']' : if(top==0 || stack[top-1]!='[') a=1;
                       else top--;
                       break;
            case '{' : stack[top]=*arr; indx[top++]=arr-ptr;break;
            case '}' : if(top==0 || stack[top-1]!='{') a=1;
                       else top--;break;
            case '+' : stack[top]=*arr; indx[top++]=arr-ptr;break;
            case '-' : if(top==0 || stack[top-1]!='+') a=1;
                        else top--; break;
            case '<' : stack[top]=*arr; indx[top++]=arr-ptr;break;
            case '>' : if(top==0 || stack[top-1]!='<') a=1;
                        else top--;
        }

        if(a==1){
            printf("NO %d\n", arr-ptr+1);
            return;
        }

        arr++;
    }

    if(top) printf("NO %d\n", arr-ptr+1);
    else puts("YES");
}

int main(){
    char inp[4000];

    while(receive(inp)) process(inp);

    return 0;
}
