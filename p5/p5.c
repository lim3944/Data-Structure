#include<stdio.h>
#include<stdlib.h>

//type declare
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
int IsFull(Queue Q);
void Dequeue(Queue Q);
void Enqueue(Queue Q,int X);
void PrintFirst(Queue Q);
void PrintRear(Queue Q);
void DeleteQueue(Queue Q);

int main(int argc,char** argv){
	int i,j;
	int temp;
	FILE *ifp;
	Queue Q;
	ifp=fopen(argv[1],"r");
	char chk[2]={'0','0'};
	while(chk[0]!='q'){
		chk[0]='q';
		fscanf(ifp,"%s",chk);
		switch(chk[0]){
			case 'n':{
				fscanf(ifp,"%d",&temp);
				Q=MakeEmpty(temp);
				break;
			}
			case 'e':{
				fscanf(ifp,"%d",&temp);
				Enqueue(Q,temp);
				break;
			}
			case 'd':{
				Dequeue(Q);
				break;
			}
			case 'f':{
				PrintFirst(Q);
				break;
			}	
			case 'r':{
				PrintRear(Q);
				break;
			}
		}
	}
	DeleteQueue(Q);
	return 0;
}

//Make a empty queue
Queue MakeEmpty(int max){
	Queue Q;
	Q=malloc(sizeof(struct CircularQueue));
	
	Q->key=malloc(sizeof(int)*max);
	Q->first=0;
	Q->rear=-1;
	Q->qsize=0;
	Q->max_queue_size=max;
	return Q;
}

//Return true if the queue is empty else false
int IsEmpty(Queue Q){
	if(Q->qsize==0)
		return 1;
	else
		return 0;
}

//Return true if the queue is full else false
int IsFull(Queue Q){
	if(Q->qsize==Q->max_queue_size)
		return 1;
	else
		return 0;
}

//Pop the first element of queue
void Dequeue(Queue Q){
	if(IsEmpty(Q))
		printf("Dequeue Failed\t : Queue is Empty!\n");
	else {
		printf("Dequeue Success\t : %d\n",Q->key[Q->first]);
		Q->qsize--;
		Q->first=(Q->first+1)%(Q->max_queue_size);		
	}
}

//Insert the element in the queue
void Enqueue(Queue Q,int X){
	if(IsFull(Q))
		printf("Insertion Failed : Queue is Full\n");
	else{
		printf("Insertion Success: %d\n",X);
		Q->qsize++;
		Q->rear=(Q->rear+1)%(Q->max_queue_size);
		Q->key[Q->rear]=X;
	}
}

//Print the first element of the queue
void PrintFirst(Queue Q){
	if(IsEmpty(Q))
		printf("Print Failed\t : Queue is Empty!\n");
	else
		printf("Front of Queue\t : %d\n",Q->key[Q->first]);
}

//Print the last element of the queue
void PrintRear(Queue Q){
	if(IsEmpty(Q))
		printf("Print Failed\t : Queue is empty!\n");
	else
		printf("Rear of Queue\t : %d\n",Q->key[Q->rear]);
}

//Delete the queue
void DeleteQueue(Queue Q){
	free(Q->key);
	free(Q);
}
