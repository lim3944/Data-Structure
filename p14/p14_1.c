#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define EmptyTOS -1

//data type declare
typedef struct Data *Stack;
struct Data{
	int *key;
	int top;
	int max_stack_size;
};

//function prototype declare
Stack CreateStack(int size);
void Push(int  X, Stack S);
int Top(Stack S);
void Pop(Stack S);
void RemoveStack(Stack S);
int Isempty(Stack S);
void tracking(int* before, int i);

 int main(int argc, char** argv){
	FILE *ifp;
	int size;

	int data;
	int offset;
	 
	int i, j;

	int** map;
	int exist[100] = { 0, };

	char line1[200], line2[200],line3[200];
	char *p = line1;

	ifp = fopen(argv[1], "r");
	fscanf(ifp, " %[^\n]", line1);
	fscanf(ifp, " %[^\n]", line2);
	fscanf(ifp, " %[^\n]", line3);

	int max = 0;

	while (sscanf(p, "%d%n", &data, &offset) != EOF){
		exist[data] = 1;
		if (max < data)
			max = data;
		p += offset;
	}

	p = line2;

	int a, b, c;

	int start, end;

	int* before;
	int* visit;

	before = (int*)malloc(sizeof(int)*(max + 2));
	visit = (int*)malloc(sizeof(int)*(max + 2));
	map = (int**)malloc(sizeof(int*)*(max + 2));

	for (i = 0; i <= max; i++){
		map[i] = (int*)malloc(sizeof(int)*(max + 2));
		for (j = 0; j <= max; j++)
			map[i][j] = 0;
		before[i] = visit[i] = 0;
	}


	while (sscanf(p, "%d-%d%n", &a, &b,&offset) != EOF) {
		map[a][b] = 1;
		p += offset;
	}

	p = line3;

	//DFS
	Stack S;
	int now, temp, chk = 0;;
	while (sscanf(p, "%d-%d%n", &start, &end,&offset) != EOF) {

		S = CreateStack(max);
		Push(start, S);
		before[start] = start;
		visit[start] = 1;
		now=temp = start;
		chk = 0;

		while (!Isempty(S)){
			now = Top(S);
			before[now] = temp;
			temp = now;
			Pop(S);
			if (now == end){
				chk = 1;
				break;
			}
			
			for (i = 0; i <= max; i++){
				if (visit[i] == 0 && exist[i] == 1 && map[now][i] == 1){
					visit[i] = 1;
					Push(i, S);
				} 
			}
		}
		if (chk == 1)
			tracking(before, end);
		else
			printf("not find\n");

		p += offset;
	}
	RemoveStack(S);
	free(map);
	free(before);
	free(visit);
	return 0; 
}

//Make a empty stack
Stack CreateStack(int size){
	Stack S = NULL;
	S = (Stack)malloc(sizeof(struct Data));
	S->key = (int*)malloc(sizeof(int)*size);
	S->max_stack_size = size;
	S->top = EmptyTOS;

	return S;
}

//Push the element to the stack
void Push(int X, Stack S){
	S->top++;
	S->key[S->top] = X;
}

//Pop the element on the top of stack
void Pop(Stack S){
	S->top--;
}

//return the value of top element
int Top(Stack S){
	return S->key[S->top];
}

//Remove the stack
void RemoveStack(Stack S){
	free(S->key);
	free(S);
}

//Return 1 if the stack is empty, else 0
int Isempty(Stack S){
	if (S->top == EmptyTOS)
		return 1;
	return 0;
}

//Operate the tracking and print
void tracking(int* before, int i){
	int k = before[i];
	if (i == k){
		printf("%d", i);
		return;
	}
	tracking(before, k);
	printf("->%d", i);
}
