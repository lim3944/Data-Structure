#include<stdio.h>
#include<stdlib.h>

#define Inf 987654321
#define EmptyTOS -1

//data type declare
typedef struct Node* node;
typedef struct HeapStruct* Heap;

struct Node{
	int vertex;
	int priority;
};

struct HeapStruct{
	int Capacity;
	int Size;
	node Elements;
};

//function prototype
Heap CreateHeap(int size);
void Push(Heap H, struct Node n);
struct Node Pop(Heap H);
int empty(Heap H);
void tracking(struct Node* n, int i);

int main(int argc, char** argv){
	FILE *ifp;
	int size;

	int data;
	int offset;

	int i, j;

	int** map;
	int* chk;
	int exist[100] = { 0, };

	char line1[200], line2[200];
	char *p = line1;

	ifp = fopen(argv[1], "r");
	fscanf(ifp, " %[^\n]", line1);
	//fscanf(ifp, " %[^\n]", line2);

	int max = 0;
	int start = 0;

	sscanf(p, "%d%n", &start, &offset);
	exist[start] = 1;
	p += offset;

	while (sscanf(p, "%d%n", &data, &offset) != EOF){
		exist[data] = 1;
		if (max < data)
			max = data;
		p += offset;
	}

	//p = line2;

	chk = (int*)malloc(sizeof(int)*(max + 2));
	map = (int**)malloc(sizeof(int*)*(max + 2));

	for (i = 0; i <= max; i++){
		chk[i] = 0;
		map[i] = (int*)malloc(sizeof(int)*(max + 2));
		for (j = 0; j <= max; j++)
			map[i][j] = Inf;
	}

	int a, b, c;

	while (fscanf(ifp, "%d-%d-%d ", &a, &b, &c) != EOF) {
		map[a][b] = c;
	}

	node Data;
	Data = (struct Node*)malloc(sizeof(struct Node)*(max + 2));

	for (i = 0; i <= max; i++){
		Data[i].priority = Inf;
	}

	Heap H;
	H = CreateHeap(max);

	struct Node temp,now;
	now.priority = 0;
	now.vertex = start;
	Push(H, now);
	Data[start].priority = 0;
	Data[start].vertex = start;



	while (!empty(H)){
		now = Pop(H);
		chk[now.vertex] = 1;
		for (i = 0; i <= max; i++){
			if (map[now.vertex][i] != Inf&&chk[i] == 0 && exist[i] == 1){

				if (now.priority + map[now.vertex][i] < Data[i].priority){
					Data[i].priority = now.priority + map[now.vertex][i];
					Data[i].vertex = now.vertex;
					temp.priority = now.priority + map[now.vertex][i];
					temp.vertex = i;
					Push(H, temp);
				}
			}
		}
	}
	
	int mean=Inf,mean_position;

	for (i = 0; i <= max; i++){
		if (exist[i]==0)
			continue;
		if(Data[i].priority<mean&&Data[i].priority!=0){
			mean_position=i;
			mean=Data[i].priority;
		}
		printf("from %d to %d:", start, i);
		tracking(Data, i);
		printf(" (cost %d)\n", Data[i].priority);
	}

	printf("Shortest path\nfrom %d to %d:",start,mean_position);
	tracking(Data,mean_position);
	printf(" (cost %d)\n", mean);

	return 0;
}

//Create a empty heap
Heap CreateHeap(int size){
	Heap H;
	H = (struct HeapStruct*)malloc(sizeof(struct HeapStruct));
	H->Capacity = size;
	H->Size = 0;
	H->Elements = (struct Node*)malloc(sizeof(struct Node)*(size + 2));
	return H;
}

//Insert the value to the heap
void Push(Heap H, struct Node value){
	int i;
	for (i = ++H->Size; H->Elements[i / 2].priority>value.priority; i /= 2){
		if (i / 2 == 0) {
			break;
		}
		H->Elements[i] = H->Elements[i / 2];
	}
	H->Elements[i].priority = value.priority;
	H->Elements[i].vertex = value.vertex;
}

//Return and delete the max value(top of the heap) from the heap
struct Node Pop(Heap H){
	int i, C;

	struct Node temp, Last;

	temp.priority = H->Elements[1].priority;
	temp.vertex = H->Elements[1].vertex;

	Last.priority = H->Elements[H->Size].priority;
	Last.vertex = H->Elements[H->Size].vertex;

	H->Size--;

	for (i = 1; i * 2 <= H->Size; i = C){
		C = i * 2;
		if (C != H->Size&&H->Elements[C + 1].priority<H->Elements[C].priority)
			C++;
		if (Last.priority>H->Elements[C].priority)
			H->Elements[i] = H->Elements[C];
		else
			break;
	}
	H->Elements[i] = Last;
	return temp;
}

//Return 1 if the heap is empty, else 0
int empty(Heap H){
	if (H->Size == 0)
		return 1;
	return 0;
}

//Operate back tracking and print the path
void tracking(struct Node *n, int i){
	int k = n[i].vertex;
	if (i == k){
		printf("%d", i);
		return;
	}
	tracking(n, k);
	printf("->%d", i);
}
