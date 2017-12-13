#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EmptyTOS -1
#define MAX_SIZE 100

//type declare
typedef struct StackRecord *Stack;
struct StackRecord{
	char *key;
	int top;
	int max_stack_size;
};

//function prototype declare
Stack CreateStack(int MaxElements);
void Push(char X, Stack S);
void Pop(Stack S);
char Top(Stack S);
void RemoveStack(Stack S);
int Precedence(char X);

//main function
int main(int argc, char** argv){
	int n;
	FILE *ifp;
	char input[100];

	//file open
	ifp = fopen(argv[1], "r");

	fgets(input, MAX_SIZE, ifp);
	char temp_operator;
	Stack S = NULL;
	S = CreateStack(MAX_SIZE);
	printf("original infix form : %s", input);
	printf("converted postfix form : ");

	//infix to postfix algorithm
	for (n = 0; n<strlen(input); n++){
		switch (input[n]){
		case '#':{
			while (S->top != EmptyTOS){
				if (Top(S) != '('&&Top(S) != ')')
					printf("%c", Top(S));
				Pop(S);
			}
			printf("#");
			break;
		}
		case '(':{
			Push(input[n], S);
			break;
		}
		case ')':{
			while (Top(S) != '('){
				printf("%c", Top(S));
				Pop(S);
			}
			Pop(S);
			break;
		}
		case '+':
		case '-':
		case '/':
		case '*':
		case '%':{
			if (S->top == EmptyTOS)
				Push(input[n], S);
			else{
				while (Precedence(Top(S)) >= Precedence(input[n]) && Top(S) != '('&&S->top != EmptyTOS){

					printf("%c", Top(S));
					Pop(S);
				}
				Push(input[n], S);
			}
			break;
		}
		default:{
			printf("%c", input[n]);
			break;
		}
		}
	}

	//free memory
	RemoveStack(S);
	return 0;
}

//Create a new stack
Stack CreateStack(int MaxElements){
	Stack S = NULL;

	//memory allocation
	S = (Stack)malloc(sizeof(struct StackRecord));
	S->key = (char*)malloc(sizeof(char)*MaxElements);

	S->max_stack_size = MaxElements;
	S->top = EmptyTOS;

	return S;
}
//push the factor in the stack
void Push(char X, Stack S){
	S->top++;
	S->key[S->top] = X;
}
//Pop the factor from the top of stack
void Pop(Stack S){
	S->top--;
}
//return the factor from the top of stack
char Top(Stack S){
	return S->key[S->top];
}
//Free the memory that the stack occupied
void RemoveStack(Stack S){
	free(S->key);
	free(S);
}
//return the precedence of operator
int Precedence(char X){
	if (X == '+' || X == '-')
		return 1;
	if (X == '*' || X == '/' || X == '%')
		return 2;
	else
		return 3;
}
