#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
//data type declare
typedef struct CQueue *Queue;
struct CQueue{
	int *key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

//function prototype declare
Queue MakeEmpty(int max);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
void Topsort(int V,int** map,int* Indegree);

int main(int argc, char** argv){
	FILE *ifp;
	int size;
	
	int** map;
	int* Indegree;

	int data;
	int offset;

	char line1[200], line2[200];
	char *p = line1;

	ifp = fopen(argv[1], "r");
	fscanf(ifp, " %[^\n]", line1);
	fscanf(ifp, " %[^\n]", line2);

	int max = 0;
	while (sscanf(p, "%d%n", &data, &offset) != EOF){
		if (max < data)
			max = data;
		p += offset;
	}

	p = line2;

	map = (int**)malloc(sizeof(int*)*(max+1));
	Indegree = (int*)malloc(sizeof(int)*(max+1));

	int i = 0,j=0;
	for (int i = 0; i <= max; i++)
		map[i] = (int*)malloc(sizeof(int)*(max+1));

	for (i = 0; i <= max; i++){
		Indegree[i] = 0;
		for (j = 0; j <= max; j++)
			map[i][j] = 0;
	}

	char temp[5];
	int a=0, b=0;
	while (sscanf(p, "%s%n", temp,&offset) != EOF){
		a = temp[0] - '0';
		b = temp[2] - '0';
		map[a][b] = 1;
		Indegree[b]++;
		p += offset;
	}

	Topsort(max,map,Indegree);
	free(Indegree);
	for(i=0;i<=max;i++){
		free(map[i]);
	}
	free(map);
	return 0;

}

//Make a empty queue
Queue MakeEmpty(int max){
	Queue Q;
	Q = (struct CQueue*)malloc(sizeof(struct CQueue));

	Q->key = (int*)malloc(sizeof(int)*(max+1));
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

//Return true if the queue is full else false
int IsFull(Queue Q){
	if (Q->qsize == Q->max_queue_size)
		return 1;
	else
		return 0;
}

//Pop the first element of queue
int Dequeue(Queue Q){
	int temp = Q->key[Q->first];
	Q->qsize--;
	Q->first = (Q->first + 1) % (Q->max_queue_size);
	return temp;
}

//Insert the element in the queue
void Enqueue(Queue Q, int X){
	Q->qsize++;
	Q->rear = (Q->rear + 1) % (Q->max_queue_size);
	Q->key[Q->rear] = X;
}

//Operate Toplogical sort and print
void Topsort(int V,int** map, int* Indegree){
	Queue myQ=NULL;
	int i=0, j=0;
	int now=0;

	myQ = MakeEmpty(V);

	for (i = 1; i <= V; i++){
		if (Indegree[i] == 0){
			Enqueue(myQ, i);
		}
	}

	while (!IsEmpty(myQ)){
		now = Dequeue(myQ);
		printf("%d\t", now);
		for (j = 1; j <= V; j++){
			if (j == now){
				continue;
			}
			if (map[now][j] != 0){
				if (--Indegree[j] == 0){
					Enqueue(myQ, j);
				}
			}
		}
	}
	printf("\n");
	free(myQ);
}
