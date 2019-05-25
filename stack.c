#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<ctype.h> 
#include"stack.h" 
#define N 30 //n is the size of the array 
 
char stack[N]; 
int top=-1; 
 
void push(char item) 
{ 
        if(top >=(N-1)) 
        { 
                printf("Stack Overflow!"); 
        } 
        else 
        { 
                top++; 
                stack[top] = item; 
        } 
} 
char pop() 
{ 
        char item; 
        if(top<0) 
        { 
                printf("Underflow or invalid expression"); 
                getchar(); 
                exit(1); 
        } 
        else 
        { 
                item = stack[top]; 
                top--; 
                return (item); 
        } 
} 
int isOperator(char sym) 
{ 
        if(sym == '*'|| sym == '/' || sym == '+' || sym == '-') 
        { 
                return 1; 
        } 
        else 
        { 
                return 0; 
        } 
} 
int priority(char sym) 
{ 
        if(sym == '*' || sym == '/') 
        { 
                return 2; 
        } 
        else if(sym == '+' || sym == '-') 
        { 
                return 1; 
        } 
        else  
        { 
                return 0; 
        } 
} 
void convert(char inf[],char post[]) 
{ 
        int i,j; 
        char item; 
        char x; 
        push('('); 
        strcat(inf,")"); 
        i=0;
        j=0;
        item = inf[i];
        while(item != '=')
        {
                if(item == '(')
                {
                        push(item);
                }
                else if(isdigit(item) || isalpha(item)||item == '.')
                {
                        post[j] =item;
                        j++;
                }
                else if(isOperator(item)==1) //if is an operator
                {
                        x=pop();
                        while((isOperator(x) == 1) && priority(x) >= priority(item))
                        {
                                post[j] = x;
                                j++;
                                x=pop();
                        }
                        push(x);
                        push(item);
                }
                else if(item == ')')
                {
                        x=pop();
                        while(x != '(')
                        {
                                post[j] = x;
                                j++;
                                x=pop();
                        }
                }
                else
                {
                  //if is neither
                  printf("INVALID CHARACTER");
                  exit(1);
                }
                i++;
                item = inf[i];
        }
        if(top>0)
        {
                printf("Invalid Symbol");
                getchar();
                exit(1);
        }
        post[j] = '\0'; // can be = also
}

