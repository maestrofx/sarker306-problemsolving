/** Simple expression parser
    Author:- Herbert Schildt
    Source:- C:The complete Refernce */
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define SIZE 10005

/******************************************************************/
#define DELIMITER 1
#define VARIABLE 2
#define NUMBER 3

/*****************************************************************/
void reverse(char *from, char *to )
{
    int len=strlen(from);
    int l;
    for(l=0;l<len;l++) to[l]=from[len-l-1];
    to[len]='\0';
}

void zero_cancel(char *a){
    register int i, j;

    if(*a=='-') i=1, j=1;
    else i=j=0;
    for(;a[i]=='0';i++);
    for(;a[i];j++, i++) a[j]=a[i];
    if(j==0 || (j==1 && a[0]=='-')) a[0]='0', a[1]=0;
    else a[j]=0;
}

int cmp(char *a, char *b){
    int x=strlen(a), y=strlen(b);
    if(x==y) return strcmp(a, b);
    else return x-y;
}

int iszero(char *ans){
    if(ans[0]=='0' && ans[1]==0) return 1;
    return 0;
}

void add_minus(char *answer){
    int x=strlen(answer);
    answer[x+1]=0;
    for(;x;x--) answer[x]=answer[x-1];
    answer[0]='-';
}

/******************** arithmatic ops *****************************/
void multiply(char *result,char *first,char *sec)
{
	char F[SIZE],S[SIZE],temp[2*SIZE];
	int f_len,s_len,f,s,r,t_len,hold,res;
	f_len=strlen(first);
	s_len=strlen(sec);
	reverse(first,F);
	reverse(sec,S);
	t_len=f_len+s_len;
	r=-1;
	for(f=0;f<=t_len;f++)
		temp[f]='0';
	temp[f]='\0';
	for(s=0;s<s_len;s++)
	{
		hold=0;
		for(f=0;f<f_len;f++)
		{
			res=(F[f]-'0')*(S[s]-'0') + hold+(temp[f+s]-'0');
			temp[f+s]=res%10+'0';
			hold=res/10;
			if(f+s>r) r=f+s;
		}
		while(hold!=0)
		{
			res=hold+temp[f+s]-'0';
			hold=res/10;
			temp[f+s]=res%10+'0';
			if(r<f+s)
				r=f+s;
			f++;
		}
	}

	for(;r>0 && temp[r]=='0';r--);
	temp[r+1]='\0';
	reverse(temp,result);
}

void call_mult(char *res, char *fir, char *sec){
    if(*fir=='-' && *sec=='-') multiply(res, fir+1, sec+1);
    else if(*fir=='-'){
        multiply(res+1, fir+1, sec);
        *res='-';
        if(iszero(res+1)) res[0]='0', res[1]=0;
    }
    else if(*sec=='-'){
        multiply(res+1, fir, sec+1);
        *res='-';
        if(iszero(res+1)) res[0]='0', res[1]=0;
    }
    else multiply(res, fir, sec);
}

void exponentiate(char *res, char *base, long p){
    char temp[SIZE];

    if(p==0){
        strcpy(res, "1");
        return;
    }

    if(p&1){
        exponentiate(temp, base, p-1);
        multiply(res, temp, base);
    }
    else{
        exponentiate(temp, base, p>>1);
        multiply(res, temp, temp);
    }
}

void call_pow(char *res, char *base, long p){
    if(*base=='-'){
        if(p&1) exponentiate(res+1, base+1, p), *res='-';
        else exponentiate(res, base+1, p);
        if(iszero(res+1)) res[0]='0', res[1]=0;
    }
    else exponentiate(res, base, p);
}

void add(char *res, char *first, char *sec)
{
    char F[SIZE], S[SIZE], Res[SIZE];
    int f,s,sum,extra,now;
    f=strlen(first);
    s=strlen(sec);
    reverse(first,F);
    reverse(sec,S);

    for(now=0,extra=0;(now<f && now<s);now++)
    {
        sum=(F[now]-'0') + (S[now]-'0') + extra;
        Res[now]=sum%10 +'0';
        extra= sum/10;
    }
    for(;now<f;now++)
    {
        sum=F[now] + extra-'0';
        Res[now]=sum%10 +'0';
        extra=sum/10;
    }
    for(;now<s;now++)
    {
        sum=S[now] + extra-'0';
        Res[now]=sum%10 +'0';
        extra=sum/10;
    }
    if(extra!=0) Res[now++]=extra+'0';
    Res[now]='\0';
    if(strlen(Res)==0) strcpy(Res,"0");
    reverse(Res,res);
}

int subtract(char *result, char *large, char *small){
    char L[SIZE], S[SIZE];
    int l,s,now,hold,diff,sign=0;

    l=strlen(large);
    s=strlen(small);
    if(l<s){
        strcpy(result,large);
        strcpy(large,small);
        strcpy(small,result);
        now=l; l=s; s=now;
        sign = 1;
    }
    if(l==s){
        if(strcmp(large, small)<0){
            strcpy(result,large);
            strcpy(large,small);
            strcpy(small,result);
            now=l; l=s; s=now;
            sign =1;
        }
    }
    reverse(large,L);
    reverse(small,S);
    for(;s<l;s++)
    S[s]='0';
    S[s]='\0';
    for(now=0,hold=0;now<l;now++){
        diff=L[now]-(S[now]+hold);
        if(diff<0){
             hold=1;
            result[now]=10+diff+'0';
        }
        else{
            result[now]=diff+'0';
            hold=0;
        }
    }
    for(now=l-1;now>0;now--){
        if(result[now]!='0')
        break;
    }
    result[now+1]='\0';
    reverse(result,L);
    strcpy(result,L);

    return sign;
}

void call_sub(char *res, char *fir, char *sec){
    char temp[SIZE], temp2[SIZE];

    if(*fir=='-' && *sec=='-'){
        if(subtract(res, sec+1, fir+1)==1) add_minus(res);
    }
    else if(*fir=='-'){
        add(res+1, fir+1, sec);
        *res='-';
        if(iszero(res+1)) res[0]='0', res[1]=0;
    }
    else if(*sec=='-') add(res, fir, sec+1);
    else if(subtract(res, fir, sec)==1) add_minus(res);
}

void call_sum(char *res, char *fir, char *sec){
    if(*fir=='-' && *sec=='-'){
        add(res+1, fir+1, sec+1);
        *res='-';
        if(iszero(res+1)) res[0]='0', res[1]=0;
    }
    else if(*fir=='-') call_sub(res, sec, fir+1);
    else if(*sec=='-') call_sub(res, fir, sec+1);
    else add(res, fir, sec);
}

/***************************************************************/


/*****************************************************************/
char *prog;				/*holds expression to be analyzed*/
char token[SIZE];
char tok_type;
/*****************************************************************/
void eval_exp(char *answer);
void eval_exp2(char *answer);
void eval_exp3(char *answer);
void eval_exp4(char *answer);
void eval_exp5(char *answer);
void eval_exp6(char *answer);
void atom(char *answer);
void get_token(void);
void putback(void);
void serror(int error);
int isdelim(char c);

/****************************************************************/
/*Parser entry point*/
void eval_exp(char *answer)
{
	get_token();
	if(!*token)
	{
		serror(2);
		return;
	}

	eval_exp2(answer);
	if(*token)
		serror(0);	/*Last token must be null*/
}

/*Add or subtract two terms*/
void eval_exp2(char *answer)
{
	register char op;
	char temp[SIZE], res[SIZE];
	eval_exp3(answer);
	while((op=*token)=='+'||op=='-')
	{
		get_token();
		eval_exp3(temp);
		switch(op)
		{
		case '-':call_sub(res, answer, temp);
			     strcpy(answer, res);
				 break;
		case '+':call_sum(res, answer, temp);
			     strcpy(answer, res);
				 break;
		}
	}
}

/*Multiply or divide two factors*/
void eval_exp3(char *answer){
	register char op;
	char temp[SIZE], res[SIZE];
	eval_exp4(answer);
	while((op=*token)=='*'||op=='/'||op=='%')
	{
		get_token();
		eval_exp4(temp);
		switch(op)
		{
		case '*': call_mult(res, answer, temp);
			     strcpy(answer, res);
				   break;
		}
	}
}

/* Evaluate a unary + or -. */
void eval_exp4(char *answer)
{
  int x;
  register char  op;

  op = 0;
  if((tok_type == DELIMITER) && *token=='+' || *token == '-') {
    op = *token;
    get_token();
  }
  eval_exp5(answer);
  if(op == '-' && !iszero(answer)) add_minus(answer);
}

/* Process an exponent */
void eval_exp5(char *answer)
{
  char temp[SIZE], ex[SIZE];
  register long t;

  eval_exp6(answer);
  if(*token == '^') {
    get_token();
    eval_exp5(temp);
    if((t=atol(temp))==0) {
      strcpy(answer, "1");
      return;
    }

    call_pow(temp, answer, t);
    strcpy(answer, temp);
  }
}

/* Process a parenthesized expression. */
void eval_exp6(char *answer)
{
  if((*token == '(')) {
    get_token();
    eval_exp2(answer);
    if(*token != ')')
      serror(1);
    get_token();
  }
  else atom(answer);
}

/* Get the value of a number or a variable. */
void atom(char *answer)
{
  switch(tok_type) {
    case NUMBER:
      strcpy(answer, token);
      if(answer[0]=='-'){
          zero_cancel(answer+1);
          if(iszero(answer+1)) *answer='0', *(answer+1)=0;
      }
      else zero_cancel(answer);
      get_token();
      return;
    default:
      serror(0);
  }
}

/* Return a token to the input stream. */
void putback(void)
{
  char *t;

  t = token;
  for(; *t; t++) prog--;
}

/* Display a syntax error. */
void serror(int error)
{
  static char *e[]= {
      "Syntax Error",
      "Unbalanced Parentheses",
      "No Expression Present",
      "Division by Zero"
  };
  printf("%s\n", e[error]);
}

/* Return the next token. */
void get_token(void)
{
  register char *temp;

  tok_type = 0;
  temp = token;
  *temp = '\0';

  if(!*prog) return; /* at end of expression */

  while(isspace(*prog)) ++prog; /* skip over white space */

  if(strchr("+-*/%^=()", *prog)){
    tok_type = DELIMITER;
    /* advance to next char */
    *temp++ = *prog++;
  }
  else if(isalpha(*prog)) {
    while(!isdelim(*prog)) *temp++ = *prog++;
    tok_type = VARIABLE;
  }
  else if(isdigit(*prog)) {
    while(!isdelim(*prog)) *temp++ = *prog++;
    tok_type = NUMBER;
  }
  *temp = '\0';
}

/* Return true if c is a delimiter. */
int isdelim(char c)
{
  if(strchr(" +-/*%^=()", c) || c==9 || c=='\r' || c==0)
    return 1;
  return 0;
}

char array[1000000];

int receive(char *arr){
    char temp=0, ch, *ptr=arr;

    while(1){
        if((ch=getchar())==EOF) return 0;
        if(ch=='\n'){
            *arr=0;
           /* puts(ptr);*/
            return 1;
        }

        if(temp==ch && ch=='*'){
            *(arr-1)='^';
        }

        else if(ch!=' ' && ch!='\n') *arr++=ch;
        temp=ch;
    }
}

int main(){
    char answer[SIZE];

    while(receive(array)){
        answer[0]=0;
        prog=array;
        eval_exp(answer);
        printf("%s\n", answer);
    }

    return 0;
}
