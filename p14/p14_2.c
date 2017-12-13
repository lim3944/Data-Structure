#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define EmptyTOS -1
#pragma warning(disable : 4996)
//data type declare

typedef struct CircularQueue *Queue;
struct CircularQueue{
	int *key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

//function prototype declare
Queue MakeEmpty(int max);
int IsEmpty(Queue Q);
void Pop(Queue Q);
void Push(int X, Queue Q);
int First(Queue Q);
void DeleteQueue(Queue Q);
void tracking(int* before, int i);

int main(int argc, char** argv){
	FILE *ifp;
	int size;

	int data;
	int offset;

	int i, j;

	int** map;
	int exist[100] = { 0, };

	char line1[200], line2[200], line3[200];
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


	while (sscanf(p, "%d-%d%n", &a, &b, &offset) != EOF) {
		map[a][b] = 1;
		p += offset;
	}

	p = line3;


	//BFS
	Queue Q;
	int now, temp, chk = 0;;
	while (sscanf(p, "%d-%d%n", &start, &end, &offset) != EOF) {

		Q = MakeEmpty(max);
		Push(start, Q);
		before[start] = start;
		visit[start] = 1;
		now = temp = start;
		chk = 0;

		while (!IsEmpty(Q)){
			now = First(Q);
			before[now] = temp;
			visit[now] = 1;
			temp = now;
			Pop(Q);
			if (now == end){
				chk = 1;
				break;
			}

			for (i = 0; i <= max; i++){
				if (visit[i] == 0 && exist[i] == 1 && map[now][i] == 1){
					visit[i] = 1;
					Push(i, Q);
				}
			}
		}
		if (chk == 1)
			tracking(before, end);
		else
			printf("not find\n");

		p += offset;
	}


	DeleteQueue(Q);
	free(map);
	free(before);
	free(visit);
	return 0;
}
//Make a empty queue
Queue MakeEmpty(int max){
	Queue Q;
	Q = (Queue)malloc(sizeof(struct CircularQueue));

	Q->key = (int*)malloc(sizeof(int)*max);
	Q->first = 0;
	Q->rear = -1;
	Q->qsize = 0;
	Q->max_queue_size = max;
	return Q;
}

//Return true if the queue is empty else false
int IsEmpty(Queue Q){
	if (Q->qsize == 0)
		return 1;
	else
		return 0;
}

//Pop the first element of queue
void Pop(Queue Q){
	Q->qsize--;
	Q->first = (Q->first + 1) % (Q->max_queue_size);
}

//Insert the element in the queue
void Push(int X, Queue Q){
	Q->qsize++;
	Q->rear = (Q->rear + 1) % (Q->max_queue_size);
	Q->key[Q->rear] = X;
}

//Print the first element of the queue
int First(Queue Q){
	return Q->key[Q->first];
}

//Delete the queue
void DeleteQueue(Queue Q){
	free(Q->key);
	free(Q);
}

//Operate tracking and print
void tracking(int* before, int i){
	int k = before[i];
	if (i == k){
		printf("%d", i);
		return;
	}
	tracking(before, k);
	printf("->%d", i);
}
