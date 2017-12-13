#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define EmptyTOS -1

//data type declare
typedef struct Data *Stack;
struct Data{
	char *key;
	int top;
	int max_stack_size;
};

//function prototype declare
Stack CreateStack(int size);
void Push(char X,Stack S);
char Top(Stack S);
void Pop(Stack S);
void RemoveStack(Stack S);

int main(int argc,char** argv){
	FILE *ifp;
	int ans=0;
	ifp=fopen(argv[1],"r");
	char form[105];
	fgets(form,105,ifp);
	int length=strlen(form);
	int i=0;
	int temp1=0,temp2=0;
	int calculate=0;
	Stack S=CreateStack(length);
	printf("converted postfix form : ");

	//print the formula without #
	for(i=0;i<length;i++){
		if(form[i]=='#')
			break;
		printf("%c",form[i]);
	}

	printf("\n");
	i=0;

	while(form[i]!='#'){

		//if the element is digit, push it to stack
		if(isdigit(form[i]))
			Push(form[i],S);
		//else operate
		else{
			temp1=Top(S)-'0';
			Pop(S);
			temp2=Top(S)-'0';
			Pop(S);
			switch(form[i]){
				case '+':
					calculate=temp1+temp2;
					Push(calculate+'0',S);
					break;
				case '-':
					calculate=temp2-temp1;
					Push(calculate+'0',S);
					break;
				case '*':
					calculate=temp1*temp2;
					Push(calculate+'0',S);
					break;
				case '/':
					calculate=temp2/temp1;
					Push(calculate+'0',S);
					break;
				case '%':
					calculate=temp2%temp1;
					Push(calculate+'0',S);
					break;
			}
		}
		i++;
	}
	ans=Top(S)-'0';
	printf("evaluation result : %d",ans);
	RemoveStack(S);
	return 0;
	
				
}

//Make a empty stack
Stack CreateStack(int size){
	Stack S=NULL;
	S=(Stack)malloc(sizeof(struct Data));
	S->key=(char*)malloc(sizeof(char)*size);
	S->max_stack_size=size;
	S->top=EmptyTOS;

	return S;
}

//Push the element to the stack
void Push(char X,Stack S){
	S->top++;
	S->key[S->top]=X;
}

//Pop the element on the top of stack
void Pop(Stack S){
	S->top--;
}

//return the value of top element
char Top(Stack S){
	return S->key[S->top];
}

//Remove the stack
void RemoveStack(Stack S){
	free(S->key);
	free(S);
}
